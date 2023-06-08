/*******************************************************************
*
*  DESCRIPTION: Atomic Model Timer
*
*  AUTHOR: Ahmad Mizan 
*  
*  DATE: 28/10/2008
*
*******************************************************************/

#ifndef _TRANSMITTER_H
#define _TRANSMITTER_H


#include "atomic.h"     // class Atomic

class Transmitter : public Atomic
{
public:
	Transmitter( const string &name = "Transmitter" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	Port &startTx;
	Port &sentData;
	Port &sentPkt;
	Port &rxSeq;
	Port &rxAck;
	Port &t0Trig, &t1Trig, &t2Trig, &t3Trig;
	Port &t0TimeOut, &t1TimeOut, &t2TimeOut, &t3TimeOut;
	Port &resetTimers;
	Time txTime;
	Time pTime;
	Time rTime;
	int txSeq;
	int counter;
	int pktNum;
	int totalPktNum; 
	int expectedSeq, receivedSeq;
	bool doResetTimers;
	bool sending;
	bool ackReceived;
	bool newFram;

//	int alt_bit;
//	bool sending;
//	typedef list<Value> ElementList ;
//	ElementList elements ;

//	Time timeLeft;

};	// class Transmitter

// ** inline ** // 
inline
string Transmitter::className() const
{
	return "Transmitter" ;
}

#endif   _TRANSMITTER_H
