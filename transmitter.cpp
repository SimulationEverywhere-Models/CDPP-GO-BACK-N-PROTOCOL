/*******************************************************************
*
*  DESCRIPTION: Atomic Model Transmitter
*
*  AUTHOR: Ahmad Mizan 
*  
*  DATE: 28/10/2008
*
*******************************************************************/

/** include files **/
#include "transmitter.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )


/** public functions **/

/*******************************************************************
* Function Name: Transmitter
* Description: 
********************************************************************/
Transmitter::Transmitter( const string &name )
: Atomic( name )
, startTx( addInputPort( "startTx" ) )
, sentData( addOutputPort( "sentData" ) )
, sentPkt( addOutputPort( "sentPkt" ) )
, rxSeq( addOutputPort( "rxSeq" ) )
, rxAck( addInputPort( "rxAck" ) )
, t0Trig( addOutputPort( "t0Trig" ) )
, t1Trig( addOutputPort( "t1Trig" ) )
, t2Trig( addOutputPort( "t2Trig" ) )
, t3Trig( addOutputPort( "t3Trig" ) )
, t0TimeOut( addInputPort( "t0TimeOut" ) )
, t1TimeOut( addInputPort( "t1TimeOut" ) )
, t2TimeOut( addInputPort( "t2TimeOut" ) )
, t3TimeOut( addInputPort( "t3TimeOut" ) )
, resetTimers( addOutputPort( "resetTimers" ) )
, txTime(0, 0, 20, 0)
, pTime(0, 0, 0, 1)
, rTime(0, 0, 0, 1)
{
	string time( MainSimulator::Instance().getParameter( description(), "txTime" ) );
	if( time != "" )
		txTime = time ;
		
	string time1( MainSimulator::Instance().getParameter( description(), "pTime" ) );
	if( time1 != "" )
		pTime = time1 ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Transmitter::initFunction()
{
	newFram = true;
	txSeq=0;
	this-> passivate();
	expectedSeq = 0;
	counter = 0;
	pktNum=0;
	doResetTimers=false;
	sending = false;
	//holdIn(passive, Time::pTime);
	//startTx = false;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Transmitter::externalFunction( const ExternalMessage &msg )
{
	if((msg.port() == t0TimeOut || msg.port() == t1TimeOut || msg.port() == t2TimeOut || msg.port() == t3TimeOut) && msg.value()!=0 && this->state() == passive)
	{
		doResetTimers=true;
		counter=0;
		if(pktNum<totalPktNum)
			pktNum -=3;	
		//sendOutput( msg.time(), resetTimers, 1 ) ;
		//this->passivate();
		//sending = true;
		holdIn(active, rTime);
	}
	else if( msg.port() == rxAck && msg.value()==expectedSeq)
	{
		expectedSeq++;
		receivedSeq = msg.value();
		expectedSeq=expectedSeq%4;
		counter--;
		sending = true;
		ackReceived = true;
		//this->passivate();

		//holdIn(active, txTime ); 
	}
	
	else if( msg.port() == startTx  && this->state() == passive && msg.value()>0 && newFram==true)
	{	
		newFram = false;
		txSeq=0;
		expectedSeq = 0;
		counter = 0;
		pktNum=0;
		totalPktNum=msg.value();
		doResetTimers=false;
		sending = true;
		holdIn(active, txTime );
	}
	
	//if( msg.port() == startTx  && this->state() == active)
	//{	
	//	holdIn(active, txTime ); 
	//}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Transmitter::internalFunction( const InternalMessage & )
{

		if(state()== passive && counter<3 /*&& sending == true */&& pktNum<totalPktNum )
		{
			sending = true;
			holdIn(active , txTime );
		}
		//else if(state()==passive && doResetTimers==true)
			//holdIn(active , pTime );
		else if(state()==passive && sending == false)
			holdIn(passive , pTime );
//			passivate();
		else if(state()==active)
			holdIn(passive,pTime);
		else if ((counter>3 || counter == 3)&& pktNum<totalPktNum  )
		{
			holdIn(passive , pTime );
//			passivate();
			sending = false;
		}
		else if (pktNum>totalPktNum || pktNum==totalPktNum)
		{
			holdIn(passive , pTime );
//			passivate();
			sending = false;
			newFram = true;
		}
		else if (ackReceived == true)
			holdIn(passive , pTime );	
			
	//	this->passivate();
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Transmitter::outputFunction( const InternalMessage &msg )
{

		if(doResetTimers==true && state()==active)
		{
			sendOutput( msg.time(), resetTimers, 1 ) ;
			doResetTimers=false;
			sending = true;
					//passivate();
		}
		else if(state()==active && sending == true)
		{
			txSeq = pktNum%4;
			sendOutput( msg.time(), sentData, pktNum*10+txSeq ) ;
			sendOutput( msg.time(), sentPkt, pktNum ) ; //for demo
			
			
			if(txSeq==0)
			sendOutput( msg.time(), t0Trig, 1) ;
			else if(txSeq==1)
			sendOutput( msg.time(), t1Trig, 1) ;
			else if(txSeq==2)
			sendOutput( msg.time(), t2Trig, 1) ;
			else if(txSeq==3)
			sendOutput( msg.time(), t3Trig, 1) ;
				
//			txSeq++;
//			txSeq = txSeq%4;
			counter++;
			pktNum++;
	
		}
		else if(ackReceived == true)
		{
			sendOutput( msg.time(), rxSeq, receivedSeq  ) ;
			ackReceived = false;
			
		}
		
//	if(state()==passive && counter>0)
//	{
//		counter--;
//		sendOutput( msg.time(), sentData, counter ) ;
		
//	}
	return *this ;
}

