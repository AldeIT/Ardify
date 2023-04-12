/*
 * @Brief: Arduino Prototyping Course 2023 UNIVR -- ESP32/C++ Code.
 * @Author: Alessandro Aldegheri VR471346, Michele Cipriani  VR471337
 */

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "SpotifyArduino.h"
#include "SpotifyArduinoCert.h"
#include "arduino_secrets.h"
#include "thingProperties.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// your network SSID (name)
char ssid[] = SECRET_SSID;

// your network password
char password[] = SECRET_OPTIONAL_PASS;

// Your client ID of your spotify APP
char clientId[] = "";

// Your client Secret of your spotify APP (Do Not share this!)
char clientSecret[] = "";

// Spotify API Library Parameters
#define SPOTIFY_MARKET "IE"
#define SPOTIFY_REFRESH_TOKEN "AQAd_noWVIFyplSEaBU4ibuigCOqQFzNBTAUF7EEGzuHGAMiI219Ruy4L1SvBYo9tNaNlrUoAzVwILVGrl_r7dxQXfylNa2c8YxDj8bbHkopz19AqmwnOp9c0I9tCTxQLFw"

// Variables Declaration
String device;
String command;
int count;
int volume_AUX;
WiFiClientSecure client;

// Creating Spotify API Object
SpotifyArduino spotify(client, clientId, clientSecret, SPOTIFY_REFRESH_TOKEN);

void setup()
{
  // Initializing variables
  volume_AUX = 0;
  count = 0;

  // Debug purposes Serial
  Serial.begin(9600);

  // Arduino/ESP32 Communication Serial (TX/RX)
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  // Connection to wifi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  // Setting the Spotify Certificate
  client.setCACert(spotify_server_cert);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Arduino IOT Cloud Variables
  volume = 0;
  next_song = 0;
  previous_song = 0;
  device_name = "";
}

void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying)
{
  // Sending to Arduino the current TrackName
  Serial2.print(currentlyPlaying.trackName);
}

void settingPlayerDetails(PlayerDetails playerDetails)
{
  // Setting the device name and the current Volume
  device = playerDetails.device.name;
  volume_AUX = playerDetails.device.volumePercent;
}

void loop()
{

  // Updating the Arduino Cloud Variables
  ArduinoCloud.update();

  // Spotify API Functions
  spotify.getCurrentlyPlaying(printCurrentlyPlayingToSerial, SPOTIFY_MARKET);
  spotify.getPlayerDetails(settingPlayerDetails, SPOTIFY_MARKET);

  // Setting the Arduino Cloud Volume to the API Volume, same for the device
  volume = volume_AUX;
  device_name = device;

  // Reading the command sent by the Arduino on the serial port
  command = Serial2.readString();

  // If the command is Stop
  if (command.indexOf("stop") >= 0)
  {
    // Checking if the song is to be paused or resumed
    if (count % 2 == 0)
    {
      // Spotify API to pause the song
      if (!spotify.pause())
      {
        Serial.println("done!");
      }
    }
    else
    {
      // Spotify API to play the song
      if (!spotify.play())
      {
        Serial.println("done!");
      }
    }
    count++;
  } // If the command is Next
  else if (command.indexOf("next") >= 0)
  {
    // Spotify API to play the next song
    if (!spotify.nextTrack())
    {
      // Updating the counter
      next_song++;
      Serial.println("done!");
    }
  } // If the command is Back
  else if (command.indexOf("back") >= 0)
  {
    // Spotify API to go back to the previous song
    if (!spotify.previousTrack())
    {
      // Updating the counter
      previous_song++;
      Serial.println("done!");
    }
  } // If the command is Up
  else if (command.indexOf("up") >= 0)
  {
    // Getting the current volume
    spotify.getPlayerDetails(settingPlayerDetails, SPOTIFY_MARKET);
    // Spotify API to set the volume of the player
    if (!spotify.setVolume(volume_AUX + 10 /*10% more*/))
    {
      Serial.println("done!");
    }
  } // If the command is Down
  else if (command.indexOf("down") >= 0)
  {
    // Getting the current volume
    spotify.getPlayerDetails(settingPlayerDetails, SPOTIFY_MARKET);
    // Spotify API to set the volume of the player
    if (!spotify.setVolume(volume_AUX - 10 /*10% less*/))
    {
      Serial.println("done!");
    }
  }

  delay(1250);
}
