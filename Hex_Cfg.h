//====================================================================
//Project Lynxmotion Phoenix
//Description: 
//    This is the hardware configuration file for the Hex Robot.
//  
//    This version of the Configuration file is set up to run on the
//    Lynxmotion BotboardDuino board, which is similiar to the Arduino Duemilanove
//
//    This version of configuration file assumes that the servos will be controlled
//    by a Lynxmotion Servo controller SSC-32 and the user is using a Lynxmotion 
//    PS2 to control the robot.
//
//Date: March 18, 2012
//Programmer: Kurt (aka KurtE)
//
//NEW IN V1.1 (2013-05-17)
//   - Support for Arduino Pro Mini on Bot Board (originally for Basic Atom Pro)
//NEW IN V1.0
//   - First Release
//
//====================================================================

//==================================================================================================================================
//==================================================================================================================================
//==================================================================================================================================
//[CONDITIONAL COMPILING] - COMMENT IF NOT WANTED
// Define other optional components to be included or not...

//comment if terminal monitor is not required
#define OPT_TERMINAL_MONITOR  

//====================================================================
#ifdef OPT_TERMINAL_MONITOR   // turning off terminal monitor will turn these off as well...
#define OPT_SSC_FORWARDER  // only useful if terminal monitor is enabled
#define OPT_FIND_SERVO_OFFSETS    // Only useful if terminal monitor is enabled
#endif

#define OPT_GPPLAYER

// Which type of control(s) do you want to compile in

#define SSCSerial         Serial3
#define MAESTROSerial     Serial2
#define DBGSerial         Serial1


#define USEPS2

//==================================================================================================================================
//==================================================================================================================================
//==================================================================================================================================
// CHR-3
//==================================================================================================================================
#define USE_SSC32
//#define	cSSC_BINARYMODE	1			// Define if your SSC-32 card supports binary mode.

//[SERIAL CONNECTIONS]

// Warning I will undefine some components as the non-megas don't have enough memory...
//#undef OPT_FIND_SERVO_OFFSETS 

#define cSSC_BAUD   38400   //SSC32 BAUD rate

// Maestro Device Number
#define MAESTRO 12

#define PT_PAN 2
#define PT_TILT 3

#define PT_ON_SSC32 

#define PAN_ON_SSC32 30
#define TILT_ON_SSC32 31


//--------------------------------------------------------------------
//[Arduino Mega Pin Numbers]
  #define SOUND_PIN       5   // Botboarduino JR pin number
  #define PS2_DAT         8        
  #define PS2_CMD         7
  #define PS2_SEL         6  // On the PS2 receiver this pin may be called ATT (attention)
  #define PS2_CLK         9
  #define HEADLIGHT      39
  #define VOLTSENSOR     A0

 
  #define STATUSLED      10
  

//====================================================================
//[ULTRASONIC PIN NUMBERS]
#define trigFront       30
#define echoFront       31
#define trigLeft        32
#define echoLeft        33
#define trigRight       35
#define echoRight       34
#define trigBack        37
#define echoBack        36

//====================================================================
//[VIDEO TRANSMIT PIN NUMBER]
#define VIDEOTRANSMIT  40 //relay for 5v arduino management of 12v transmitter

//====================================================================
//[SSC PIN NUMBERS]
#define cRRCoxaPin      0   //Rear Right leg Hip Horizontal
#define cRRFemurPin     1   //Rear Right leg Hip Vertical
#define cRRTibiaPin     2   //Rear Right leg Knee

#define cRMCoxaPin      4   //Middle Right leg Hip Horizontal
#define cRMFemurPin     5   //Middle Right leg Hip Vertical
#define cRMTibiaPin     6   //Middle Right leg Knee

#define cRFCoxaPin      8   //Front Right leg Hip Horizontal
#define cRFFemurPin     9   //Front Right leg Hip Vertical
#define cRFTibiaPin     10   //Front Right leg Knee

#define cLRCoxaPin      16   //Rear Left leg Hip Horizontal
#define cLRFemurPin     17   //Rear Left leg Hip Vertical
#define cLRTibiaPin     18   //Rear Left leg Knee

#define cLMCoxaPin      20   //Middle Left leg Hip Horizontal
#define cLMFemurPin     21   //Middle Left leg Hip Vertical
#define cLMTibiaPin     22   //Middle Left leg Knee

#define cLFCoxaPin      24   //Front Left leg Hip Horizontal
#define cLFFemurPin     25   //Front Left leg Hip Vertical
#define cLFTibiaPin     26   //Front Left leg Knee


//--------------------------------------------------------------------
//[MIN/MAX ANGLES]
#define cRRCoxaMin1     -650      //Mechanical limits of the Right Rear Leg
#define cRRCoxaMax1     650
#define cRRFemurMin1    -1050
#define cRRFemurMax1    750
#define cRRTibiaMin1    -530
#define cRRTibiaMax1    900

#define cRMCoxaMin1     -650      //Mechanical limits of the Right Middle Leg
#define cRMCoxaMax1     650
#define cRMFemurMin1    -1050
#define cRMFemurMax1    750
#define cRMTibiaMin1    -530
#define cRMTibiaMax1    900

#define cRFCoxaMin1     -650      //Mechanical limits of the Right Front Leg
#define cRFCoxaMax1     650
#define cRFFemurMin1    -1050
#define cRFFemurMax1    750
#define cRFTibiaMin1    -530
#define cRFTibiaMax1    900

