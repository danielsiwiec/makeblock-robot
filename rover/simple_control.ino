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

MeBluetooth bluetooth(PORT_6);
MeDCMotor leftMotor(M1);
MeDCMotor rightMotor(M2);
uint8_t motorSpeed = 100;

void setup()
{
  Serial.begin(115200);
  bluetooth.begin(115200);    //The factory default baud rate is 115200
  Serial.println("Bluetooth Start!");
}

void forward()
{
  leftMotor.run(motorSpeed);
  rightMotor.run(motorSpeed);
}

void backwards()
{
  leftMotor.run(-motorSpeed);
  rightMotor.run(-motorSpeed);
}

void right()
{
  leftMotor.run(motorSpeed);
  rightMotor.run(motorSpeed*0.2);
}

void left()
{
  leftMotor.run(motorSpeed*0.2);
  rightMotor.run(motorSpeed);
}

void stop()
{
  leftMotor.stop();
  rightMotor.stop();
}

void loop()
{ 
  if (bluetooth.available())
  {
    String data = bluetooth.readString();
    Serial.print(data);
    if (data.equals("FORWARD")) forward();
    if (data.equals("BACKWARDS")) backwards();
    if (data.equals("LEFT")) left();
    if (data.equals("RIGHT")) right();
    if (data.equals("0")) stop();
  }
}

