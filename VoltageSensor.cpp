#include "Hex_Globals.h"
#include "Hex_Cfg.h"

int offset = 20;

void voltageSetup() {
  // put your setup code here, to run once:
  pinMode(VOLTSENSOR, INPUT);
}

double voltageRead() {
   //put your main code here, to run repeatedly:
  int volt = analogRead(VOLTSENSOR);
  volt -= offset;
  double voltage = map(volt, 0, 1023, 0, 2500);
  voltage /=100;
  return voltage;
}


extern boolean g_fLowVoltageShutdown;    // If set the bot shuts down because the input voltage is to low

// Part of Original Phoenix code. Not used
bool CheckVoltage() {
#ifdef  cVoltagePin   
#ifdef cTurnOffVol
    Voltage = analogRead(cVoltagePin); // Battery voltage
    Voltage = ((long)Voltage*1955)/1000;

    if (!g_fLowVoltageShutdown) {
        if ((Voltage < cTurnOffVol) || (Voltage >= 1999)) {
#ifdef DBGSerial          
            DBGSerial.println("Voltage went low, turn off robot");
#endif            
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
      g_ControlState.SelectedLeg = 255;
      g_fLowVoltageShutdown = 1;
            s_bLVBeepCnt = 0;    // how many times we beeped...
      g_ControlState.fHexOn = false;
  }
#ifdef cTurnOnVol
    } else if ((Voltage > cTurnOnVol) && (Voltage < 1999)) {
#ifdef DBGSerial
            DBGSerial.println("Voltage restored");
#endif          
            g_fLowVoltageShutdown = 0;
            
#endif      
    } else {
        if (s_bLVBeepCnt < 5) {
          s_bLVBeepCnt++;
          MSound(SOUND_PIN, 1, 45, 2000);
        }
        delay(2000);
    }
#endif  
#endif
  return g_fLowVoltageShutdown;
}
