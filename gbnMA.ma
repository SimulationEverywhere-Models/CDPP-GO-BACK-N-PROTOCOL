[top]
components : transmitter@Transmitter
components : timer0@Timer
components : timer1@Timer
components : timer2@Timer
components : timer3@Timer
components : Network
components : receiver@Receiver

out : ->->->->->sentPkt
out : <-<-<-ack
out : !!!!!!!!!!!!!!!!!!!!!!!!!!reset
in : startTx


Link : resetTimers@transmitter !!!!!!!!!!!!!!!!!!!!!!!!!!reset
Link : out2@Network <-<-<-ack
Link : sentPkt@transmitter ->->->->->sentPkt
Link : sentData@transmitter in1@Network
Link : out1@Network in@receiver
Link : out@receiver in2@Network 
Link : out2@Network rxAck@transmitter

Link : resetTimers@transmitter reset@timer0
Link : resetTimers@transmitter reset@timer1
Link : resetTimers@transmitter reset@timer2
Link : resetTimers@transmitter reset@timer3
Link : t0Trig@transmitter trigger@timer0
Link : t1Trig@transmitter trigger@timer1
Link : t2Trig@transmitter trigger@timer2
Link : t3Trig@transmitter trigger@timer3
Link : timeOutSig@timer0 t0TimeOut@transmitter
Link : timeOutSig@timer1 t1TimeOut@transmitter
Link : timeOutSig@timer2 t2TimeOut@transmitter
Link : timeOutSig@timer3 t3TimeOut@transmitter
Link : startTx startTx@transmitter


[transmitter]
txTime : 00:00:10:000 
pTime : 00:00:00:100
rTime : 00:00:00:001

[receiver]
preparation : 00:00:01:000 

[timer0]
timeOut : 00:01:00:00
zero : 00:00:00:00

[timer1]
timeOut : 00:01:00:00
zero : 00:00:00:00

[timer2]
timeOut : 00:01:00:00
zero : 00:00:00:00

[timer3]
timeOut : 00:01:00:00
zero : 00:00:00:00

[Network]
components : subnet1@Subnet
components : subnet2@Subnet

out : in1 in2
out : out1 out2

Link : in1 in@subnet1
Link : out@subnet1 out1 
Link : in2 in@subnet2
Link : out@subnet2 out2 

[subnet1]
distribution : normal
mean : 3
deviation : 1

[subnet2]
distribution : normal
mean : 3
deviation : 1 
