#!/usr/bin/perl
# file: gab7.pl
# 《perl网络编程》16.1节多路复用输入输出脚本

use strict;
use IO::Socket;
use IO::Poll qw(POLLIN POLLOUT POLLERR POLLHUP);
use Errno qw(EWOULDBLOCK);
use constant MAXBUF => 8192;
$SIG{PIPE} = 'IGNORE'; # 忽略PIPE信号，防止程序write已关闭的连接时异常退出

my ($to_stdout, $to_socket, $stdin_done, $sock_done);

my $host = shift || "127.0.0.1";
my $port = shift || 9000;
print "Connecting $host:$port \n";
my $socket = IO::Socket::INET->new("$host:$port") or die $@; # $@ 比 $! 输出的错误信息多一些。INET->new()返回的socket类型依据参数而有变化，具体描述参考 perldoc.perl.org

my $poll = IO::Poll->new() or die "Can't create IO::Poll object";
$poll->mask(\*STDIN => POLLIN); # \* 是typeglob，也叫类型团。具体原理不详，但一般在函数或类中传递 文件、socket句柄 时使用。
$poll->mask($socket => POLLIN);

# test
my $EOL = "\015\012"; # 使用\015\012比使用\r\n的好处是，在多平台(windows, unix)中能保持不变的行为。
if (!syswrite($socket, "GET /baidu.com HTTP/1.1".$EOL.$EOL)) {
	die "failed to GET\n";
}

$socket->blocking(0); # turn off blocking on the socket
STDOUT->blocking(0);  # turn off blocking on the socket

while ($poll->handles) {
	$poll->poll;

	# handle readers
	for my $handle ($poll->handles(POLLIN|POLLHUP|POLLERR)) {
		if ($handle eq \*STDIN) {
			$stdin_done++ unless sysread(STDIN, $to_socket, 2048, length($to_socket));
		}
		elsif ($handle eq $socket) {
			$sock_done++ unless sysread($socket, $to_stdout,2048, length($to_stdout));
		}
	}

	# handle writers
	for my $handle ($poll->handles(POLLOUT|POLLERR)) {
		if ($handle eq \*STDOUT) {
			my $bytes = syswrite(STDOUT, $to_stdout);
			unless ($bytes) { 
				next if $! == EWOULDBLOCK;
				die "write to stdout failed: $!";
			}
			substr($to_stdout, 0, $bytes) = ''; # 去除已经发送的字节
		}
		elsif ($handle eq $socket) {
			my $bytes = syswrite($socket, $to_socket);
			unless ($bytes) {
				next if $! == EWOULDBLOCK;
				die "write to socket failed: $!";
			}
			substr($to_socket, 0, $bytes) = '';
		}
	}
}
continue {
	my ($outmask, $inmask, $sockmask) = (0, 0, 0);

	if (length($to_stdout) > 0){
		$outmask = POLLOUT;
	}
	if (length($to_socket) < MAXBUF
		&& !($sock_done || $stdin_done)) { # TODO unless or ?
		$inmask = POLLIN;
	}
	
	if (length($to_socket) > 0 && !$sock_done) {
		$sockmask  = POLLOUT;
	}

	if (length($to_stdout) < MAXBUF && !$sock_done) {
		$sockmask |= POLLIN;
	}

	$poll->mask(\*STDIN => $inmask);
	$poll->mask(\*STDOUT => $outmask);
	$poll->mask($socket => $sockmask);

	if ($stdin_done and !length($to_socket)) { 
		$socket->shutdown(1);
	}
}
print "end...\n";
