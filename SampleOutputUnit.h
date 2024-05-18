#ifndef SAMPLEOUTUNIT_H
#define SAMPLEOUTUNIT_H
#include <string.h>
#define buzzerPin 3

// sample out unit: BASIC
class basicOutputUnit
{
protected:
	// this is just a sample; it is essentially empty
public:		
	virtual bool displayOutput()
	{
		Serial.println("Basic output funciton");
	}
	void countDown()	// Beginning of the Game
		{	
			Serial.println("User get ready!")	;
			for (int i = 3;  i > 0; i--){								// Counts down from 3 (3 second countdown)
				Serial.println(i);
				delay(1000);
			}
		Serial.println("Game Starts!");
		}

	void displayGame(ana_LED feedbackLED[], int sequence[], int length)	// LEDs light up accordingly based on the user's input with the press buttons during each round 
		{
			for (int i = 0; i < length; i++){
				feedbackLED[sequence[i]].switch_on();					// Switches on the corresponding LED for 1 second
				delay(1000);											// Tcue = 1000
				feedbackLED[sequence[i]].switch_off();					
				delay(500);												// Tcue/2

			}
		}
};

// sample out unit: ADVANCED
class advancedOutUnit : public basicOutputUnit
{
public:
	virtual bool displayOutput()
	{
		Serial.println("Advanced output funciton <<<< >>>>> ");
	}
	void countDown()	// Beginning of the Game
	{	
		pinMode(buzzerPin, OUTPUT);										// Implementation of the buzzer
		Serial.println("User get ready!")	;
		for (int i = 3;  i > 0; i--){
			Serial.println(i);
			delay(1000);
		}
	Serial.println("Game Starts!");
	tone(buzzerPin, 500);												// Buzzer would play a 0.5kHz pitch sound since once countdown finishes, to alert user the game has started
	delay(500);
	noTone(buzzerPin);
	}
};
#endif