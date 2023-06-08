/*******************************************************************
*
*  DESCRIPTION: Atomic Model Receiver
*
*  AUTHOR: Ahmad Mizan
*
*
*
*******************************************************************/

/** include files **/
#include "receiver.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Receiver
* Description: 
********************************************************************/
Receiver::Receiver( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
, preparationTime( 0, 0, 10, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Receiver::initFunction()
{
	this-> passivate();
	receivedData = 0; 
	expected = 0;
	seq=0;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Receiver::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in )
	{
		receivedData = static_cast < int > (msg.value());
		/*if(receivedData%10==seq)
		{
			seq++;
			seq = seq%4;
			holdIn( active, preparationTime );
			
		}*/
		holdIn( active, preparationTime );
		
			
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Receiver::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Receiver::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), out, receivedData % 10) ;
	return *this ;
}
