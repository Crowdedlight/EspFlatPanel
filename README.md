# EspFlatPanel
Code for ESP32-S3 and ASCOM Alpaca driver for wireless Flat Panel running DotStar LED strip.

Test of it can be seen here: https://youtu.be/fPaTHsD9jYk

**Libs required:**  
ArduinoJson 7.0  
FastLED 3.6.0  

**They should be installed automatically through platformio when loading this workspace**


Tested and verified with ASCOM ConformU to conforming to the Ascom Alpaca Standard:  
```
20:53:32.934 ASCOM Universal Device Conformance Checker Version 2.2.0.23978, Build time: ons 17 januar 2024 10:30:52
20:53:32.934
20:53:32.935 Operating system is Microsoft Windows 10.0.19045 64bit, Application is 64bit.
20:53:32.936
20:53:32.937 Alpaca device: Esp Flat Panel (192.168.11.19:4567 CoverCalibrator/0)
20:53:32.938
20:53:32.938 CreateDevice                        INFO     Creating Alpaca device: IP address: 192.168.11.19, IP Port: 4567, Alpaca device number: 0
20:53:32.939 CreateDevice                        INFO     Alpaca device created OK
20:53:32.940 CreateDevice                        INFO     Successfully created driver
20:53:33.947 CreateDevice                        OK       Driver instance created successfully
20:53:33.948
20:53:33.949 Pre-connect checks
20:53:33.949
20:53:33.950 Connect to device
20:53:34.209 Connected                           OK       Connected to device successfully using Connected = True
20:53:34.211
20:53:34.211 Common Driver Methods
20:53:34.212 InterfaceVersion                    OK       1
20:53:34.262 Connected                           OK       True
20:53:34.318 Description                         OK       ESP32 Alpaca controlled flat-panel for use with DotStar LED strip and a homemade flatpanel
20:53:34.362 DriverInfo                          OK       Driver is firmware made by Crowdedlight for ESP32-S3: https://github.com/Crowdedlight/EspFlatPanel
20:53:34.407 DriverVersion                       OK       v1.0.0
20:53:34.468 Name                                OK       Esp Flat Panel
20:53:34.468
20:53:34.469 Action                              INFO     Conform cannot test the Action method
20:53:34.505 SupportedActions                    OK       Driver returned an empty action list
20:53:34.506
20:53:34.507 DeviceState                         INFO     DeviceState tests omitted - DeviceState is not available in this interface version.
20:53:34.507
20:53:34.508 Properties
20:53:34.559 CalibratorState                     OK       Off
20:53:34.608 CoverState                          OK       NotPresent
20:53:34.683 MaxBrightness                       OK       255
20:53:34.794 Brightness                          OK       255
20:53:34.794
20:53:34.796 Methods
20:53:34.853 OpenCover                           OK       CoverStatus is 'NotPresent' and a NotImplementedException error was generated as expected
20:53:34.931 CloseCover                          OK       CoverStatus is 'NotPresent' and a NotImplementedException error was generated as expected
20:53:34.973 HaltCover                           OK       CoverStatus is 'NotPresent' and a NotImplementedException error was generated as expected
20:53:35.016 CalibratorOn                        OK       CalibratorOn with brightness -1 threw an InvalidValueException as expected
20:53:35.153 CalibratorOn                        OK       CalibratorOn with brightness 0 was successful. The synchronous operation took 0,1 seconds
20:53:35.198 CalibratorOn                        OK       The Brightness property does return the value that was set
20:53:35.298 CalibratorOn                        OK       CalibratorOn with brightness 63 was successful. The synchronous operation took 0,1 seconds
20:53:35.374 CalibratorOn                        OK       The Brightness property does return the value that was set
20:53:35.504 CalibratorOn                        OK       CalibratorOn with brightness 127 was successful. The synchronous operation took 0,1 seconds
20:53:35.551 CalibratorOn                        OK       The Brightness property does return the value that was set
20:53:35.676 CalibratorOn                        OK       CalibratorOn with brightness 191 was successful. The synchronous operation took 0,1 seconds
20:53:35.729 CalibratorOn                        OK       The Brightness property does return the value that was set
20:53:35.855 CalibratorOn                        OK       CalibratorOn with brightness 255 was successful. The synchronous operation took 0,1 seconds
20:53:35.909 CalibratorOn                        OK       The Brightness property does return the value that was set
20:53:35.949 CalibratorOn                        OK       CalibratorOn with brightness 256 threw an InvalidValueException as expected
20:53:36.076 CalibratorOff                       OK       CalibratorOff was successful. The synchronous action took 0,1 seconds
20:53:36.106 CalibratorOff                       OK       Brightness is set to zero when the calibrator is turned off
20:53:36.107
20:53:36.108 Disconnect from device
20:53:36.178 Connected                           OK       False
20:53:36.180
20:53:36.180 Conformance test has finished
20:53:36.181
20:53:36.182 No errors, warnings or issues found: your driver passes ASCOM validation!!
```
