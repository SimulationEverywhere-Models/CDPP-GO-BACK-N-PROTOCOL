/*******************************************************************
*
*  DESCRIPTION: Atomic Model Timer
*
*  AUTHOR: Ahmad Mizan 
*  
*  DATE: 28/10/2008
*
*******************************************************************/

#ifndef __TIMER_H
#define __TIMER_H


#include "atomic.h"     // class Atomic

class Timer : public Atomic
{
public:
	Timer( const string &name = "Timer" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &trigger;
	const Port &timeOutSig;
	Port &reset;
	Time timeOut, zero;
//	int alt_bit;
//	bool sending;
//	typedef list<Value> ElementList ;
//	ElementList elements ;

//	Time timeLeft;

};	// class Timer

// ** inline ** // 
inline
string Timer::className() const
{
	return "Timer" ;
}

#endif   //__TIMER_H
