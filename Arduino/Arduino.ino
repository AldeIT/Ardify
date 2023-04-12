/*
 * @Brief: Arduino Prototyping Course 2023 UNIVR -- Arduino/C++ Code.
 * @Author: Alessandro Aldegheri VR471346, Michele Cipriani  VR471337
 */

// including the LCD's library to use its functions.
#include <LiquidCrystal.h>

// including the IR Remote library to use its functions.
#include <IRremote.h>

// declaring the LCD pins.
LiquidCrystal lcd(13, 8, 9, 10, 11, 12);

// declaring the IR receiever pin to 7.
const int recv_pin = 7;

// code to create a receiver object using the 'IRrecv' function.
IRrecv irrecv(recv_pin);

// code to declare a results object.
decode_results results;

// creating a variable to store the song name that is sent from the ESP32 through the serial port.
String readSong = " ";

//debug
String oldSong = "";

// to find out if the song is to be stop or to resume
int flag;
int count;

// SETUP
void setup()
{

  // code to enable the receiver that we created.
  irrecv.enableIRIn();

  // initializing the lcd
  lcd.begin(16, 2);

  // initializing the flags
  flag = 0;
  count = 1;

  // initializing the serial monitor.
  Serial.begin(9600);

  // changing the serial's timing to wait for stream data to 0.
  Serial.setTimeout(0);
}

// MAIN-LOOP
void loop()
{

  delay(900);

  // updating the created variable to read the song from ESP32
  readSong = Serial.readString();
  if (readSong!=""){
    oldSong = readSong;
  }
  // setting the cursor on the 1602 LCD
  lcd.setCursor(0, 1);

  // print the song to the LCD display
  if (readSong==""){
    lcd.print(oldSong);
  }else {
    lcd.print(readSong);
  }
  

  delay(400);

  // creating an if-statement to decode the signal sent from the transmitter, which is the remote. We store the signal in the 'results' variable.
  if (irrecv.decode())
  {

    // withdrawing the exadecimal value sent by the remote.
    results.value = irrecv.decodedIRData.decodedRawData;

    // creating a switch to compare the value to multiple cases.
    switch (results.value)
    {

    // CASE: 1. represents the pause button.
    case 0xEA15FF00:

      // setting the cursor on the 1602 LCD
      lcd.setCursor(0, 0);

      // printing the keyword 'stop' to the serial monitor for recognition by the ESP32 script.
      Serial.println("stop");

      // checking if the song is being paused or resumed
      if (count % 2 == 0 && flag == 0)
      {
        // printing the 'Resume' string on the 1602 LCD.
        lcd.print("Resume");
      }
      else
      {
        // printing the 'Paused' string on the 1602 LCD.
        lcd.print("Paused");
        flag = 0;
      }

      count++;
      delay(250);
      break;

    // CASE: 2. represents the previous button.
    case 0xF807FF00:

      // printing the keyword 'back' to the serial monitor for recognition by the ESP32  script.
      Serial.println("back");

      // setting the cursor on the 1602 LCD
      lcd.setCursor(0, 0);

      // printing the 'Playing Previous:' string on the 1602 LCD.
      lcd.print("Playing Previous:");

      delay(250);
      flag = 1;
      break;

    // CASE: 3. represents the forward button.
    case 0xF609FF00:

      // printing the keyword 'next' to the serial monitor for recognition by the ESP32 script.
      Serial.println("next");

      // setting the cursor on the 1602 LCD
      lcd.setCursor(0, 0);

      // code to print 'Playing Next:' string on the 1602 LCD.
      lcd.print("Playing Next:");

      delay(250);
      flag = 1;
      break;

    // CASE: 4. represents the volume up button.
    case 0xBF40FF00:

      // printing the keyword 'up' to the serial monitor for recognition by the ESP32 script.
      Serial.println("up");

      // setting the cursor on the 1602 LCD
      lcd.setCursor(0, 0);

      // code to print 'Volume up' string on the 1602 LCD.
      lcd.print("Volume up");

      delay(250);
      break;

    // CASE: 5. represents the volume down button.
    case 0xE619FF00:

      // printing the keyword 'down' to the serial monitor for recognition by the ESP32 script.
      Serial.println("down");

      // setting the cursor on the 1602 LCD
      lcd.setCursor(0, 0);

      // code to print 'Volume down' string on the 1602 LCD.
      lcd.print("Volume down");

      delay(250);
      break;
    }

    // code to allow the receiver resume for the next data sent through the transmitter.
    irrecv.resume();
  }

  // creating a for-loop to add the scrolling effect.
  for (int counter = 0; counter < 16; counter++)
  {

    // scrolling one position to the right.
    lcd.scrollDisplayRight();

    // adding a delay to create an effect.
    delay(150);
  }
  
  // clearing the lcd after each iteration of the main-loop.
  lcd.clear();
}
