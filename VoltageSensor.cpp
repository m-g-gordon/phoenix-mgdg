#include <TimerThree.h>

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


extern void blinkCallback();


extern boolean g_fLowVoltageShutdown;    // If set the bot shuts down because the input voltage is too low

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
            Timer3.initialize(500000);         // initialize timer1, and set a 1/2 second period
            Timer3.attachInterrupt(blinkCallback);  // attaches callback() as a timer overflow interrupt
        }
    } 

    return g_fLowVoltageShutdown;
}


bool bLedOn = true;

void blinkCallback()
{
  if (bLedOn)
  {
    digitalWrite(STATUSLED, LOW);   // set the LED off
    bLedOn = false;
  }
  else
  {
    digitalWrite(STATUSLED, HIGH);    // set the LED on
    bLedOn=true;
  }
}


