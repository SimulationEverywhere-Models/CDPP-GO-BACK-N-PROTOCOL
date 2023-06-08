[top]
components : transmitter@Transmitter
components : timer0@Timer
components : timer1@Timer
components : timer2@Timer
components : timer3@Timer


out : ->->->->->->sentPkt
out : <-<-<-ack
out : !!!!!!!!!!!!!!!!!!!!!!!!!!reset
in : startTx
in : ack

Link : ack rxAck@transmitter
Link : startTx startTx@transmitter
Link : resetTimers@transmitter !!!!!!!!!!!!!!!!!!!!!!!!!!reset
Link : rxSeq@transmitter <-<-<-ack
Link : sentPkt@transmitter ->->->->->->sentPkt
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

[transmitter]
txTime : 00:00:10:000 
pTime : 00:00:00:100
rTime : 00:00:00:001

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
