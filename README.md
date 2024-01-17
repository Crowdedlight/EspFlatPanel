# EspFlatPanel
Code for ESP32-S3 and ASCOM Alpaca driver for wireless Flat Panel running DotStar LED strip

Libs required:
ArduinoJson 7.0
FastLED 3.6.0

They should be installed automatically through platformio when loading this workspace


Tested and verified with ASCOM ConformU to conforming to the Ascom Alpaca Standard.  
The issues reported is due to ConformU skips testing Cover methods when Cover is "Not Implemented". I have raised the issue on the group forum. 

```
00:51:47.744 ASCOM Universal Device Conformance Checker Version 2.1.0.23787, Build time: tor 11 januar 2024 11:25:50
00:51:47.745
00:51:47.745 Operating system is Microsoft Windows 10.0.19045 64bit, Application is 64bit.
00:51:47.746
00:51:47.747 Alpaca device: Esp Flat Panel (192.168.11.19:4567 CoverCalibrator/0)
00:51:47.748
00:51:47.748 CreateDevice                        INFO     Creating Alpaca device: IP address: 192.168.11.19, IP Port: 4567, Alpaca device number: 0
00:51:47.749 CreateDevice                        INFO     Alpaca device created OK
00:51:47.750 CreateDevice                        INFO     Successfully created driver
00:51:48.764 CreateDevice                        OK       Driver instance created successfully
00:51:48.765
00:51:48.765 Pre-connect checks
00:51:48.766
00:51:48.767 Connect to device
00:51:48.944 Connected                           OK       Connected to device successfully using Connected = True
00:51:48.945
00:51:48.946 Common Driver Methods
00:51:48.947 InterfaceVersion                    OK       1
00:51:48.984 Connected                           OK       True
00:51:49.018 Description                         OK       ESP32 Alpaca controlled flat-panel for use with DotStar LED strip and a homemade flatpanel
00:51:49.060 DriverInfo                          OK       Driver is firmware made by Crowdedlight for ESP32-S3: https://github.com/Crowdedlight/EspFlatPanel
00:51:49.095 DriverVersion                       OK       v1.0.0
00:51:49.123 Name                                OK       Esp Flat Panel
00:51:49.124
00:51:49.124 Action                              INFO     Conform cannot test the Action method
00:51:49.170 SupportedActions                    OK       Driver returned an empty action list
00:51:49.171
00:51:49.171 DeviceState                         INFO     DeviceState tests omitted - DeviceState is not available in this interface version.
00:51:49.172
00:51:49.172 Properties
00:51:49.207 CalibratorState                     OK       Off
00:51:49.254 CoverState                          OK       Received a NotImplementedException from an Alpaca device as expected
00:51:49.331 MaxBrightness                       OK       255
00:51:49.404 Brightness                          OK       255
00:51:49.405
00:51:49.405 Methods
00:51:49.406 OpenCover                           ISSUE    Test skipped because CoverState returned an exception
00:51:49.407 CloseCover                          ISSUE    Test skipped because CoverState returned an exception
00:51:49.408 HaltCover                           ISSUE    Test skipped because CoverState returned an exception
00:51:49.458 CalibratorOn                        OK       CalibratorOn with brightness -1 threw an InvalidValueException as expected
00:51:49.562 CalibratorOn                        OK       CalibratorOn with brightness 0 was successful. The synchronous operation took 0,1 seconds
00:51:49.604 CalibratorOn                        OK       The Brightness property does return the value that was set
00:51:49.740 CalibratorOn                        OK       CalibratorOn with brightness 63 was successful. The synchronous operation took 0,1 seconds
00:51:49.759 CalibratorOn                        OK       The Brightness property does return the value that was set
00:51:49.885 CalibratorOn                        OK       CalibratorOn with brightness 127 was successful. The synchronous operation took 0,1 seconds
00:51:49.928 CalibratorOn                        OK       The Brightness property does return the value that was set
00:51:50.029 CalibratorOn                        OK       CalibratorOn with brightness 191 was successful. The synchronous operation took 0,1 seconds
00:51:50.068 CalibratorOn                        OK       The Brightness property does return the value that was set
00:51:50.166 CalibratorOn                        OK       CalibratorOn with brightness 255 was successful. The synchronous operation took 0,1 seconds
00:51:50.204 CalibratorOn                        OK       The Brightness property does return the value that was set
00:51:50.235 CalibratorOn                        OK       CalibratorOn with brightness 256 threw an InvalidValueException as expected
00:51:50.392 CalibratorOff                       OK       CalibratorOff was successful. The synchronous action took 0,2 seconds
00:51:50.429 CalibratorOff                       OK       Brightness is set to zero when the calibrator is turned off
00:51:50.430
00:51:50.431 Disconnect from device
00:51:50.523 Connected                           OK       False
00:51:50.524
00:51:50.524 Conformance test has finished
00:51:50.525
00:51:50.526 Your device had 3 issues, 0 errors and 0 configuration alerts
00:51:50.527
00:51:50.527 Issue Summary
00:51:50.528 OpenCover                           ISSUE    Test skipped because CoverState returned an exception
00:51:50.529 CloseCover                          ISSUE    Test skipped because CoverState returned an exception
00:51:50.530 HaltCover                           ISSUE    Test skipped because CoverState returned an exception
```
