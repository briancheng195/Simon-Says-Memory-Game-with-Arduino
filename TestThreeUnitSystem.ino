#include <SampleThreeUnitSystem.h>
#include <Debounce_Button.h>
#include <Beginner_LED.h>

TU_basicSystem testSys;
//TU_advancedSystem testSys;

const int number = 4;
debounceButton test_button[number];
ana_LED feedbackLED[number];
int in[number] = {4,5,7,8};            // Pin connections of Press Buttons with Arduino
int cue[number] = {6,9,10,11};         // Pin connections of LEDs with Arduino

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < number; i++) {   // Setting up Press Buttons with Debounce_Button.h library
    test_button[i].setInputPin(in[i]); 
    test_button[i].setDebounceTime(10);
    test_button[i].setLongpushTime(500);
    feedbackLED[i].setup_LED(cue[i]);  // Setting up the buzzer (used for advanced features)
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  testSys.progressSystem();
  testSys.SimonSays(feedbackLED, test_button, number);  // Running the Simon Says match sequence from the SampleThreeUnit.h library
}

