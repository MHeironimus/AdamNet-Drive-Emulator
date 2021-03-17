# AdamNet Drive Emulator (ADE)

The AdamNet Drive Emulator (ADE) is an SD card drive emulator for the ColecoVision Adam. It replicates all of the known drive commands and has no known incompatibilities. It is written in C++ using the Arduino IDE. It is simple to assemble for anyone with basic electronics skills. I have also created a companion program for the Adam called ADE Commander (ADEC) https://github.com/Kalidomra/ADE-Commander. This program is put in the root of the SD card as "boot.dsk". 

			This is a beta. Use at your own risk.
			
You can wire up your own without a PCB using the instructions below, or build a PCB using the layout provided by Chris Tersteeg: https://github.com/djtersteegc/coleco-adam-ade-pro-shield


### Bill of Materials:

 1. Arduino Mega 2560 R3 - An original Arduino or a quality replica.
 2. 1602 Keypad Shield - Arduino Version
 3. SD Card Shield - Micro SD with level converter
 4. 6 connector phone cable.
 5. 1k and 33 ohm resistors.
 6. PNP Transistor (2N3906)
 
*Version 0.5 has changed how the AdamNet line is connected; it now requires a PNP transistor. This version is not compatible with the old method of connecting the AdamNet line to the Mega2560.

### How it is connected:

 Look at the "Connection Diagram.jpg" file.

 1. Mount the 1602 Keypad Shield to the Mega2560. Ensure the contrast potentiometer is adjusted on the LCD. It is the tiny blue box in the upper left corner with a screw. Most of the time it is not adjusted correctly and will take several turns left or right to adjust.
 2. Connect the SD Card Shield to the Mega2560.
 	Use the following pins: MISO = 50, MOSI = 51, SCK = 52, CS = 53, 5v and GND
 3. Attached the phone cord with the resistors and transistor as identified in "Connection Diagram.jpg".

### Installation:

 1. Install the Arduino IDE and configure it for the Mega2560: https://www.arduino.cc/
 2. Install the SD Card Library to your Arduino IDE: https://github.com/greiman/SdFat/releases
 
	NOTE: Use version 1.1.4, ADE will not compile with version 2.0 or above.
	
 	How to install a library: https://www.arduino.cc/en/guide/libraries
 3. Download the latest ADE release from GitHub. Load it in the Arduino IDE. You should see all of the ADE tabs open in the Arduino IDE.
 4. Connect the Mega2560 to the USB port. Press the "Upload" button in the Arduino IDE to compile and upload.
 5. You should see the ADE starting up on the LCD. If you can not see anything on the LCD and you have no errors in the Arduino IDE, try adjusting the contrast on the LCD.

### How it works:

Place up to 300 files per directory on a FAT32 formatted SD card. These can be in DSK or DDP format commonly found on the web.
On start up of the ADE there is no mounted file. Scroll though the files using the up and down keys. 
Mount or change directory of the currently selected item in the bottom of the LCD with the right key. 
Unmount with a long press of the right button.
The currently mounted file for the drive is shown on the top row. The select key will change the current drive displayed.

The ADE also has 2 setup/troubleshooting modes:

 1. Device Selection Mode: Hold the Select key while the ADE to starting up. In this mode, you can configure which drives will be enabled. After they are configured, restart the ADE to resume drive emulation.
 2. Voltage Mode: Holding the Mount/Unmount (Right) key while the ADE to starting up. In this mode the ADE will display the input voltage to the Mega2560. This can help trouble shoot some power related issues. The voltage should be close to 5v. Restart the ADE to resume drive emulation.


