#include "Hex_Cfg.h"
#include "Hex_Globals.h"

// Define some globals for debug information
boolean g_fShowDebugPrompt = true;
boolean g_fDebugOutput = true;


int ptctr = 0;
int ptxpos[] = { 900, 1100, 1300, 1500, 1800, 2100};
int ptypos[] = { 1500, 1500, 1500, 1500, 1500, 1500};

//==============================================================================
// BlueTooth TerminalMonitor - Simple background task checks to see if the user is asking
// us to do anything, like varous commands, update debug levels and the like.
//==============================================================================
bool TerminalMonitor(void)
{
  char szCmdLine[12];  // currently pretty simple command lines...
  int ich;
  int ch;
  // See if we need to output a prompt.
  if (g_fShowDebugPrompt) {
    DBGSerial.println("Arduino Phoenix Monitor");
    //DBGSerial.println("D - Toggle debug on or off");
    DBGSerial.println("C - Centre all Body Servos");
    // DBGSerial.println("O - Enter SSC-32 Servo offset mode");
    DBGSerial.println("X - Report Version of SSC-32");
    DBGSerial.println("M - Cycle Pan-Tilt mode");
    DBGSerial.println("V - Toggle Video Streaming");
    DBGSerial.println("B - Read Battery Voltage");
    DBGSerial.println("L - Toggle Headlights");
    DBGSerial.println("U - Turn on Ultrasonics");
    DBGSerial.println("? - Show this List");
    DBGSerial.println("! - Start/Stop Robot");
    g_fShowDebugPrompt = false;
  }

  // First check to see if there is any characters to process.
  if (ich = DBGSerial.available())
  {
    ich = 0;
    // For now assume we receive a packet of data from serial monitor, as the user has
    // to click the send button...
    for (ich = 0; ich < sizeof(szCmdLine); ich++)
    {
      ch = DBGSerial.read();        // get the next character
      if ((ch == -1) || ((ch >= 10) && (ch <= 15)))
        break;
      szCmdLine[ich] = ch;
    }

    szCmdLine[ich] = '\0';    // go ahead and null terminate it...

    DBGSerial.print("Serial Cmd Line: [");
    DBGSerial.print(String(szCmdLine));
    DBGSerial.println("]");

    // So see what are command is.
    if (ich == 0)
    {
      // g_fShowDebugPrompt = true;
    }
    else if ((ich == 1) && ((szCmdLine[0] == 'd') || (szCmdLine[0] == 'D')))
    {
      g_fDebugOutput = !g_fDebugOutput;
      if (g_fDebugOutput)
        DBGSerial.println("Debug is on");
      else
        DBGSerial.println("Debug is off");
    }
    else if ((ich == 1) && ((szCmdLine[0] == 'u') || (szCmdLine[0] == 'U')))
    {
      g_fDebugOutput = !g_fDebugOutput;
      if (g_ControlState.UseUltrasonics)
      {
        DBGSerial.println("Ultrasonics are on");
        reportUltrasonicDistances();
      }
      else
        DBGSerial.println("OFF Enable Ultrasonics First");
    }
    else if ((ich == 1) && (szCmdLine[0] == '!'))
    {
      g_fShowDebugPrompt = false;
      if (g_ControlState.fHexOn)
      {
        //DBGSerial.println("Turning Robot Off");
        //TurnRobotOff();
      }
      else
      {
        //Turn on
        //DBGSerial.println("Turning Robot On");
        //g_ControlState.fHexOn = 1;
      }
    }
    else if ((ich == 1) && ((szCmdLine[0] == 'x') || (szCmdLine[0] == 'X')))
    {
      g_fShowDebugPrompt = false;
      g_ServoDriver.ReportVersion();
    }
    else if ((ich == 1) && ((szCmdLine[0] == 'o') || (szCmdLine[0] == 'O')))
    {
      g_ServoDriver.FindServoOffsets();
    }
    else if ((ich == 1) && ((szCmdLine[0] == 's') || (szCmdLine[0] == 'S')))
    {
      g_ServoDriver.SSCForwarder();
    }
    else if ((ich == 1) && ((szCmdLine[0] == 'm') || (szCmdLine[0] == 'M')))
    {
      g_fShowDebugPrompt = false;  // Do not redraw all the options
      
      DBGSerial.print("PAN & TILT Mode: ptcntr=");
      DBGSerial.print( String(ptctr));
      DBGSerial.println("");

      g_ServoDriver.UpdatePanPosition(PAN_ON_SSC32, ptxpos[ptctr]);
      g_ServoDriver.UpdateTiltPosition(TILT_ON_SSC32, ptypos[ptctr]);

      delay(200);

      ptctr++;
      if(ptctr > 5) ptctr = 0;
    }
    else if ((ich == 1) && ((szCmdLine[0] == 'v') || (szCmdLine[0] == 'V')))
    {
      g_fShowDebugPrompt = false;  // Do not redraw all the options
      
      DBGSerial.println("Toggling Video");
      g_ControlState.VIDEO_TRX = !g_ControlState.VIDEO_TRX;

      digitalWrite(VIDEOTRANSMIT, g_ControlState.VIDEO_TRX ? HIGH : LOW);
    }
    else if ((ich == 1) && ((szCmdLine[0] == 'b') || (szCmdLine[0] == 'B')))
    {
      g_fShowDebugPrompt = false;  // Do not redraw all the options
      
      DBGSerial.println("Read Battery Voltage");
      double voltage = voltageRead();
      DBGSerial.print("Voltage: ");
      DBGSerial.print(voltage);
      DBGSerial.println("V");  
    }
    else if ((ich == 1) && ((szCmdLine[0] == 'l') || (szCmdLine[0] == 'L')))
    {
      g_fShowDebugPrompt = false;  // Do not redraw all the options
      
      DBGSerial.println("Toggling Headlights");
      g_ControlState.HEADLIGHTS = !g_ControlState.HEADLIGHTS;
      if (g_ControlState.HEADLIGHTS) {
        digitalWrite(HEADLIGHT, HIGH);
      }
      else {
        digitalWrite(HEADLIGHT, LOW);
      }
    }
    else if ((ich == 1) && ((szCmdLine[0] == '?') ))
    {
      g_fShowDebugPrompt = true;
    }

    return true;
  }
  return false;
}

