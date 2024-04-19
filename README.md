# Introduction

# Bill of Material
* I sourced all my parts from Sayal but feel free to source from wherever you'd like :)
* Use your judgement when substituting parts ensuring compatability with the code and PCB. Modify the code and gerber as necessary

Qty | Item Description | Notes |
--- | --- | --- |
1 | DEVKIT DOIT V1.1 ESP32 | test |
1 | ULN2003 IC | test | 
1 | 28BYJ-48 Stepper Motor | test |
1 | SH1106 OLED Display | Some displays swap the position of VCC and GND. Verify the display pinout is compatible with PCB.|
1 | Red LED |  |
1 | Green LED |  |
1 | 10 nF capacitor |  |
2 | Resistor | Choose between 360Ω and 1k Ω to control LED brightness |
1 | 6-pin USB-C jack |  |
1 | Pointer |  |
As Req. | M3 Mounting Hardware |  |

# PCB

* The Gerber file includes the text "JLCJLCJLCJLC" to indicate where JLCPCB should print the PCB's ID. Change the text to "WayWayWay" if using PCBWay, or other text according to your manufacturer's information.

# Software

* Use the Arduino IDE to flash the program onto the ESP32.
* Install the following libraries required to compile the code:
* In order to fetch real stock market information, you will need to obtain an API key from finnhub.io
* Change the network and API parameters at the top of the code as necessary such as the symbol, key, ssid, pass, etc.

# Soldering and Installation
<ul>
	<li>Test all components before soldering onto the PCB</li>
	<li>Extract the ULN2003 IC from the driver board that comes with the motor and solder it directly onto the PCB before installing the motor.</li>
	<li>Insulate the pins from the ULN2003 IC on the backside of the PCB and mount the motor to the back of the PCB using M3 hardware so that the shaft protrudes through the 10mm hole in the PCB towards the front.</li>
	<li>Cut the motor wires to length and solder them onto the back of the PCB making sure to pay attention to which color corresponds to which hole.</li>
	<li>Turn the PCB back over to the front and insulate the solder from the motor connections. Afterwards, solder on the OLED display.</li>
 	<li>Solder all other components.</li>
  	<li>Use M3 hardware to mount the PCB however you would like.</li>
   	<li>Install the pointer onto the shaft of the motor.</li>
</ul>

# Operation
<ul>
	<li>Plug and play. Use power supply that is rated at 5V and can supply at least 2A. A phone charging brick should be sufficient.</li>
	<li>Manually level the pointer to horizontal before the power the device since the motor does not have absolute positioning. (i.e., it doesn’t remember its positioning between power ons.)</li>
	<li>If the ESP32 is unable to establish a connection to the internet or API, it will automatically enter demo mode and generate random data.</li>
</ul>
  
  
   
