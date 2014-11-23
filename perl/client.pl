#!/usr/bin/perl

use strict;
use IO::Socket;
use IO::Poll qw(POLLIN POLLOUT POLLERR POLLHUP);
use Errno qw(EWOULDBLOCK);
use constant MAXBUF => 8192;
$SIG{PIPE} = 'IGNORE'; # TODO 这是做什么

my ($to_stdout, $to_socket, $stdin_done, $sock_done);

my $host = shift or die "Usage: pollnet.pl host [port]\n";
my $port = shift || 'echo'; # TODO what is this?
my $socket = IO::Socket::INET->new("$host:$port") or die $@; # TODO what is that $@ ? other default is TCP?

my $poll = IO::Poll->new() or die "Cna't create IO::Poll object";
$poll->mask(\*STDIN => POLLIN); # TODO what is \* ?
$poll->mask($socket => POLLIN);

my $EOL = "\015\012";
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
			$stdin_done++ unless sysread($STDIN, $to_socket, 2048, length($to_socket));
			
		}
		elsif ($handle eq $socket) {
			$sock_done++ unless sysread($socket, $to_stdout,2048, length($to_stdout));
		}
	}

	# handle writers
	for my $handle ($poll->handles(POLLOUT|POLLERR)) {
		if ($handle eq \*STDOUT) {
			my $bytes = syswrite(STDOUT, $to_stdout);
			unless ($bytes) { # TODO notices this program style
				next if $! == EWOULDBLOCK;
				die "write to stdout failed: $!";
			}
			substr($to_stdout, 0, $bytes) = ''; # TODO notices this 
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
	my ($outmask, $inmask, $sockmask) = {0, 0, 0};

	$outmask = POLLOUT if length($to_stdout) > 0;
	$inmask = POLLIN unless length($to_socket) >= MAXBUF
							or ($sock_done || $stdin_done); # TODO unless or ?
	
	$sockmask  = POLLOUT unless length($to_socket) == 0 or $sock_done;
	$sockmask |= POLLIN  unless length($to_stdout) >= MAXBUF or $sock_done;

	$poll->mask(\*STDIN => $inmask);
	$poll->mask(\*STDOUT => $outmask);
	$poll->mask($socket => $sockmask);

	$socket->shutdown(1) if $stdin_done and !length($to_socket); 
}
