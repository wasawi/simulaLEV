#include "pmThreadedOscReceiver.h"

//--------------------------
pmThreadedOscReceiver::pmThreadedOscReceiver()
{
	threadSleepMs=1;
	verbose = false;
	oscPort = 0;
	filterAddress = "";
	
}                       


//--------------------------
pmThreadedOscReceiver::~pmThreadedOscReceiver()
{
	stop();
}

//--------------------------
void pmThreadedOscReceiver::setup(int _oscPort, string _filter)
{
	ofThread::startThread(true, false);   // blocking, verbose
	oscPort			= _oscPort;
	filterAddress	= _filter;
	ofxOscReceiver::setup(oscPort);
    
    printf("oscRecThread :: setup at input port %d\n",_oscPort);
}

//--------------------------
void pmThreadedOscReceiver::stop()
{
	stopThread();
}

//--------------------------
void pmThreadedOscReceiver::threadedFunction()
{	
	while( isThreadRunning() != 0 )
	{        
		// OSC 
		// check for waiting messages
		//while(ofxOscReceiver::hasWaitingMessages() )
		if(ofxOscReceiver::hasWaitingMessages() )
		{
			// get the next message
			ofxOscMessage m;
			ofxOscReceiver::getNextMessage( &m );
			
				pmOscMessage pmM;
				pmM.address = m.getAddress();
				if(m.getArgType(0)==OFXOSC_TYPE_FLOAT)
				{
					pmM.value = m.getArgAsFloat(0);
				}

                if(verbose) printf("pmThreadOsc :: new OscMessage In %s :: %f \n",pmM.address.c_str(),pmM.value);

				ofNotifyEvent(newOscMessage,pmM,this);
			
		}
    
		ofSleepMillis(threadSleepMs);
	}
}

//--------------------------
void pmThreadedOscReceiver::setThreadSleepMs(int ms)
{
	threadSleepMs = ms;
}

//--------------------------
void pmThreadedOscReceiver::setVerbose(bool b)
{
	verbose = b;
}
//--------------------------
void pmThreadedOscReceiver::setAddressFilter(string s)
{
	filterAddress = s;
}
//--------------------------
void pmThreadedOscReceiver::draw()
{
	
}

	
