/*******************************************************************
*
*  DESCRIPTION: Atomic Model Timer
*
*  AUTHOR: Ahmad Mizan 
*  
*  DATE: 28/10/2008
*
*******************************************************************/

/** include files **/
#include "timer.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: Timer
* Description: 
********************************************************************/
Timer::Timer( const string &name )
: Atomic( name )
, trigger( addInputPort( "trigger" ) )
, timeOutSig( addOutputPort( "timeOutSig" ) )
, reset( addInputPort("reset"))
, timeOut(0, 0, 20, 0)
, zero(0,0,0,0)
{	string time2( MainSimulator::Instance().getParameter( description(), "timeOut" ) ) ;

	if( time2 != "" )
		timeOut = time2 ;	
	string time3( MainSimulator::Instance().getParameter( description(), "zero" ) ) ;

	if( time3 != "" )
		zero = time3 ;	
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Timer::initFunction()
{
	this-> passivate();
	//holdIn(passive, Time::zero);
	//trigger = false;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Timer::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == trigger  /*&& this->state() == passive*/ && msg.value()!=0)
	{	
		holdIn(active, timeOut ); 
	}
	
	if( msg.port() == reset && msg.value()!=0)
	{	
		holdIn(passive, zero ); 
	}
	
	//if( msg.port() == trigger  && this->state() == active)
	//{	
	//	holdIn(active, timeOut ); 
	//}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Timer::internalFunction( const InternalMessage & )
{
	if(state()==active)
	{
		holdIn( passive  , timeOut );
	}
	else
		this->passivate();
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Timer::outputFunction( const InternalMessage &msg )
{
	if(state()==passive)
	{
		sendOutput( msg.time(), timeOutSig, false ) ;
	}
	else
		sendOutput( msg.time(), timeOutSig, true ) ;
	return *this ;
}

