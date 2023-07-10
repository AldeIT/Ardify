[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com) 
[![forthebadge](https://forthebadge.com/images/badges/open-source.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)

## Introduction

Ardify is a control center that interacts with your Spotify Player using official APIs. It consists of two communicating boards, an Arduino UNO and an ESP32 Thing Plus, each with their respective functions. Arduino handles user interaction, receiving commands through an infrared remote control. The possible operations are:

- Pause and Resume: allow you to stop and resume playback at your convenience.
- Skip: allows you to skip to the next song.
- Previous: allows you to go back to the previous song.
- Volume: allows you to adjust the volume to your liking.

Additionally, connected to the Arduino, there is a 16x02 LCD screen that displays the current song title and the received action. Through a proper connection, Arduino communicates certain directives to the second board to indicate which actions to take.

Once the ESP32 receives the information, it makes the corresponding API calls. At the same time, the board is connected to the cloud via ArduinoIOT, which allows us to save and keep updated statistics viewable on the online platform. The saved statistics include:

- Device Name History: a history of all used devices.
- Skip Counter: a temporary counter for each session that counts "Skip" operations.
- Previous Counter: a temporary counter for each session that counts "Previous" operations.
- Volume: the current volume value.
- Volume History: a graph showing the volume trend during the current session.


![photo_5872829231786999170_y](https://user-images.githubusercontent.com/94229712/231538541-2b12d819-f8f4-4592-9410-5ec3870fd698.jpg)

## Used Components

- Arduino Uno
- ESP32 Thing Plus
- 1602 LCD Screen
- IR Receiver
- IR Remote


## Wiring Diagram

![fritz png](https://user-images.githubusercontent.com/94229712/231539592-a98317e5-cbc8-41c2-8e4b-5e56fb384330.png)

## Wiring

LCD1602:

   - VSS pin to GND or '-' row of breadboard.

   - VDD pin to 3.3V or '+' row of breadboard.

   - V0 pin to GND or '-' row of breadboard.

   - RS pin to Digital Pin #13.

   - RW pin to GND or '-' row of breadboard.

   - E pin to Digital Pin #8.

   - D4 pin to Digital Pin #9.

   - D5 pin to Digital Pin #10.

   - D6 pin to Digital Pin #11.

   - D7 pin to Digital Pin #12.

   - A pin to 5V or '+' row of breadboard.

   - K pin to GND or '-' row of breadboard.



IR RECEIVER:

   - G pin to GND or '-' row of breadboard.

   - R pin to 5V or '+' row of breadboard.

   - Y pin to Digital Pin #7.



ESP32 THING PLUS:

   - GPIO17 (TX1) pin to Digital Pin #0 (RX0).

   - GPIO16 (RX1) pin to Digital Pin #1 (TX0).

   - GND pin to GND or '-' row of breadboard.


## Used Libraries

- LiquidCrystal: for managing the LCD screen
- IRremote: for managing the infrared receiver
- WiFi: for connecting the ESP32 to the internet
- SpotifyArduino: for controlling the Spotify player through APIs
- SoftwareSerial: for establishing serial communication on TX and RX pins
- ArduinoJson: for handling the return values from APIs
- thingProperties: for managing variable updates in the cloud


## References

For managing the Spotify APIs, we relied on an existing library:

  - https://github.com/witnessmenow/spotify-api-arduino

For the operation and management of the LCD screen, we referred to the official documentation:

  - https://buildmedia.readthedocs.org/media/pdf/arduinoliquidcrystal/latest/arduinoliquidcrystal.pdf

For the usage of the IRremote library, we consulted various tutorials including:

  - https://www.pjrc.com/teensy/td_libs_IRremote.html

For the connection and interface with Arduino Cloud, we primarily followed this guide:

  - https://docs.arduino.cc/arduino-cloud/getting-started/esp-32-cloud

