# Sumd-Joy

A simple Arduino sketch that converts the SUMD signal of a Graupner 12 channel receiver like the GR-12L into a joystick.
This assumes an Arduino Leonard or Arduino Pro Mini that can create USB interfaces.

## X&Y Axis
It assumes that the Remote is setup as a Plane, with a single aileron channel and standard Elevator rudder and a single motor. The channel mapping follows the Graupner default assignment:

| Channel | Joystick |
|---------|----------|
| 1       | Y-Axis   |
| 2       | Rx-Axis  |
| 3       | Ry-Axis  |
| 4       | X-Axis   |

## Z Axis
Channel 5 & 6 are used as Z-Axis and RZ-Axis. 

## Buttons
The remaining 6 channels are mapped to tri-state switches such that each switch sends **1100**, **1500** or **1900**. Those values are then mapped to 3 joystick buttons each that are pressed if the channel is in their value range:
    
     B1   B2   B3
    1100 1500 1900
      \   |   /
       \  |  /
        \ | /
       Channel 6


## Arduino Joystick Library

The Joystick.* and DynamicHID.* have been copied from the [Arduino Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary)