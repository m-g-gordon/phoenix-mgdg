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
  delay(5);
  // volt += offset;
  double voltage = map(volt, 0, 1023, 0, 2500);
  voltage /=100;
  return voltage;
}


extern boolean g_fLowVoltageShutdown;    // If set the bot shuts down because the input voltage is to low

// Part of Original Phoenix code. Not used
bool CheckVoltage() {
 
    double voltage = voltageRead();  // Battery Voltage
    
    if (!g_fLowVoltageShutdown) 
    {
        if (voltage < 9.0) 
        {
            DBGSerial.println("Voltage is less than threshold, turning off robot");

            //Turn off Robot
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

            g_fLowVoltageShutdown = true;
            
            g_ControlState.fHexOn = false;

            // Setup Blink on Status LED
        }
    } 

    return g_fLowVoltageShutdown;
}
