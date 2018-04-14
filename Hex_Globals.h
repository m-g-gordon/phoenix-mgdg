//==============================================================================
// GLOBALS - The main global definitions for the CPhenix program - still needs
//		to be cleaned up.
// This program assumes that the main files were compiled as C files
//==============================================================================
#ifndef _HEX_GLOBALS_H_
#define _HEX_GLOBALS_H_
#include <stdarg.h>

#include "Hex_Cfg.h"
#include "PololuMaestro.h"
#include "ServoDriver.h"
#include "InputController.h"
//=============================================================================
//[CONSTANTS]
//=============================================================================
#define BUTTON_DOWN 0
#define BUTTON_UP 	1

#define	c1DEC		10
#define	c2DEC		100
#define	c4DEC		10000
#define	c6DEC		1000000

#define	cRR			0
#define	cRM			1
#define	cRF			2
#define	cLR			3
#define	cLM			4
#define	cLF			5

#define	WTIMERTICSPERMSMUL  	64	// BAP28 is 16mhz need a multiplyer and divider to make the conversion with /8192
#define WTIMERTICSPERMSDIV  	125 // 
#define USEINT_TIMERAV


#define NUM_GAITS    5
extern void GaitSelect(void);
extern short SmoothControl (short CtrlMoveInp, short CtrlMoveOut, byte CtrlDivider);


//-----------------------------------------------------------------------------
// Define global class objects
//-----------------------------------------------------------------------------
#ifndef PT_ON_SSC32
extern MicroMaestro     g_PTServoDriver;           // our global pan and tilt servo driver class
#endif

extern ServoDriver      g_ServoDriver;           // our global servo driver class
extern InputController  g_InputController;       // Our Input controller 
extern INCONTROLSTATE   g_ControlState;		 // State information that controller changes

//-----------------------------------------------------------------------------
// Define Global variables
//-----------------------------------------------------------------------------
extern boolean          g_fDebugOutput;

#if 0

//[gait]
extern byte		GaitType;			//Gait type
extern short	NomGaitSpeed;		//Nominal speed of the gait

//[Single Leg Control]
extern byte		SelectedLeg;
extern short		SLLegX;
extern short		SLLegZ;
extern boolean		fSLHold;		 	//Single leg control mode


#endif

// Sounds Unit
extern void MSound(uint8_t _pin, byte cNotes, ...);

// The defined controller must provide the following
extern void InitController(void);
extern void	ControlInput(void);
extern void	AllowControllerInterrupts(boolean fAllow);

// Ultrasonic Unit
extern void InitializeUltrasonic();
extern float getBackDistance();
extern float getLeftDistance();
extern float getRightDistance();
extern float getFrontDistance();
extern void calcSensorDistances();

// Voltage Sensor
extern void voltageSetup();
extern double voltageRead();
extern bool CheckVoltage(void);

// Bluetoooth Monitor, debug handler...
extern bool TerminalMonitor();
extern boolean g_fDBGHandleError;


#endif


