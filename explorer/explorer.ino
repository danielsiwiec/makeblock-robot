/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * @file    SlaveBluetoothBySoftSerialTest.ino
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2015/09/09
 * @brief   Description: this file is sample code for Me bluetooth device.
 *          The bluetooth inherited the MeSerial class from SoftwareSerial.
 *          You also can use this sample code to reset the bluetooth. The
 *          AT command for the Me bluetooth can see 0n page 7 of
 *          doc\Me_Bluetooth\Datasheet\ELET114A_Datasheet_v1.5.5_CH.pdf
 *          You can use the command "AT+URATE=<baudrate> <CR> <LF>" to re-set 
 *          the baud rate.
 *
 * Function List:
 * 1. void MeBluetooth::begin()
 * 2. int16_t MeBluetooth::available()
 * 3. size_t MeSerial::write(uint8_t byte)
 * 4. int16_t MeSerial::read(void)
 *
 * \par History:
 * <pre>
 * <Author>     <Time>        <Version>      <Descr>
 * Mark Yan     2015/09/09    1.0.0          rebuild the old lib
 * </pre>
 */
 
#include "MeOrion.h"
#include <SoftwareSerial.h>

#define NONE 0
#define LEFT 1
#define RIGHT 2

MeBluetooth bluetooth(PORT_6);
MeDCMotor leftMotor(M1);
MeDCMotor rightMotor(M2);
MeUltrasonicSensor ultraSensor(PORT_7);
uint8_t motorSpeed = 100;
bool go = false;
int rotateDirection = NONE;

void setup()
{
  bluetooth.begin(115200);    //The factory default baud rate is 115200
  bluetooth.setTimeout(50);
}

void forward()
{
  leftMotor.run(motorSpeed);
  rightMotor.run(motorSpeed);
}

void rotateLeft()
{
  leftMotor.run(-motorSpeed);
  rightMotor.run(motorSpeed);
  delay(100);
  stop();
}

void rotateRight()
{
  leftMotor.run(motorSpeed);
  rightMotor.run(-motorSpeed);
  delay(100);
  stop();
}

void stop()
{
  leftMotor.stop();
  rightMotor.stop();
}

void checkGo()
{
  String input = bluetooth.readString();
  if (input.equals("go")) go = true;
  if (input.equals("stop")) go = false;
}

void pickDirection()
{
  rotateDirection = random(1,3);
}

void loop()
{
    checkGo();
    if (go)
    {
      double distance = ultraSensor.distanceCm(); 
      bluetooth.println(distance);
      if (distance < 50 )
      {
        bluetooth.println("Obstacle ahead...");
        if (rotateDirection == NONE)
        {
          pickDirection();
        }
        switch(rotateDirection){
          case LEFT:
            bluetooth.println("Rotating left");
            rotateLeft();
            break;
          case RIGHT:
            bluetooth.println("Rotating right");
            rotateRight();
            break;
        }
      } else {
        bluetooth.println("Forward");
        rotateDirection = NONE;
        forward();
      }
    } else {
      bluetooth.println("Stopped");
      stop();
    }
}

