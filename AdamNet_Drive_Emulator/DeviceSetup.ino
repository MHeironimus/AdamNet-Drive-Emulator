void DeviceSetup(){                                                // Initialize the EEPROM and the devices
  byte numberofdrives = 0;
  Device4 = false;
  Device5 = false;
  Device6 = false;
  Device7 = false;
  // Check if the EEPROM has been initialized. 3 Checks: 1 -> Bytes 'ADE', 2 -> NameLength Hasn't Changed, 3 -> Version Hasn't Changed
  if ((EEPROM.read(0) == 65) && (EEPROM.read(1) == 68) && (EEPROM.read(2) == 69) &&
      (EEPROM.read(32) == NameLength) && 
      (EEPROM.read(16) == Version[0]) && (EEPROM.read(17) == Version[1]) && (EEPROM.read(18) == Version[2])){ 
   if (EEPROM.read(4) == 1){
      Device4 = true;
      numberofdrives++;
    }
    if (EEPROM.read(5) == 1){
      Device5 = true;
      numberofdrives++;
    }
    if (EEPROM.read(6) == 1){
      Device6 = true;
      numberofdrives++;
    }
    if (EEPROM.read(7) == 1){
      Device7 = true;
      numberofdrives++;
    }
  }
  else{                                    // Eeprom is not initialized, let's set it up. Default is all drives on.
    Serial.println(F("EEPROM Not Initialized"));
    Serial.println(F("Erasing EEPROM:"));
    for (int w; w <= 4096; w++){
      EEPROM.write(w,0xFF);
      if ( w % 102 == 0){
        Serial.print(F("."));
      }
    }
    Serial.println();
    Serial.println(F("Initializing EEPROM"));
    Serial.println(F("D1, D2, D3 and D4 have been enabled"));
    Device4= true;
    Device5= true;
    Device6= true;
    Device7= true;
    EEPROM.write(0,65);                    // A  )
    EEPROM.write(1,68);                    // D  } = Signature bytes to know that the EEPROM has been configured.
    EEPROM.write(2,69);                    // E  )
    EEPROM.write(3,4);                     // Initial display device is 4
    EEPROM.write(4,1);                     // Enable Device 4
    EEPROM.write(5,1);                     // Enable Device 5
    EEPROM.write(6,1);                     // Enable Device 6
    EEPROM.write(7,1);                     // Enable Device 7
    // Future Device bytes 8,9,10,11,12,13,14,15
    EEPROM.write(16,Version[0]);           //  )
    EEPROM.write(17,Version[1]);           //  } = Version Number
    EEPROM.write(18,Version[2]);           //  )
    EEPROM.write(32,NameLength);           // The maximum file length
    numberofdrives = 4;
  }
  if (numberofdrives == 0){                // No Drives have been turned on
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("No Drives"));
    lcd.setCursor(0,1);
    lcd.print(F("Enabled"));
    while(1){}                             // Program will die here. Re-run config mode and turn on a drive.
  }
  DeviceDisplayed = EEPROM.read(3); // Load in the last device that was displayed
  if ((DeviceDisplayed == 4) && !Device4){ //Make sure it is still available, if not make it 0
    DeviceDisplayed = 0;
  }
  if ((DeviceDisplayed == 5) && !Device5){
    DeviceDisplayed = 0;
  }
  if ((DeviceDisplayed == 6) && !Device6){
    DeviceDisplayed = 0;
  }
  if ((DeviceDisplayed == 7) && !Device7){
    DeviceDisplayed = 0;
  }
  if ((DeviceDisplayed < 4) || (DeviceDisplayed > 7)){ // If the device is outside the correct numbers then re-assign to the lowest available device.
      if (Device4){
        DeviceDisplayed = 4; 
      }
      else if (Device5){
        DeviceDisplayed = 5; 
      }
      else if (Device6){
        DeviceDisplayed = 6; 
      }
      else if (Device7){
        DeviceDisplayed = 7; 
      }
  }
  if (Device4){
    if (BootDiskIndex != 0){               // If there is a boot disk then mount it.
      MountedFile[0] = BootDiskIndex;
      Serial.print(F("D1: <boot>: "));
      Serial.println(BootDisk);
      StatusSetup(0x40, 4);                // Set the Status to "disk in"
      refreshscreen = 1;
    }
    else{
      DeviceSetupCommand(4);
    }
  }
  if (Device5){
    DeviceSetupCommand(5);
  }
  if (Device6){
    DeviceSetupCommand(6);
  }
  if (Device7){
    DeviceSetupCommand(7);
  }
}
void DeviceSetupCommand(byte devicenumber){
  String eepromfilename;
  byte hiByte =  EEPROM.read(devicenumber * 400);
  byte lowByte =  EEPROM.read((devicenumber * 400) + 1);
  MountedFile[devicenumber-4] =  word(hiByte, lowByte);
  eepromfilename = EepromStringRead((devicenumber * 400) + 2);
  if (MountedFile[devicenumber-4] > MaxFiles || eepromfilename != GetFileName(FilesIndex[MountedFile[devicenumber-4]])){
    MountedFile[devicenumber-4] = 0;
  }
  else if (MountedFile[devicenumber-4] != 0){
    Serial.print(F("D"));
    Serial.print(devicenumber - 3);
    Serial.print(F(": "));
    Serial.println(eepromfilename);
  }
  if (MountedFile[devicenumber-4] == 0){
    StatusSetup(0x43, devicenumber);       // Setup the Status array to "no disk"
    Serial.print(F("D"));
    Serial.print(devicenumber - 3);
    Serial.println(F(": < No Disk >"));
  }
  else{
    StatusSetup(0x40, devicenumber);       // Set the Status to "disk in"
  }
}