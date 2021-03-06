//====================================================================
//Project Lynxmotion Phoenix
//Description: Phoenix, control file.
//The control input subroutine for the phoenix software is placed in this file.
//Can be used with V2.0 and above
//Configuration version: V1.0
//Date: 25-10-2009
//Programmer: Jeroen Janssen (aka Xan)
//             Kurt Eckhardt (aka KurtE) - converted to c ported to Arduino...
//
//Hardware setup: PS2 version
// 
//NEW IN V1.0
//- First Release
//
//Walk method 1:
//- Left StickWalk/Strafe
//- Right StickRotate
//
//Walk method 2:
//- Left StickDisable
//- Right StickWalk/Rotate
//
//
//PS2 CONTROLS:
//[Common Controls]
//- StartTurn on/off the bot
//- L1Toggle Shift mode
//- L2Toggle Rotate mode
//- CircleToggle Single leg mode
//   - Square        Toggle Balance mode
//- TriangleMove body to 35 mm from the ground (walk pos) 
//and back to the ground
//- D-Pad upBody up 10 mm
//- D-Pad downBody down 10 mm
//- D-Pad leftdecrease speed with 50mS
//- D-Pad rightincrease speed with 50mS
//
//[Walk Controls]
//- selectSwitch gaits
//- Left Stick(Walk mode 1) Walk/Strafe
// (Walk mode 2) Disable
//- Right Stick(Walk mode 1) Rotate, 
//(Walk mode 2) Walk/Rotate
//- R1Toggle Double gait travel speed
//- R2Toggle Double gait travel length
//
//[Shift Controls]
//- Left StickShift body X/Z
//- Right StickShift body Y and rotate body Y
//
//[Rotate Controls]
//- Left StickRotate body X/Z
//- Right StickRotate body Y
//
//[Single leg Controls]
//- selectSwitch legs
//- Left StickMove Leg X/Z (relative)
//- Right StickMove Leg Y (absolute)
//- R2Hold/release leg position
//
//[GP Player Controls]
//- selectSwitch Sequences
//- R2Start Sequence
//
//====================================================================
// [Include files]
#if ARDUINO>99
#include <Arduino.h> // Arduino 1.0
#else
#include <Wprogram.h> // Arduino 0022
#endif
#include "Hex_Globals.h"
#ifdef USEPS2
#include <PS2X_lib.h>

//[CONSTANTS]
#define WALKMODE          0
#define TRANSLATEMODE     1
#define ROTATEMODE        2
#define SINGLELEGMODE     3
#define GPPLAYERMODE      4


#define cTravelDeadZone 4      //The deadzone for the analog input from the remote
#define  MAXPS2ERRORCNT  5     // How many times through the loop will we go before shutting off robot?

//=============================================================================
// Global - Local to this file only...
//=============================================================================
PS2X ps2x; // create PS2 Controller Class


// Define an instance of the Input Controller...
InputController  g_InputController;       // Our Input controller 


static short      g_BodyYOffset; 
static short      g_sPS2ErrorCnt;
static short       g_BodyYShift;
static byte        ControlMode;
static bool        DoubleHeightOn;
static bool        DoubleTravelOn;
static bool        WalkMethod;
byte            GPSeq;             //Number of the sequence

// this variable helps debounce certain states on ControlState
// Video Enable is not allowed to change quicker than one second interval
// Headlight Enable is not allowed to change quicker than one second interval
long lastToggleTime = -1;

// General purpose variable to keep track of timing
long inputTimerStart = 0;

// this variable helps debounce ultrasonic state on ControlState
long lastUltrasonicToggleTime = -1;

// some external or forward function references.
extern void MSound(uint8_t _pin, byte cNotes, ...);
extern void PS2TurnRobotOff(void);

//==============================================================================
// This is The function that is called by the Main program to initialize
//the input controller, which in this case is the PS2 controller
//process any commands.
//==============================================================================

