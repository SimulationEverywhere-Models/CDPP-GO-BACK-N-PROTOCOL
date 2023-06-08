[top]
components : timer@Timer
out : timeOutSig
in : trigger
in : reset
Link : timeOutSig@timer timeOutSig
Link : trigger trigger@timer
Link : reset reset@timer

[timer]
timeOut : 00:00:20:000 
zero : 00:00:00:00

