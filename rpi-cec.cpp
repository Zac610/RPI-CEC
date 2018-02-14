#include <libcec/cec.h>

#include <iostream>
using std::cout;
using std::endl;
using std::string;
#include <libcec/cecloader.h>

#include "bcm_host.h"

// The main loop will just continue until a ctrl-C is received
#include <signal.h>

enum LogLevel
{
	NO   = 0,
	ERR  = 1,
	INFO = 2
};

class mystreambuf: public std::streambuf {};
mystreambuf nostreambuf;
std::ostream nocout(&nostreambuf);
#define log(x) ((x <= gLogLevel)? std::cout : nocout)

const static string ProgramName = "Raspberry CEC Test";

// default values, can be override by parameters
LogLevel gLogLevel = NO;
bool gSingleMode = true; // false: display 

int gLastKeyCode = 0xffffffff;
bool gExitLoop = false;


void handleSignal(int signal)
{
	log(INFO) << "Received signal #" << signal << endl;
	gExitLoop = true;
}


//CEC::CBCecKeyPressType from cectypes.h
void on_keypress(void* not_used, const CEC::cec_keypress *msg)
{
	gLastKeyCode = static_cast<int>(msg->keycode); 

	if (gLogLevel > LogLevel::NO)
	{
		std::string key("default");
		switch( msg->keycode )
		{
			case CEC::CEC_USER_CONTROL_CODE_SELECT:{key="SELECT";break;}
			case CEC::CEC_USER_CONTROL_CODE_UP:{key="UP";break;}
			case CEC::CEC_USER_CONTROL_CODE_DOWN:{key="DOWN";break;}
			case CEC::CEC_USER_CONTROL_CODE_LEFT:{key="LEFT";break;}
			case CEC::CEC_USER_CONTROL_CODE_RIGHT:{key="RIGHT";break;}
			case CEC::CEC_USER_CONTROL_CODE_RIGHT_UP:{key="RIGHT_UP";break;}
			case CEC::CEC_USER_CONTROL_CODE_RIGHT_DOWN:{key="RIGHT_DOWN";break;}
			case CEC::CEC_USER_CONTROL_CODE_LEFT_UP:{key="LEFT_UP";break;}
			case CEC::CEC_USER_CONTROL_CODE_LEFT_DOWN:{key="LEFT_DOWN";break;}
			case CEC::CEC_USER_CONTROL_CODE_ROOT_MENU:{key="ROOT_MENU";break;}
			case CEC::CEC_USER_CONTROL_CODE_SETUP_MENU:{key="SETUP_MENU";break;}
			case CEC::CEC_USER_CONTROL_CODE_CONTENTS_MENU:{key="CONTENTS_MENU";break;}
			case CEC::CEC_USER_CONTROL_CODE_FAVORITE_MENU:{key="FAVORITE_MENU";break;}
			case CEC::CEC_USER_CONTROL_CODE_EXIT:{key="EXIT";break;}
			case CEC::CEC_USER_CONTROL_CODE_TOP_MENU:{key="TOP_MENU";break;}
			case CEC::CEC_USER_CONTROL_CODE_DVD_MENU:{key="DVD_MENU";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER_ENTRY_MODE:{key="NUMBER_ENTRY_MODE";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER11:{key="NUMBER11";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER12:{key="NUMBER12";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER0:{key="NUMBER0";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER1:{key="NUMBER1";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER2:{key="NUMBER2";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER3:{key="NUMBER3";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER4:{key="NUMBER4";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER5:{key="NUMBER5";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER6:{key="NUMBER6";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER7:{key="NUMBER7";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER8:{key="NUMBER8";break;}
			case CEC::CEC_USER_CONTROL_CODE_NUMBER9:{key="NUMBER9";break;}
			case CEC::CEC_USER_CONTROL_CODE_DOT:{key="DOT";break;}
			case CEC::CEC_USER_CONTROL_CODE_ENTER:{key="ENTER";break;}
			case CEC::CEC_USER_CONTROL_CODE_CLEAR:{key="CLEAR";break;}
			case CEC::CEC_USER_CONTROL_CODE_NEXT_FAVORITE:{key="NEXT_FAVORITE";break;}
			case CEC::CEC_USER_CONTROL_CODE_CHANNEL_UP:{key="CHANNEL_UP";break;}
			case CEC::CEC_USER_CONTROL_CODE_CHANNEL_DOWN:{key="CHANNEL_DOWN";break;}
			case CEC::CEC_USER_CONTROL_CODE_PREVIOUS_CHANNEL:{key="PREVIOUS_CHANNEL";break;}
			case CEC::CEC_USER_CONTROL_CODE_SOUND_SELECT:{key="SOUND_SELECT";break;}
			case CEC::CEC_USER_CONTROL_CODE_INPUT_SELECT:{key="INPUT_SELECT";break;}
			case CEC::CEC_USER_CONTROL_CODE_DISPLAY_INFORMATION:{key="DISPLAY_INFORMATION";break;}
			case CEC::CEC_USER_CONTROL_CODE_HELP:{key="HELP";break;}
			case CEC::CEC_USER_CONTROL_CODE_PAGE_UP:{key="PAGE_UP";break;}
			case CEC::CEC_USER_CONTROL_CODE_PAGE_DOWN:{key="PAGE_DOWN";break;}
			case CEC::CEC_USER_CONTROL_CODE_POWER:{key="POWER";break;}
			case CEC::CEC_USER_CONTROL_CODE_VOLUME_UP:{key="VOLUME_UP";break;}
			case CEC::CEC_USER_CONTROL_CODE_VOLUME_DOWN:{key="VOLUME_DOWN";break;}
			case CEC::CEC_USER_CONTROL_CODE_MUTE:{key="MUTE";break;}
			case CEC::CEC_USER_CONTROL_CODE_PLAY:{key="PLAY";break;}
			case CEC::CEC_USER_CONTROL_CODE_STOP:{key="STOP";break;}
			case CEC::CEC_USER_CONTROL_CODE_PAUSE:{key="PAUSE";break;}
			case CEC::CEC_USER_CONTROL_CODE_RECORD:{key="RECORD";break;}
			case CEC::CEC_USER_CONTROL_CODE_REWIND:{key="REWIND";break;}
			case CEC::CEC_USER_CONTROL_CODE_FAST_FORWARD:{key="FAST_FORWARD";break;}
			case CEC::CEC_USER_CONTROL_CODE_EJECT:{key="EJECT";break;}
			case CEC::CEC_USER_CONTROL_CODE_FORWARD:{key="FORWARD";break;}
			case CEC::CEC_USER_CONTROL_CODE_BACKWARD:{key="BACKWARD";break;}
			case CEC::CEC_USER_CONTROL_CODE_STOP_RECORD:{key="STOP_RECORD";break;}
			case CEC::CEC_USER_CONTROL_CODE_PAUSE_RECORD:{key="PAUSE_RECORD";break;}
			case CEC::CEC_USER_CONTROL_CODE_ANGLE:{key="ANGLE";break;}
			case CEC::CEC_USER_CONTROL_CODE_SUB_PICTURE:{key="SUB_PICTURE";break;}
			case CEC::CEC_USER_CONTROL_CODE_VIDEO_ON_DEMAND:{key="VIDEO_ON_DEMAND";break;}
			case CEC::CEC_USER_CONTROL_CODE_ELECTRONIC_PROGRAM_GUIDE:{key="ELECTRONIC_PROGRAM_GUIDE";break;}
			case CEC::CEC_USER_CONTROL_CODE_TIMER_PROGRAMMING:{key="TIMER_PROGRAMMING";break;}
			case CEC::CEC_USER_CONTROL_CODE_INITIAL_CONFIGURATION:{key="INITIAL_CONFIGURATION";break;}
			case CEC::CEC_USER_CONTROL_CODE_SELECT_BROADCAST_TYPE:{key="SELECT_BROADCAST_TYPE";break;}
			case CEC::CEC_USER_CONTROL_CODE_SELECT_SOUND_PRESENTATION:{key="SELECT_SOUND_PRESENTATION";break;}
			case CEC::CEC_USER_CONTROL_CODE_PLAY_FUNCTION:{key="PLAY_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_PAUSE_PLAY_FUNCTION:{key="PAUSE_PLAY_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_RECORD_FUNCTION:{key="RECORD_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_PAUSE_RECORD_FUNCTION:{key="PAUSE_RECORD_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_STOP_FUNCTION:{key="STOP_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_MUTE_FUNCTION:{key="MUTE_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_RESTORE_VOLUME_FUNCTION:{key="RESTORE_VOLUME_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_TUNE_FUNCTION:{key="TUNE_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_SELECT_MEDIA_FUNCTION:{key="SELECT_MEDIA_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_SELECT_AV_INPUT_FUNCTION:{key="SELECT_AV_INPUT_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_SELECT_AUDIO_INPUT_FUNCTION:{key="SELECT_AUDIO_INPUT_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_POWER_TOGGLE_FUNCTION:{key="POWER_TOGGLE_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_POWER_OFF_FUNCTION:{key="POWER_OFF_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_POWER_ON_FUNCTION:{key="POWER_ON_FUNCTION";break;}
			case CEC::CEC_USER_CONTROL_CODE_F1_BLUE:{key="F1_BLUE";break;}
			case CEC::CEC_USER_CONTROL_CODE_F2_RED:{key="F2_RED";break;}
			case CEC::CEC_USER_CONTROL_CODE_F3_GREEN:{key="F3_GREEN";break;}
			case CEC::CEC_USER_CONTROL_CODE_F4_YELLOW:{key="F4_YELLOW";break;}
			case CEC::CEC_USER_CONTROL_CODE_F5:{key="F5";break;}
			case CEC::CEC_USER_CONTROL_CODE_DATA:{key="DATA";break;}
			case CEC::CEC_USER_CONTROL_CODE_AN_RETURN:{key="AN_RETURN";break;}
			case CEC::CEC_USER_CONTROL_CODE_AN_CHANNELS_LIST:{key="AN_CHANNELS_LIST";break;}
			default: break;
		};
	
		log(INFO) << "on_keypress [" << msg->duration << "]: " << gLastKeyCode << " " << key << std::endl;
	}
	if (gSingleMode)
		gExitLoop = true;
		
}


int main(int argc, char* argv[])
{
	// Install the ctrl-C signal handler
	if( SIG_ERR == signal(SIGINT, handleSignal) )
	{
		std::cerr << "Failed to install the SIGINT signal handler\n";
		return -1;
	}

	if (argc > 1) // if invoked with parameters, assume verbose is requested
	{
		gLogLevel = INFO;
		gSingleMode = false;
	}
	
	log(INFO) << ProgramName << " starting..." << endl;
	
	// Initialise the graphics pipeline for the raspberry pi. Yes, this is necessary.
	bcm_host_init();

	// Set up the CEC config and specify the keypress callback function
	CEC::ICECCallbacks cec_callbacks;
	CEC::libcec_configuration cec_config;
	cec_config.Clear();
	cec_callbacks.Clear();
	cec_callbacks.keyPress	= &on_keypress;

	const std::string devicename("CECExample");
	devicename.copy(cec_config.strDeviceName, std::min(devicename.size(),13u) );

	cec_config.clientVersion	 = CEC::LIBCEC_VERSION_CURRENT;
	cec_config.bActivateSource = 0;
	cec_config.callbacks		   = &cec_callbacks;
	cec_config.deviceTypes.Add(CEC::CEC_DEVICE_TYPE_RECORDING_DEVICE);

	// Get a cec adapter by initialising the cec library
	CEC::ICECAdapter* cec_adapter = LibCecInitialise(&cec_config);
	if( !cec_adapter )
	{ 
		std::cerr << "Failed loading libcec.so\n"; 
		return -1; 
	}

	// Try to automatically determine the CEC devices 
	CEC::cec_adapter_descriptor devices[10];
	int8_t devices_found = cec_adapter->DetectAdapters(devices, 10, NULL); // TODO: deprecated, use DetectAdapters instead
	if( devices_found <= 0)
	{
		std::cerr << "Could not automatically determine the cec adapter devices\n";
		UnloadLibCec(cec_adapter);
		return -1;
	}
	else
	{
		log(INFO) << "found " << (int)devices_found << " devices" << endl;
		log(INFO) << " comm: " << devices[0].strComName << endl;
		log(INFO) << " path: " << devices[0].strComPath << endl;
	}

	// Open a connection to the zeroth CEC device
	if( !cec_adapter->Open(devices[0].strComName) )
	{		
		std::cerr << "Failed to open the CEC device on port " << devices[0].strComName << std::endl;
		UnloadLibCec(cec_adapter);
		return -1;
	}

	cout << "1 " << cec_adapter << endl;

	// Loop until ctrl-C occurs
	log(INFO) << "Ready." << endl;
	while( !gExitLoop ) // without while -> segmentation fault
	{
	 // nothing to do.  All happens in the CEC callback on another thread
		sleep(2);
	}

	// Close down and cleanup
	cec_adapter->Close();
	UnloadLibCec(cec_adapter);

	log(INFO) << ProgramName << " ended." << endl;

	return gLastKeyCode;
}