// If both PS2 and XBee are defined then we will become secondary to the xbee
void InputController::Init(void)
{
    int error;

    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);  // Setup gamepad (clock, command, attention, data) pins

    g_BodyYOffset = 65;  // 0 - Devon wanted...
    g_BodyYShift = 0;
    g_sPS2ErrorCnt = 0;  // error count

    ControlMode = WALKMODE;
    DoubleHeightOn = false;
    DoubleTravelOn = false;
    WalkMethod = false;
 
    g_ControlState.SpeedControl = 100;    // Sort of migrate stuff in from Devon.
    g_ControlState.HEADLIGHTS = false;
    g_ControlState.VIDEO_TRX = false;

    g_ControlState.UseUltrasonics = false;
}

//==============================================================================
// This function is called by the main code to tell us when it is about to
// do a lot of bit-bang outputs and it would like us to minimize any interrupts
// that we do while it is active...
//==============================================================================
void InputController::AllowControllerInterrupts(boolean fAllow)
{
// We don't need to do anything...
}

//==============================================================================
// This is The main code to input function to read inputs from the PS2 and then
//process any commands.
//==============================================================================
void InputController::ControlInput(void)
{
    //Start time for debouncing some buttons
    inputTimerStart = millis();

    if(lastToggleTime == -1)
    {
      lastToggleTime = inputTimerStart;
    }

    if(lastUltrasonicToggleTime == -1)
    {
      lastUltrasonicToggleTime = inputTimerStart;
    }
    
    // Then try to receive a packet of information from the PS2.
    ps2x.read_gamepad();          //read ps-2 controller

    // Wish the library had a valid way to verify that the read_gamepad succeeded... Will hack for now
    if ((ps2x.Analog(1) & 0xf0) == 0x70) {
        // In an analog mode so should be OK...
        g_sPS2ErrorCnt = 0;    // clear out error count...
        
        if (ps2x.ButtonPressed(PSB_START)) {// OK lets try "0" button for Start. 
            if (g_ControlState.fHexOn) 
            {
                PS2TurnRobotOff();
            } 
            else 
            {
                //Turn on
                g_ControlState.fHexOn = 1;
            }
        }

        // CODE ADDED BY MGGORDON AND DGREENAWAY
        // [non Robot Related Common functions]
        //
        //Pan video camera servo right
        if (ps2x.Button(PSB_PAD_RIGHT)) {
          g_ControlState.PT_PAD_RIGHT = true;
          g_ControlState.PT_PAD_LEFT = false;
        }
        else {
          g_ControlState.PT_PAD_RIGHT = false;
        }

        //Pan video camera servo left
        if (ps2x.Button(PSB_PAD_LEFT)) {
          g_ControlState.PT_PAD_LEFT = true;
          g_ControlState.PT_PAD_RIGHT = false;
        }
        else {
          g_ControlState.PT_PAD_LEFT = false;
        }

        //Pan video camera servo up
        if (ps2x.Button(PSB_PAD_UP)) {
          g_ControlState.PT_PAD_UP = true;
          g_ControlState.PT_PAD_DOWN = false;
        } 
        else {
          g_ControlState.PT_PAD_UP = false;
        }

        //Tilt video camera servo down
        if (ps2x.Button(PSB_PAD_DOWN)) 
        {        
          g_ControlState.PT_PAD_DOWN = true;
          g_ControlState.PT_PAD_UP = false;
        }
        else {
          g_ControlState.PT_PAD_DOWN = false;
        }

        long durationSinceLastToggle = inputTimerStart - lastToggleTime;
        if(durationSinceLastToggle > 1000) 
        {
          //Turn Video Camera On/Off
          if (ps2x.Button(PSB_CROSS))
          {
            MSound (SOUND_PIN, 2, 50, 2000, 50, 2250);
            g_ControlState.VIDEO_TRX = !g_ControlState.VIDEO_TRX;
            lastToggleTime = millis();
          }

          //Turn Headlights On/Off
          if (ps2x.Button(PSB_SQUARE))
          {
            MSound (SOUND_PIN, 2, 50, 2000, 50, 2250);
            g_ControlState.HEADLIGHTS = !g_ControlState.HEADLIGHTS;
            lastToggleTime = millis();
          }
        }

        long durationSinceLastUltrasonicToggle = inputTimerStart - lastUltrasonicToggleTime;
        if(durationSinceLastUltrasonicToggle > 1000) 
        {
          //Turn Video Camera On/Off
          if (ps2x.Button(PSB_CIRCLE))
          {
            MSound (SOUND_PIN, 2, 50, 2000, 50, 2250);
            g_ControlState.UseUltrasonics = !g_ControlState.UseUltrasonics;
            lastUltrasonicToggleTime = millis();
          }
        }

        // END CODE ADDED BY MGGORDON AND DGREENAWAY

        if (g_ControlState.fHexOn) {
            // [SWITCH MODES]
    
             //Translate mode
            if (ps2x.ButtonPressed(PSB_L1)) {// L1 Button Test
                MSound(SOUND_PIN, 1, 50, 2000);  //sound SOUND_PIN, [50\4000]
                if (ControlMode != TRANSLATEMODE )
                    ControlMode = TRANSLATEMODE;
                else {
                    if (g_ControlState.SelectedLeg==255) 
                        ControlMode = WALKMODE;
                    else
                        ControlMode = SINGLELEGMODE;
                }
            }
  
            //Rotate mode
            if (ps2x.ButtonPressed(PSB_L2)) {    // L2 Button Test
                MSound(SOUND_PIN, 1, 50, 2000);  //sound SOUND_PIN, [50\4000]
                if (ControlMode != ROTATEMODE)
                    ControlMode = ROTATEMODE;
                else {
                    if (g_ControlState.SelectedLeg == 255) 
                        ControlMode = WALKMODE;
                    else
                        ControlMode = SINGLELEGMODE;
                }
            }
    
            //Single leg mode fNO
//            if (ps2x.ButtonPressed(PSB_CIRCLE)) {// O - Circle Button Test
//                if (abs(g_ControlState.TravelLength.x)<cTravelDeadZone && abs(g_ControlState.TravelLength.z)<cTravelDeadZone 
//                        && abs(g_ControlState.TravelLength.y*2)<cTravelDeadZone )   {
//                    //Sound SOUND_PIN,[50\4000]
//                    if (ControlMode != SINGLELEGMODE) {
//                        ControlMode = SINGLELEGMODE;
//                            if (g_ControlState.SelectedLeg == 255)  //Select leg if none is selected
//                                g_ControlState.SelectedLeg=cRF; //Startleg
//                    } else {
//                        ControlMode = WALKMODE;
//                        g_ControlState.SelectedLeg=255;
//                    }
//                }
//            }      

//#ifdef OPT_GPPLAYER
//            // GP Player Mode X
//            if (ps2x.ButtonPressed(PSB_CROSS)) { // X - Cross Button Test
//                MSound(SOUND_PIN, 1, 50, 2000);  //sound SOUND_PIN, [50\4000]
//                if (ControlMode != GPPLAYERMODE) {
//                    ControlMode = GPPLAYERMODE;
//                    GPSeq=0;
//                } else
//                    ControlMode = WALKMODE;
//            }
//#endif // OPT_GPPLAYER

            //Stand up, sit down  
            if (ps2x.ButtonPressed(PSB_TRIANGLE)) { // Triangle - Button Test
                if (g_BodyYOffset>0) 
                    g_BodyYOffset = 0;
                else
                    g_BodyYOffset = 100;
            }
            
            //[Common functions]
            //Switch Balance mode on/off 
//            if (ps2x.ButtonPressed(PSB_SQUARE)) { // Square Button Test
//                g_ControlState.BalanceMode = !g_ControlState.BalanceMode;
//                if (g_ControlState.BalanceMode) {
//                    MSound(SOUND_PIN, 1, 250, 1500);  
//                } else {
//                    MSound(SOUND_PIN, 2, 100, 2000, 50, 4000);
//                }
//            }

            //Enable Ultrasonic Sensing
            if (ps2x.Analog(PSS_RX)== 0 && ps2x.Analog(PSS_LX) == 0 && ps2x.Analog(PSS_RY) == 0 && ps2x.Analog(PSS_LY) == 0){
              g_ControlState.UseUltrasonics = true; 
            }

            //[Walk functions]
            if (ControlMode == WALKMODE) {
                //Switch gaits
                if (ps2x.ButtonPressed(PSB_SELECT)            // Select Button Test
                        && abs(g_ControlState.TravelLength.x)<cTravelDeadZone //No movement
                        && abs(g_ControlState.TravelLength.z)<cTravelDeadZone 
                        && abs(g_ControlState.TravelLength.y*2)<cTravelDeadZone  ) 
                {
                    g_ControlState.GaitType = g_ControlState.GaitType+1;                    // Go to the next gait...
                    if (g_ControlState.GaitType < NUM_GAITS) {                 // Make sure we did not exceed number of gaits...
                        MSound(SOUND_PIN, 1, 50, 2000);  //sound SOUND_PIN, [50\4000]
                    } else {
                        MSound (SOUND_PIN, 2, 50, 2000, 50, 2250); 
                        g_ControlState.GaitType = 0;
                    }
                    GaitSelect();
                }
  
                //Double leg lift height
                if (ps2x.ButtonPressed(PSB_R1)) { // R1 Button Test
                    MSound(SOUND_PIN, 1, 50, 2000);  //sound SOUND_PIN, [50\4000]
                    DoubleHeightOn = !DoubleHeightOn;
                    if (DoubleHeightOn)
                        g_ControlState.LegLiftHeight = 80;
                    else
                        g_ControlState.LegLiftHeight = 50;
                }
  
                //Double Travel Length
                if (ps2x.ButtonPressed(PSB_R2)) {// R2 Button Test
                    MSound (SOUND_PIN, 1, 50, 2000);  //sound SOUND_PIN, [50\4000]
                    DoubleTravelOn = !DoubleTravelOn;
                }
  
                // Switch between Walk method 1 && Walk method 2
                if (ps2x.ButtonPressed(PSB_R3)) { // R3 Button Test
                    MSound (SOUND_PIN, 1, 50, 2000);  
                    WalkMethod = !WalkMethod;
                }
  
                //Walking
                if (WalkMethod)  //(Walk Methode) 
                    g_ControlState.TravelLength.z = (ps2x.Analog(PSS_RY)-128); //Right Stick Up/Down  

                else {
                    g_ControlState.TravelLength.x = -(ps2x.Analog(PSS_LX) - 128);
                    g_ControlState.TravelLength.z = (ps2x.Analog(PSS_LY) - 128);
                }

                if (!DoubleTravelOn) {  //(Double travel length)
                    g_ControlState.TravelLength.x = g_ControlState.TravelLength.x/2;
                    g_ControlState.TravelLength.z = g_ControlState.TravelLength.z/2;
                }

                g_ControlState.TravelLength.y = -(ps2x.Analog(PSS_RX) - 128)/4; //Right Stick Left/Right 
            }

            //[Translate functions]
            g_BodyYShift = 0;
            if (ControlMode == TRANSLATEMODE) {
                g_ControlState.BodyPos.x = (ps2x.Analog(PSS_LX) - 128)/2;
                g_ControlState.BodyPos.z = -(ps2x.Analog(PSS_LY) - 128)/3;
                g_ControlState.BodyRot1.y = (ps2x.Analog(PSS_RX) - 128)*2;
                g_BodyYShift = (-(ps2x.Analog(PSS_RY) - 128)/2);
            }

            //[Rotate functions]
            if (ControlMode == ROTATEMODE) {
                g_ControlState.BodyRot1.x = (ps2x.Analog(PSS_LY) - 128);
                g_ControlState.BodyRot1.y = (ps2x.Analog(PSS_RX) - 128)*2;
                g_ControlState.BodyRot1.z = (ps2x.Analog(PSS_LX) - 128);
                g_BodyYShift = (-(ps2x.Analog(PSS_RY) - 128)/2);
            }

            //[Single leg functions]
            if (ControlMode == SINGLELEGMODE) {
                //Switch leg for single leg control
                if (ps2x.ButtonPressed(PSB_SELECT)) { // Select Button Test
                    MSound (SOUND_PIN, 1, 50, 2000);  
                    if (g_ControlState.SelectedLeg<5)
                        g_ControlState.SelectedLeg = g_ControlState.SelectedLeg+1;
                    else
                        g_ControlState.SelectedLeg=0;
                }

                g_ControlState.SLLeg.x= (ps2x.Analog(PSS_LX) - 128)/2; //Left Stick Right/Left
                g_ControlState.SLLeg.y= (ps2x.Analog(PSS_RY) - 128)/10; //Right Stick Up/Down
                g_ControlState.SLLeg.z = (ps2x.Analog(PSS_LY) - 128)/2; //Left Stick Up/Down

                // Hold single leg in place
                if (ps2x.ButtonPressed(PSB_R2)) { // R2 Button Test
                    MSound (SOUND_PIN, 1, 50, 2000);  
                    g_ControlState.fSLHold = !g_ControlState.fSLHold;
                }
            }

#ifdef OPT_GPPLAYER
            //[GPPlayer functions]
//            if (ControlMode == GPPLAYERMODE) {
//
//                //Switch between sequences
//                if (ps2x.ButtonPressed(PSB_SELECT)) { // Select Button Test
//                    if (!g_ServoDriver.FIsGPSeqActive() ) {
//                        if (GPSeq < 5) {  //Max sequence
//                            MSound (SOUND_PIN, 1, 50, 1500);  //sound SOUND_PIN, [50\3000]
//                            GPSeq = GPSeq+1;
//                        } else {
//                            MSound (SOUND_PIN, 2, 50, 2000, 50, 2250);//Sound SOUND_PIN,[50\4000, 50\4500]
//                            GPSeq=0;
//                        }
//                    }
//                }
//                //Start Sequence
//                if (ps2x.ButtonPressed(PSB_R2))// R2 Button Test
//                    g_ServoDriver.GPStartSeq(GPSeq);
//            }
#endif // OPT_GPPLAYER

            //Calculate walking time delay
            g_ControlState.InputTimeDelay = 128 - max(max(abs(ps2x.Analog(PSS_LX) - 128), abs(ps2x.Analog(PSS_LY) - 128)), abs(ps2x.Analog(PSS_RX) - 128));
        }
  
        //Calculate g_ControlState.BodyPos.y
        g_ControlState.BodyPos.y = max(g_BodyYOffset + g_BodyYShift,  0);
    } 
    else 
    {
      // We may have lost the PS2... See what we can do to recover...
      if (g_sPS2ErrorCnt < MAXPS2ERRORCNT)
          g_sPS2ErrorCnt++;    // Increment the error count and if to many errors, turn off the robot.
      else if (g_ControlState.fHexOn)
          PS2TurnRobotOff();
       
       //This line is only required for use with older version of the PS2 library.
       //ps2x.reconfig_gamepad();
    }
}

//==============================================================================
// PS2TurnRobotOff - code used couple of places so save a little room...
//==============================================================================
void PS2TurnRobotOff(void)
{
   //Turn off
    g_ControlState.BodyPos.x = 0;
    g_ControlState.BodyPos.y = 0;
    g_ControlState.BodyPos.z = 0;
    g_ControlState.BodyRot1.x = 0;
    g_ControlState.BodyRot1.y = 0;
    g_ControlState.BodyRot1.z = 0;
    g_ControlState.TravelLength.x = 0;
    g_ControlState.TravelLength.z = 0;
    g_ControlState.TravelLength.y = 0;
    g_BodyYOffset = 0;
    g_BodyYShift = 0;
    g_ControlState.SelectedLeg = 255;
    g_ControlState.fHexOn = 0;
}


#endif //USEPS2


