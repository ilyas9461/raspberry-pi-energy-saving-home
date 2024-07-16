### **Raspberry Pi Energy Saving Home**

Recently, smart homes are popular concepts. Many scenarios are implemented for savings in smart homes. When the saving status is determined by observing the condition of the house using various sensors, lamps, etc. devices are turned off. Movement is usually detected with motion sensors (PIR, etc.). However, motion sensors cannot detect people in the room in case of inactivity. In this case, using a camera provides better results. Using camera and motion sensors together in bright and dark situations provides better results.
<p>
<img src="./assets/20210720_164401_raspberry_pi_circuit_note_fig2a.jpg" width="60%" height="50%" border: 5px solid #555>
</p>

For this purpose, facial recognition was carried out in a room with a Raspberry Pi (RPi) and camera module. As a result of facial recognition, if there is no one in the room and this is the case for a certain period of time, the lamp and other working electronic devices in the room are turned off with the shutdown information sent wirelessly to the lamp-socket module.

When facial recognition information is obtained from the motion sensor or the RPi camera, the switching information is sent wirelessly to the lamp-socket module.


NRF24L01 wireless module and relay module were used together with Arduino Leonardo as the lamp module.

<p>
<img src="./assets/lamba_modul.jpg" width="70%" height="70%" border: 5px solid #555>
</p>


Thus, when there is no one in a room, the lamps and electronic devices in that room do not work unnecessarily. This will save electricity at home or in any office-like environment.

In addition, all the lamps in the house will be able to turn on and off automatically without the need for buttons. If an RPi module with Wi-Fi feature is used, the situation at home can be monitored via the web and the system can also be used for home security.

Here, RPi is used for facial recognition via camera and web connection if necessary. In terms of cost, RPi that meets these basic features can be selected. Additionally, Arduino UNO was used with an NRF24L01 wifi module for ease of programming with RPi. RPi receives and sends wireless commands via the Arduino-NRF module.

While operations in RPi (Face recognition, USB-serial communication, etc.) are carried out with Python language, C++ language is used in Arduino cards.

- Rasberry Pi 3B
- Python programming language
- NRF24L01 wifi 
- Smart Home