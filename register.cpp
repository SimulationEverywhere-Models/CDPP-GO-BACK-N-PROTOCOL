/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Ahmad Mizan
*
*  DATE: 28/10/2008
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "timer.h"        // class Receiver
#include "transmitter.h"        // class Subnet
#include "subnet.h"        // class Subnet2
#include "receiver.h"        // class Subnet2

void MainSimulator::registerNewAtomics()
{
 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Subnet>(), "Subnet" ) ;   
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transmitter>(), "Transmitter" ) ; 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Timer>(), "Timer" ) ; 
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Receiver>(), "Receiver" ) ; 
}