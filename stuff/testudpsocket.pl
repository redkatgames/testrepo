use IO::Socket;
use strict;

my $sock = IO::Socket::INET->new(
    Proto    => 'udp',
    PeerPort => 5000,
    PeerAddr => 'hostname',
) or die "Could not create socket: $!\n";

$sock->send('a file to have your advice') or die "Send error: $!\n";
