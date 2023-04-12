## 1 Introduzione

Ardify è  un centro di controllo che interagisce con il proprio Player di Spotify mediante l’utilizzo di
API ufficiali. Esso `e composto da due schede comunicanti, un Arduino UNO e un ESP32 Thing Plus,
con relative funzioni. Arduino si occupa dell’interazione con l’utente, dal quale riceve comandi tramite
apposito telecomando ad infrarossi. Le possibili operazioni sono:

- Pause e Resume: permettono di fermare e far ripartire la riproduzione a proprio piacimento;
- Skip: permette di saltare alla canzone successiva;
- Previous: permette di tornare alla canzone precedente;
- Volume: modifica del volume a propria scelta.

Inoltre, collegato all’Arduino, `e presente uno schermo LCD 16x02 il quale mostra a video il titolo della
canzone corrente e l’azione ricevuta. Tramite un opportuno collegamento, Arduino comunica alla seconda
scheda alcune direttive per indicare quali azioni intraprendere.

L’ESP32, una volta ricevute le informazioni, effettua le chiamate API corrispondenti. Contemporaneamente 
la scheda `e connessa al cloud tramite ArduinoIOT, il quale ci permette di salvare e tenere aggiornate
delle statistiche visionabili sulla piattaforma online. Le statistiche salvate sono:

- Storico Device Name: uno storico di tutti i dispositivi utilizzati;
- Contatore Skip: un contatore temporaneo per ogni sessione che conta le operazioni di ”Skip”;
- Contatore Previous: un contatore temporaneo per ogni sessione che conta le operazioni di ”Previous”;
- Volume: valore attuale del volume;
- Storico Volume: un grafico che mostra l’andamento del volume durante la sessione attuale;


![photo_5872829231786999170_y](https://user-images.githubusercontent.com/94229712/231538541-2b12d819-f8f4-4592-9410-5ec3870fd698.jpg)
