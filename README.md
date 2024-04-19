# Introduction
* This project was inspired by Michael Klements' [ESP32 Stock Ticker](https://www.the-diy-life.com/bitcoin-ticker-using-an-esp32-and-oled-display/) and [this Reddit post](https://www.reddit.com/r/wallstreetbets/comments/lfkprt/finished_my_diy_project_just_in_time_for_gme_to/?rdt=59493).
* These files are for **PERSONAL USE** only. Please contact me if you wish to use these files commercially.
# Bill of Materials
* I sourced all my parts from Sayal but feel free to source from wherever you'd like :)
* Use your judgement when substituting parts ensuring compatability with the code and PCB. Modify the code and gerber as necessary

Qty | Item Description | Notes |
--- | --- | --- |
1 | [DOIT ESP32 DEVKIT V1](https://shop.sayal.com/products/1815-ha1?_pos=1&_sid=3067e8a6e&_ss=r)  |  |
1 | [ULN2003 IC](https://shop.sayal.com/products/1814-lc1?_pos=3&_sid=53d498842&_ss=r) | The IC and motor come as a set if ordering from Sayal. | 
1 | [28BYJ-48 Stepper Motor](https://shop.sayal.com/products/1814-lc1?_pos=3&_sid=53d498842&_ss=r) | See above. |
1 | [SH1106 OLED Display](https://shop.sayal.com/products/1814-fa1?_pos=1&_sid=ff4679778&_ss=r) | Some displays swap the position of VCC and GND. Verify the display pinout is compatible with PCB.|
1 | Red LED |  |
1 | Green LED |  |
1 | 10 nF capacitor |  |
2 | Resistor | Choose between 360Ω and 1k Ω to control LED brightness. |
1 | [6-pin USB-C jack](https://shop.sayal.com/products/amtc-1154?_pos=3&_sid=0e93b7e13&_ss=r) |  |
1 | Pointer | 3D print using `pointer-rocket.stp`. |
As Req. | M3 Mounting Hardware | Minimum two sets of screws/washers/nuts to mount the motor. |

# PCB
* The Gerber file includes the text `JLCJLCJLCJLC` to indicate where JLCPCB should print the PCB's ID. Change the text to `WayWayWay` if using PCBWay, or other text according to your manufacturer's information.

# Software
* Connect your ESP32 to your computer and open up `stockticker.ino` using the Arduino IDE.
* Ensure you have selected `DOIT ESP32 DEVKIT V1` as your board.
* Ensure you have selected the correct serial port for communication.
* Install the following libraries required to compile the code:
* In order to fetch real stock market information, you will need to obtain an API key from finnhub.io.
* Change the network and API parameters at the top of the code as necessary such as `symbol`, `key`, `ssid`, `pass`, etc.
* Modify the `TO BE DETERMED` variable to set how frequently the device updates price information.
* Verify and upload the code.

# Soldering and Installation
* Test all components before soldering onto the PCB
* Extract the ULN2003 IC from the driver board that comes with the motor and solder it directly onto the PCB before installing the motor.
* Insulate the pins from the ULN2003 IC on the backside of the PCB and mount the motor to the back of the PCB using M3 hardware so that the shaft protrudes through the 10mm hole in the PCB towards the front.
* Cut the motor wires to length and solder them onto the back of the PCB making sure to pay attention to which color corresponds to which hole.
* Turn the PCB back over to the front and insulate the solder from the motor connections. Afterwards, solder on the OLED display.
* Solder all other components.
* Install the pointer onto the shaft of the motor.
* Use M3 hardware and the four corner holes on the PCB to mount the device however you'd like.


# Operation
* Plug and play. Use power supply that is rated at 5V and can supply at least 2A. A phone charging brick should be sufficient. **DO NOT PLUG IN TWO CABLES AT THE SAME TIME.**
* Manually level the pointer to horizontal before powering the device since the motor does not have absolute positioning. (i.e., it doesn’t remember its positioning between power ons.)
* If the ESP32 is unable to establish a connection to the internet or API, it will automatically enter demo mode and generate random data.

  
  
   
