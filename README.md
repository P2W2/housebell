# housebell
This is a small script to bring my old and non-smart front [doorbell](https://www.str-elektronik.de/katalog/product/ht2022-3-haustelefon-gong) into the digital age. 

It sends a message via mqtt if someone uses the apartement or house ring. 
Furthermore, MQTT messages can be received to open the house front door.
The ESP32 is powered directly from the bell system, so no external power supply is required.

# Wiring
To detect if someone is using the house or apartement bell, two voltage sensors are wired to the bell.

Futhermore bypasses the relay the opener button to open the house front door.


<img src="https://github.com/P2W2/housebell/blob/readme_featrue/housebell.png" width="800" height="600">