#define cLRCoxaMin1     -650      //Mechanical limits of the Left Rear Leg
#define cLRCoxaMax1     650
#define cLRFemurMin1    -1050
#define cLRFemurMax1    750
#define cLRTibiaMin1    -530
#define cLRTibiaMax1    900

#define cLMCoxaMin1     -650      //Mechanical limits of the Left Middle Leg
#define cLMCoxaMax1     650
#define cLMFemurMin1    -1050
#define cLMFemurMax1    750
#define cLMTibiaMin1    -530
#define cLMTibiaMax1    900


#define cLFCoxaMin1     -650      //Mechanical limits of the Left Front Leg
#define cLFCoxaMax1     650
#define cLFFemurMin1    -1050
#define cLFFemurMax1    750
#define cLFTibiaMin1    -530
#define cLFTibiaMax1    900


//--------------------------------------------------------------------
//[LEG DIMENSIONS]
//Universal dimensions for each leg in mm
#define cXXCoxaLength     29    // This is for CH3-R with Type 3 legs
#define cXXFemurLength    57
#define cXXTibiaLength    141

#define cRRCoxaLength     cXXCoxaLength	    //Right Rear leg
#define cRRFemurLength    cXXFemurLength
#define cRRTibiaLength    cXXTibiaLength

#define cRMCoxaLength     cXXCoxaLength	    //Right middle leg
#define cRMFemurLength    cXXFemurLength
#define cRMTibiaLength    cXXTibiaLength

#define cRFCoxaLength     cXXCoxaLength	    //Rigth front leg
#define cRFFemurLength    cXXFemurLength
#define cRFTibiaLength    cXXTibiaLength

#define cLRCoxaLength     cXXCoxaLength	    //Left Rear leg
#define cLRFemurLength    cXXFemurLength
#define cLRTibiaLength    cXXTibiaLength

#define cLMCoxaLength     cXXCoxaLength	    //Left middle leg
#define cLMFemurLength    cXXFemurLength
#define cLMTibiaLength    cXXTibiaLength

#define cLFCoxaLength     cXXCoxaLength	    //Left front leg
#define cLFFemurLength    cXXFemurLength
#define cLFTibiaLength    cXXTibiaLength


//--------------------------------------------------------------------
//[BODY DIMENSIONS]
#define cRRCoxaAngle1   -600   //Default Coxa setup angle, decimals = 1
#define cRMCoxaAngle1    0      //Default Coxa setup angle, decimals = 1
#define cRFCoxaAngle1    600      //Default Coxa setup angle, decimals = 1
#define cLRCoxaAngle1    -600   //Default Coxa setup angle, decimals = 1
#define cLMCoxaAngle1    0      //Default Coxa setup angle, decimals = 1
#define cLFCoxaAngle1    600      //Default Coxa setup angle, decimals = 1

#define cRROffsetX      -69     //Distance X from center of the body to the Right Rear coxa
#define cRROffsetZ      119     //Distance Z from center of the body to the Right Rear coxa
#define cRMOffsetX      -138    //Distance X from center of the body to the Right Middle coxa
#define cRMOffsetZ      0       //Distance Z from center of the body to the Right Middle coxa
#define cRFOffsetX      -69     //Distance X from center of the body to the Right Front coxa
#define cRFOffsetZ      -119    //Distance Z from center of the body to the Right Front coxa

#define cLROffsetX      69      //Distance X from center of the body to the Left Rear coxa
#define cLROffsetZ      119     //Distance Z from center of the body to the Left Rear coxa
#define cLMOffsetX      138     //Distance X from center of the body to the Left Middle coxa
#define cLMOffsetZ      0       //Distance Z from center of the body to the Left Middle coxa
#define cLFOffsetX      69      //Distance X from center of the body to the Left Front coxa
#define cLFOffsetZ      -119    //Distance Z from center of the body to the Left Front coxa

//--------------------------------------------------------------------
//[START POSITIONS FEET]
#define cHexInitXZ	 80
#define CHexInitXZCos60  40        // COS(60) = .5
#define CHexInitXZSin60  69    // sin(60) = .866
#define CHexInitY	80 //30


#define cRRInitPosX     CHexInitXZCos60      //Start positions of the Right Rear leg
#define cRRInitPosY     CHexInitY
#define cRRInitPosZ     CHexInitXZSin60

#define cRMInitPosX     cHexInitXZ      //Start positions of the Right Middle leg
#define cRMInitPosY     CHexInitY
#define cRMInitPosZ     0

#define cRFInitPosX     CHexInitXZCos60      //Start positions of the Right Front leg
#define cRFInitPosY     CHexInitY
#define cRFInitPosZ     -CHexInitXZSin60

#define cLRInitPosX     CHexInitXZCos60      //Start positions of the Left Rear leg
#define cLRInitPosY     CHexInitY
#define cLRInitPosZ     CHexInitXZSin60

#define cLMInitPosX     cHexInitXZ      //Start positions of the Left Middle leg
#define cLMInitPosY     CHexInitY
#define cLMInitPosZ     0

#define cLFInitPosX     CHexInitXZCos60      //Start positions of the Left Front leg
#define cLFInitPosY     CHexInitY
#define cLFInitPosZ     -CHexInitXZSin60
//--------------------------------------------------------------------


