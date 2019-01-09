set ns [new Simulator]
set nf [open p6.nam w]
$ns namtrace-all $nf
set nd [open p6.tr w]
$ns trace-all $nd
set er_rate 0.07

proc finish {} {
global ns nf nd
$ns flush-trace
close $nf
exec nam p6.nam &
exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

#set color to the nodes
$n1 color blue
$n0 color red
$n2 color purple
$n3 color orange
$n4 color orange
$n5 color yellow

$n0 label TCP
$n1 label UDP
#$n3 label NULL-TCPSINK

$ns duplex-link $n0 $n2 512kb 10ms DropTail
$ns duplex-link $n1 $n2 512kb 10ms DropTail
$ns duplex-link $n2 $n3 256kb 10ms DropTail
$ns duplex-link $n3 $n2 256kb 10ms DropTail


set lan [$ns newLan "$n3 $n4 $n5" 0.5Mb 40ms LL Queue/DropTail MAC/Csma/Cd Channel]

#Give node position
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns simplex-link-op $n2 $n3 orient right
$ns simplex-link-op $n3 $n2 orient left

set lm [new ErrorModel]
$lm ranvar [new RandomVariable/Uniform]
$lm drop-target [new Agent/Null]
$lm set rate_ $er_rate
$ns lossmodel $lm $n2 $n3


set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n4 $sink0
$ns connect $tcp0 $sink0
$tcp0 set fid_ 1

#$tcp0 set class_ 1

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0
set null0 [new Agent/Null]
$ns attach-agent $n5 $null0
$ns connect $udp0 $null0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0
$udp0 set fid_ 2

$ns at 0.2 "$cbr0 start"
$ns at 0.1 "$ftp0 start"
$ns at 4.5 "$cbr0 stop"
$ns at 4.4 "$ftp0 stop"
$ns at 5.0 "finish"
$ns run
