#!/usr/bin/perl
# fil: eliza_thread.pl
# 《perl网络编程》11.2节多线程服务器

use strict;
use IO::Poll qw(POLLIN POLLOUT POLLERR POLLHUP);
use IO::Socket;
use Errno qw(EWOULDBLOCK);
use Thread;

my $port = 9000;
my $listen_socket = IO::Socket::INET->new (
		LocalPort => $port,
		Listen => 20, # max clients
		Proto => 'tcp',
		Reuse => 1);

die $@ unless $listen_socket; # $@ is what?

print "listening port:$port for connections...\n";

while (my $connection = $listen_socket->accept()) {
	Thread->new(\&interact, $connection);
}


sub interact {
	my $sock = shift;

	print "$sock: new client\n";

	Thread->self->detach; # detach is what?
	
	my $poll = IO::Poll->new() or die "Can't create IO::Poll object.";
	$poll->mask($sock => POLLIN);
	$sock->blocking(0);

	my ($sock_done, $to_sock, $from_sock) = (0, "\nHello! I am $sock.\n", "");
	while ($poll->handles) { # handles is a function?
		$poll->poll();
		
		# read
		for my $h ($poll->handles(POLLIN|POLLHUP|POLLERR)) {
			if ($h eq $sock) {
				if (!sysread($h, $from_sock, 2048, length($from_sock))) {
					$sock_done++;
				}
			}
		}

		# write
		for my $h ($poll->handles(POLLOUT|POLLERR)) {
			if ($h eq $sock) {
				my $bytes = syswrite($h, $to_sock);
				if (!$bytes) {
					if ($! == EWOULDBLOCK) {next;}
					die "write to socket failed: $!";
				}
				substr($to_sock, 0, $bytes) = ''; # details usage about substr? 
			}
		}
	}
	continue {
		my ($sockmask) = (0);

		if (length($from_sock) > 0) {
			# TODO recv some cmd
			chomp($from_sock);
			$to_sock .= "\n$sock have recv some world ($from_sock)!\n";
			substr($from_sock, 0, length($from_sock)) = '';
		}

		if (length($from_sock) < 2048 && !$sock_done) {
			$sockmask |= POLLIN;
		}
		if (length($to_sock) > 0 && !$sock_done) {
			$sockmask |= POLLOUT;
		}
		
		$poll->mask($sock => $sockmask);

		if ($sock_done && length($to_sock) == 0) {
			$sock->shutdown(1);
		}
	}
	
	print "$sock: disconnect client\n";
	$sock->close();
}
