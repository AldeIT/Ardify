## Introduzione

Ardify è un centro di controllo che interagisce con il proprio Player di Spotify mediante l’utilizzo di
API ufficiali. Esso è composto da due schede comunicanti, un Arduino UNO e un ESP32 Thing Plus,
con relative funzioni. Arduino si occupa dell’interazione con l’utente, dal quale riceve comandi tramite
apposito telecomando ad infrarossi. Le possibili operazioni sono:

- Pause e Resume: permettono di fermare e far ripartire la riproduzione a proprio piacimento;
- Skip: permette di saltare alla canzone successiva;
- Previous: permette di tornare alla canzone precedente;
- Volume: modifica del volume a propria scelta.

Inoltre, collegato all’Arduino, è presente uno schermo LCD 16x02 il quale mostra a video il titolo della
canzone corrente e l’azione ricevuta. Tramite un opportuno collegamento, Arduino comunica alla seconda
scheda alcune direttive per indicare quali azioni intraprendere.

L’ESP32, una volta ricevute le informazioni, effettua le chiamate API corrispondenti. Contemporaneamente 
la scheda è connessa al cloud tramite ArduinoIOT, il quale ci permette di salvare e tenere aggiornate
delle statistiche visionabili sulla piattaforma online. Le statistiche salvate sono:

- Storico Device Name: uno storico di tutti i dispositivi utilizzati;
- Contatore Skip: un contatore temporaneo per ogni sessione che conta le operazioni di ”Skip”;
- Contatore Previous: un contatore temporaneo per ogni sessione che conta le operazioni di ”Previous”;
- Volume: valore attuale del volume;
- Storico Volume: un grafico che mostra l’andamento del volume durante la sessione attuale;


![photo_5872829231786999170_y](https://user-images.githubusercontent.com/94229712/231538541-2b12d819-f8f4-4592-9410-5ec3870fd698.jpg)

## Componenti Utilizzati

- Arudino Uno
- ESP32 Thing Plus
- Schermo LCD 1602
- IR Receiver
- IR Remote

## Schema Collegamenti

![fritz png](https://user-images.githubusercontent.com/94229712/231539592-a98317e5-cbc8-41c2-8e4b-5e56fb384330.png)

## Cablaggio

LCD1602:

   -VSS pin to GND or '-' row of breadboard.

   -VDD pin to 3.3V or '+' row of breadboard.

   -V0 pin to GND or '-' row of breadboard.

   -RS pin to Digital Pin #13.

   -RW pin to GND or '-' row of breadboard.

   -E pin to Digital Pin #8.

   -D4 pin to Digital Pin #9.

   -D5 pin to Digital Pin #10.

   -D6 pin to Digital Pin #11.

   -D7 pin to Digital Pin #12.

   -A pin to 5V or '+' row of breadboard.

   -K pin to GND or '-' row of breadboard.



IR RECEIVER:

   -G pin to GND or '-' row of breadboard.

   -R pin to 5V or '+' row of breadboard.

   -Y pin to Digital Pin #7.



ESP32 THING PLUS:

   -GPIO17 (TX1) pin to Digital Pin #0 (RX0).

   -GPIO16 (RX1) pin to Digital Pin #1 (TX0).

   -GND pin to GND or '-' row of breadboard.


## Librerie utilizzate

- LiquidCrystal: per la gestione dello schermo LCD
- IRremote: per la gestione del ricevitore ad infrarossi
- Wifi: per poter connettere l’esp32 a internet
- SpotifyArduino: per gestire il player di Spotify tramite API
- SoftwareSerial: per aprire una comunicazione seriale sui pin TX e RX
- ArduinoJson: per la gestione dei valori di ritorno delle API
- thingProperties: per gestire l’aggiornamento delle variabili in cloud


## Bibliografia

Per la gestione delle API di Spotify ci siamo appoggiati ad una libreria già esistente:

  -https://github.com/witnessmenow/spotify-api-arduino

Per il funzionamento e la gestione dello schermo LCD ci siamo appoggiati alla documentazione ufficiale:

  -https://buildmedia.readthedocs.org/media/pdf/arduinoliquidcrystal/latest/arduinoliquidcrystal.pdf

Per l’utilizzo della libreria IRreceiver ci siamo appoggiati a vari tutorial tra cui:

  -https://www.pjrc.com/teensy/td_libs_IRremote.html

Per il collegamento e l’interfaccia ad Arduino Cloud abbiamo principalmente seguito questa guida:

  -https://docs.arduino.cc/arduino-cloud/getting-started/esp-32-cloud

