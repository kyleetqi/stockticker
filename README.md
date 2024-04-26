# Introduction
* This project was inspired by Michael Klements' [ESP32 Stock Ticker](https://www.the-diy-life.com/bitcoin-ticker-using-an-esp32-and-oled-display/) and [this Reddit post.](https://www.reddit.com/r/wallstreetbets/comments/lfkprt/finished_my_diy_project_just_in_time_for_gme_to/?rdt=59493)
* These files are for **PERSONAL USE** only. Please contact me if you wish to use these files commercially.
* Please read through all documentation before starting this project.
* [Demo Video]()

![Stock ticker display mounted on a circuit board.](./images/final-design.png)

# Known Issues and Limitations
* Although finnhub.io claims to provide live stock information, the API response may not be up to date at all times.
* Please contact me if you find any issues with the repository. :)
* There are some known issues with the USB-C port. 
  * Please check that your cable and brick can successfully supply power to the board. For some reason, the Apple charging brick will not work with the board. When I was testing my board with the Apple charger, no power was supplied and I thought it was because the cable was not plugged in all the way. Because of this, I unnecessarily filed the board down so the cable could plug in properly.
  * The USB-C port is located a bit far into the board. Because of this, it may be necessary to file down the side of the PCB to plug in the cable. **PLEASE THOROUGHLY VERIFY IF THIS IS NECESSARY FOR YOU.**
  
# Bill of Materials
* I sourced all my parts from Sayal but feel free to source from wherever you'd like.
* Use your judgement when substituting parts ensuring compatibility with the code and PCB. Modify the code and gerber as necessary.

### Required Items
Qty | Item Description | Notes |
--- | --- | --- |
1 | [DOIT ESP32 DEVKIT V1](https://shop.sayal.com/products/1815-ha1?_pos=1&_sid=3067e8a6e&_ss=r)  |  |
1 | [ULN2003 IC](https://shop.sayal.com/products/1814-lc1?_pos=3&_sid=53d498842&_ss=r) | The IC and motor come as a set if ordering from Sayal. | 
1 | [28BYJ-48 Stepper Motor](https://shop.sayal.com/products/1814-lc1?_pos=3&_sid=53d498842&_ss=r) | See above. |
1 | [SH1106 OLED Display](https://shop.sayal.com/products/1814-fa1?_pos=1&_sid=ff4679778&_ss=r) | Some displays swap the position of VCC and GND. Verify the display pinout is compatible with PCB.|
1 | Red LED |  |
1 | Green LED |  |
1 | 0.1 uF capacitor | 1 uF should be fine as well. |
2 | Resistor | Choose between 360Ω and 1k Ω to control LED brightness. |
1 | [6-pin USB-C jack](https://shop.sayal.com/products/amtc-1154?_pos=3&_sid=0e93b7e13&_ss=r) |  |
1 | Pointer | 3D print using `pointer-rocket.stp`. If designing your own pointer, ensure the cylinder's inner diameter is 5mm. |
2 | #4-40 x 1/4" Screw | Used to mount the motor. M3 hardware is a suitable substitute. |
2 | #4-40 Nut | Used to mount the motor. M3 hardware is a suitable substitute. |
As Req. | Insulating tape | Electrical tape, foam tape, etc. |

### Optional Items
* The following items are used to mount the PCB to the acrylic stand I designed. If you decide to mount the PCB another way, choose your hardware accordingly.

Qty | Item Description | Notes |
--- | --- | --- |
1 | Acrylic Stand | Laser cut using `pcb-cover.dwg` |
4 | [#4-40 x 12.7mm Standoff](https://shop.sayal.com/products/krc-164-2?_pos=8&_sid=6d0b828ae&_ss=r)| M3 hardware is a suitable substitute. |
4 | #4-40 x 1/4" Screw | M3 hardware is a suitable substitute. |
4 | #4-40 x 3/8" Screw | M3 hardware is a suitable substitute. |

# PCB
* If you plan on ordering PCBs using the provided gerber file, I recommend specifying where the manufacturer prints their PCB ID#. Make sure to select the `specify ID location` option before checking out!
  * If you are ordering from JLCPCB, you do not need to edit the gerber file.
  * If you are ordering from PCBWay, edit `JLCJLCJLCJLC` to `WayWayWay`.
  * If you are ordering from another manufacturer, follow their instructions accordingly.

# Software
* Ensure you have the Arduino IDE installed.
* If this is your first time flashing your ESP32, I recommend referencing a [comprehensive setup guide.](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)
* Connect your ESP32 to your computer and open up `stockticker-public.ino` using the Arduino IDE.
* Ensure you have selected `DOIT ESP32 DEVKIT V1` as your board, and the correct serial port for communication.
  * At this stage, you may want to test if you have successfully established a connection with your ESP32. Try running an example such as the one at `File` > `Examples` > `Wifi` > `WiFiScan`
  * When trying to upload code onto my ESP32. I kept getting the error: `Failed to establish serial connection.` To resolve this, open the serial monitor and hold the `BOOT` then `EN`(RESET) buttons down on your ESP32. You should see a response in the monitor at which point the code should be able to upload successfully. I hope this helps at least one person because I never found this solution online.
* Install the following libraries required to compile the code:

Library Name | Author |
--- | --- |
Adafruit BusIO | Adafruit |
Adafruit GFX Library | Adafruit |
Adafruit SH110X | Adafruit | 
ArduinoJson | Benoit Blanchon |

* To fetch real, live stock market information, obtain a free API key from [finnhub.io.](https://finnhub.io/)
* Change the network and API parameters at the top of the code as necessary such as `symbol`, `key`, `ssid`, `pass`, etc.
* Modify the `updateTime` variable to set how frequently the device updates price information.
* Modify the `motorResponse` variable to control how sensitive the pointer is to stock changes.
* Verify and upload the code onto the ESP32.

# Soldering and Installation
* Before soldering components onto the board, use the schematic to wire and test the system on a breadboard to ensure everything is working.
* Verify that your cable can successfully plug into the USB-C port before soldering it into the board. See `Known Issues and Limitations` section.
* Extract the ULN2003 IC from the driver board that comes with the motor and solder it directly onto the front of the PCB **before** installing the motor.
* [Insulate](./images/insulation-example.JPG) the ULN2003 pins on the backside of the PCB using the insulating tape.
* Mount the motor to the back of the PCB using hardware so that the shaft protrudes through the 10mm hole in the PCB towards the front.
* Cut the motor wires to length and solder them onto the back of the PCB making sure to pay attention to which color corresponds to which hole.
* Turn the PCB back over to the front and insulate the solder from the motor connections. Afterwards, solder on the OLED display.
* Solder all other components.
* Install the pointer onto the shaft of the motor.
* Mount the device using the four corner holes on the PCB.

# Operation
* Plug and play. Use power supply that is rated at 5V and can supply at least 2A. A phone charging brick should be sufficient. **DO NOT USE MORE THAN ONE POWER SOURCE AT THE SAME TIME.**
* Manually level the pointer to horizontal before powering the device since the motor does not have absolute positioning. The motor doesn’t remember its positioning between power ons.
* If the ESP32 is unable to establish a connection to the internet or API, it will automatically enter demo mode and generate random data.
  
  
   
