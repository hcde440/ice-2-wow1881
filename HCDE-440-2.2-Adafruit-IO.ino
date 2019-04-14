// Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

// HCDE 440 19sp ICE #2 submission for Alex Banh, ajb9702

#include "config.h"

// defines the button pin to be pin 5 on our ESP8266
#define BUTTON_PIN 5
// defines the photocell pin to be the analog pin on our ESP8266
#define PHOTOCELL_PIN A0

// boolean variable that represents the current state of the button
// a false value means the button is not pressed, true means that it is
bool current = false;

// boolean variable that represents the current value of the photocell.
// photocell values range from 0 to 1024, with 1024 being the brightest.
int photocurrent = 0;

// set up the 'digital' feed to our adafruitIO dashboard with the name "digital"
AdafruitIO_Feed *digital = io.feed("digital");

// set up the 'analog' feed to our adafruitIO dashboard with the name "analog"
AdafruitIO_Feed *analog = io.feed("analog");

void setup() {

  // set button pin as an input
  pinMode(BUTTON_PIN, INPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

  // io.run() keeps the client connected to
  // io.adafruit.com and processes any incoming data.
  io.run();

  // grab the current state of the button.
  // we have to flip the logic because we are
  // using a pullup resistor.
  if(digitalRead(BUTTON_PIN) == LOW)
    current = true;
  else
    current = false;

  // grab the current state of the photocell
  photocurrent = analogRead(PHOTOCELL_PIN);

  // save/publish the current state to the 'digital' feed on adafruit io
  Serial.print("sending button -> ");
  Serial.println(current);
  digital->save(current);

  // save/publish the current state to the analog feed
  Serial.print("sending -> ");
  Serial.println(photocurrent);
  analog->save(photocurrent);

  // Forces at 2 second delay between readings to prevent overloading
  // of data sent to the adafruitIO dashboard.
  delay(2000);

}
