#include "Joystick.h"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD, 4, 1, true, true, true, true, true, true, false, false, false, false, false);

uint8_t SUMD[36];
uint16_t channels[36];

void setup() {
  memset(SUMD, 0, 36);

  pinMode(LED_BUILTIN, OUTPUT);


  // put your setup code here, to run once:
  Joystick.begin(false);
  Joystick.setXAxisRange(1100, 1900);
  Joystick.setYAxisRange(1100, 1900);
  Joystick.setZAxisRange(1100, 1900);

  Joystick.setRxAxisRange(1100, 1900);
  Joystick.setRyAxisRange(1100, 1900);
  Joystick.setRzAxisRange(1100, 1900);

//  Joystick.setRudderRange(1100, 1900);
//  Joystick.setThrottleRange(1100, 1900);
//  Joystick.setBrakeRange(1100, 1900);

  Serial1.begin(115200);
}

uint8_t numChannels = 0;



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
    return;
  }
  Serial1.readBytes(&byte, 1);
  numChannels = byte;

  Serial1.readBytes(SUMD, numChannels*2);

  for(int i=0;i<numChannels;i++) {
    channels[i] = (SUMD[i*2]<<5)+(SUMD[i*2+1]>>3);
  }
  analogWrite(LED_BUILTIN, channels[0]);

  Joystick.setXAxis(channels[0]);
  Joystick.setYAxis(channels[1]);
  Joystick.setZAxis(channels[2]);

  Joystick.setRxAxis(channels[3]);
  Joystick.setRyAxis(channels[4]);
  Joystick.setRzAxis(channels[5]);

/*  Joystick.setRudder(channels[6]);
  Joystick.setThrottle(channels[7]);
  Joystick.setBrake(channels[8]);
*/
  Joystick.sendState();

}

void loop() {
  readPacket();
}
