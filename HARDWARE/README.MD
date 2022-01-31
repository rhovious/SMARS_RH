# HARDWARE

## 3D Printing
### Base Models

* [SMARS body 3D models v1](https://cults3d.com/en/3d-model/gadget/smars-modular-robot)
* [SMARS body 3D models v4](https://cults3d.com/en/3d-model/gadget/smars-v4)
### Mods
[Various additional 3D Parts](MODS/)

* [9V Frame](<MODS/9V frame/>)
* [HM-10 Mount](<MODS/HM-10 Mount/>)
* [ADAFruit Motor Shield](<MODS/L298P Shield MK2 COVER/>)
* [Lightbar](<MODS/lightbar/>)
---
## Hardware Used

* Arduino Uno
* ADAFruit Motor Shield
* LED Strip
* 2x N90 Motors
---
## PINS

| Pin | Description |
| --- | ----------- |
 2 | Tx --> HC-05 Rx
3 | Rx --> HC-05 Tx
A4 | SDA --> i2C, used by Motor Sheild
A5 | SCL --> i2C, used by Motor Sheild
2 | Neopixel Data Pin
9  |   Servo Pin, From Motor Sheild Connection
10  |   Servo Pin, From Motor Sheild Connection

## i2c Addressed
* 0x60 (the default address of the shield)
* 0x70 (the 'all call' address that this chip uses for group-control)