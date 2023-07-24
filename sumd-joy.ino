#include "Joystick.h"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 6*3, 0, true, true, true, true, true, true, false, false, false, false, false);

uint8_t SUMD[36];
uint16_t channels[36];
uint8_t numChannels = 0;

void setup() {
  memset(SUMD, 0, 36);
  for(int i=0;i<36;i++)
    channels[i] = 1500;

  pinMode(LED_BUILTIN, OUTPUT);

  // put your setup code here, to run once:
  Joystick.begin(false);
  Joystick.setXAxisRange(1100, 1900);
  Joystick.setYAxisRange(1100, 1900);
  Joystick.setZAxisRange(1100, 1900);

  Joystick.setRxAxisRange(1100, 1900);
  Joystick.setRyAxisRange(1100, 1900);
  Joystick.setRzAxisRange(1100, 1900);

  Serial1.begin(115200);
}

void readPacket()
{
  uint8_t byte;

  while(1) {
    Serial1.readBytes(&byte, 1);
    if (byte == 0xA8)
      break;
  }
    
  Serial1.readBytes(&byte, 1);
  if (byte != 0x01) {
    Serial.print("Could not find 0x01\n");
    return;
  }

  Serial1.readBytes(&byte, 1);
  numChannels = byte;

  Serial1.readBytes(SUMD, numChannels*2);

  for(int i=0;i<numChannels;i++)
    channels[i] = (SUMD[i*2]<<5)+(SUMD[i*2+1]>>3);
}

void loop() {
  readPacket();

  // Helps to verify if data is received.
  analogWrite(LED_BUILTIN, map(channels[0], 1000, 2000, 0, 255));

  Joystick.setXAxis(channels[3]);
  Joystick.setYAxis(channels[0]);
  Joystick.setZAxis(channels[4]);

  Joystick.setRxAxis(channels[1]);
  Joystick.setRyAxis(channels[2]);
  Joystick.setRzAxis(channels[5]);

  for(int i=6;i<12;i++) {
    int btnIdx = i-6;
    Joystick.setButton(btnIdx*3,   channels[i] < 1200   );
    Joystick.setButton(btnIdx*3+1, channels[i] > 1200 && channels[i] < 1800 );
    Joystick.setButton(btnIdx*3+2, channels[i] > 1800 );
  }

  Joystick.sendState();
}
