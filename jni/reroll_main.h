#ifndef

#include "drive/DriveControl.h"
#include "relay/Relay.h"
#include "GyverLibs/Encoder.h"
#include "GyverLibs/GyverButton.h"

class Reloll_main{
	private:
		Relay _drv_rly;
		DriveControl _drv;
		
	public:
		Reroll_main();
		void update();
	
};

#endif
