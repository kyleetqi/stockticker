# Introduction

# PCB
<ul>
	<li>The Gerber file includes the text "JLCJLCJLCJLC" to indicate where JLCPCB should print the PCB's ID. Change the text to "WayWayWay" if using PCBWay, or other text according to your manufacturer's information.</li>	
</ul>

# Software
<ul>
	<li>Use the Arduino IDE to flash the program onto the ESP32.</li>
	<li>Install the following libraries required to compile the code:</li>
	<li>In order to fetch real stock market information, you will need to obtain an API key from finnhub.io</li>
	<li>Change the network and API parameters at the top of the code as necessary such as the symbol, key, ssid, pass, etc. </li>
</ul>
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
  
  
   
