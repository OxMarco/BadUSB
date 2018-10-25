# BadUSB
Personal implementation of the BadUSB exploit with an Atmel 8-bit AVR ATTiny85 acting as a HID keyboard and opening a reverse shell on the target PC.

## Description
Using a DigiSpark clone board bought from China for $1.50, using Digistump drivers, it was possible to use their default library "DigiKeyboard" that enables HID features on the ATTiny and makes it act as a standard keyboard.
There is a switch that allows to select which OS to target, either Windows or Unix based systems.

When the unit is plugged in, a new terminal window is opened and a reverse shell on port 8080 is established, without prompting anything to the user. When the script has run, the led will start blinking until unplugged from the USB port.

## HowTo
Simply run __nc -l PORT__ on your machine in order to listen to the incoming connections.
Other uses may involve an automatic meterpeter session with permanent payload deployment.

## Under Development
The features still to be fully implemented/functional:
* Non-US keyboard layout;
* Automatic OS recognition.

## Problems
Here are a couple of issues that needs to be fixed:
* Sometimes the first time the unit is plugged in, the script doesn't get executed;
* A few systems will prompt new hardware installation window and may take a couple of minutes to install the proper drivers (even though the DigiSpark acts as a typical USB keyboard).
