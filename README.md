# housebell
This is a small script to bring my old and non-smart front [doorbell](https://www.str-elektronik.de/katalog/product/ht2022-3-haustelefon-gong) into the digital age. 

It sends a message via mqtt if someone uses the apartement or house ring. 
Furthermore, MQTT messages can be received to open the house front door.
The ESP32 is powered directly from the bell system, so no external power supply is required.

There are many different bells that follow the same or similar logic. So I hope that this Reposetory can perhaps help one or the other. 
Please be careful when installing and remember to protect your MQTT broker, or whatever you use for communication, from unwanted access. 

# Wiring
To detect if someone is using the house or apartement bell, two voltage sensors are wired to the bell.
The first sensor is wired between VCC and the Input of the apartment bell at G1. The Analog pin "s" connects to PIN 34 on the ESP module.
The second sensor is wired between VCC and the Input of the house bell at G3 and the Analog pin "s" connects to PIN 35 on the ESP module. 
Both sensor are connected on the input site with the ground wire of the bell and on the output site with a GND PIN on the ESP module.

Futhermore a relay bypasses the opener button to enable remotly open the house front door.
This is done by connecting the wire in the bell at position 1 and on the other end with the relay. The relay is then connected with the ESP module trough PIN G25 and ground.
The ESP module is connected between the N conductor and the 5V line.
Last the ESP module must be connected to the ground line.

<img src="https://github.com/P2W2/housebell/blob/readme_featrue/housebell.png" width="800" height="600">
