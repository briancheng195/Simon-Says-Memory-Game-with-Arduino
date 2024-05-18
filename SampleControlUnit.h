#ifndef SAMPLECTRLNIT_H
#define SAMPLECTRLNIT_H

#include <IntervalCheckTimer.h>
#include <Debounce_Button.h>
#define buzzerPin 3

basicOutputUnit outputU;
basicInputUnit inputU;

int length = 3;				// Initial length of the random generated sequence by Simon Says (initial game difficulty)
int TimeLimit = 3000;		// Time limit of 3 seconds for each input cue
int countUserScore = 0;		// User score tally
int countSimonScore = 0;	// Simon score tally

// sample out unit: BASIC
class basicControlUnit
{
protected:
	// this is just a sample; it is essentially empty
	IntervalCheckTimer inputchk;
	int sequence[4];

public:	
	basicControlUnit()
	{
		inputchk.setInterCheck(1000);
	}
	bool isTimeToChekInput()
	{
		return inputchk.isMinChekTimeElapsedAndUpdate();
	}
	
	virtual void SequenceGenerator(ana_LED feedbackLED[]) 	// Randomly generating Simon Says' 3-digit sequence
	{
		sequence[0] = random(0, 4);
		for (int i = 1; i < length; i++) {
    		int new_num = random(0, 4);
    		while (new_num == sequence[i-1]) {
       	 		new_num = random(0, 4);
    		}
   			sequence[i] = new_num;
		}

  		Serial.print("Simon Says: ");						// Prints out Simon Says' sequence on the serial monitor
  			for (int i = 0; i < length; i++) { 
    			Serial.print(sequence[i]);
    			Serial.print(" ");
  		}
		outputU.displayGame(feedbackLED, sequence, length); // Sends the sequence to the class outputU for the LEDs to light up accordingly to the sequence
	}

	virtual void UserSays(ana_LED feedbackLED[], debounceButton test_button[]) 
	{ 
	int UserInput[length];
	int sequenceIndex = 0;
	unsigned long StartTime = millis();
	Serial.println(" ");

	while (millis() - StartTime < TimeLimit){		// Taking note of the time with millis() and the startTime is the initial time
		for (int i = 0; i < 4; i++) {				// Records the time taken by the user's each input and ensure it does not exceed the time limit of 3 seconds
			if (test_button[i].checkNewInput()) {
				Serial.print("button ");
				Serial.print(i);
				Serial.println(" pressed");
				inputU.pressButton(feedbackLED, i);	// LED lights up accordingly for each input button the user presses
				UserInput[sequenceIndex++] = i;
				StartTime = millis();				// Resets the time after the user inputs each press button
			}
		}
	}

  	if (sequenceIndex == length) {					// Ensures that the user inputs a 3-digit sequence
		Serial.print("User Input Sequence: ");	// Once the user inputs his digit sequence, print out his input sequence
		for (int i = 0; i < length; i++) {
     	Serial.print(UserInput[i]);
      	Serial.print(" ");
    	}
    Serial.println();
	} 

	bool correct = true;
  	for (int i = 0; i < length; i++){
    	if (UserInput[i] != sequence[i]){	// Checks whether the user's input sequence is correct/wrong according to Simon Says
      		correct = false;
    	}
  	}
  	if (correct) {
    	Serial.print("Correct! You won this round."); // If correct, User wins this round
		countUserScore += 1;
		Serial.println("");
		Serial.print("Your Score: ");
		Serial.println(countUserScore);
		Serial.print("Simon's Score: ");
		Serial.println(countSimonScore);
  	}
  	else {
    	Serial.print("Incorrect! Simon won this round."); // If wrong, Simon wins this round
		countSimonScore += 1;
		Serial.println("");
		Serial.print("Your Score: ");
		Serial.println(countUserScore);
		Serial.print("Simon's Score: ");
		Serial.println(countSimonScore);
  	}
		sequenceIndex = 0;	// Resets the sequenceIndex, so that user can start his sequence input again for the next round
	}

	void matchResult()		// Keeps track of the scores of user and Simon in each game (best of 3) and determines the winner of the match
		{	
			if (countUserScore >= 2) {
				Serial.println("");
				Serial.print("Your Score: ");
				Serial.println(countUserScore);
				Serial.print("Simon's Score: ");
				Serial.println(countSimonScore);
				Serial.println("You won!");
				countUserScore = 0;
				countSimonScore = 0;
			}
			
			if (countSimonScore >= 2) {
				Serial.println("");
				Serial.print("Your Score: ");
				Serial.println(countUserScore);
				Serial.print("Simon's Score: ");
				Serial.println(countSimonScore);
				Serial.println("Simon won!");
				countUserScore = 0;
				countSimonScore = 0;
			}
		}
	bool score()	{		// Displays the initial scores before the start of each round
		Serial.println("");
		Serial.print("Your Score: ");
		Serial.println(countUserScore);
		Serial.print("Simon's Score: ");
		Serial.println(countSimonScore);
	}
};

advancedInputUnit advinU;
advancedOutUnit advoutU;

// sample control unit: ADVANCED
class advancedControlUnit : public basicControlUnit
{
public:
	advancedControlUnit()
	{
		inputchk.setInterCheck(500);
	}
	void SequenceGenerator(ana_LED feedbackLED[]) 
	{
		sequence[0] = random(0, 4);
		for (int i = 1; i < length; i++) {
    		int new_num = random(0, 4);
    		while (new_num == sequence[i-1]) {
       	 		new_num = random(0, 4);
    		}
   			sequence[i] = new_num;
		}

  		Serial.print("Simon Says: ");
  			for (int i = 0; i < length; i++) { 
    			Serial.print(sequence[i]);
    			Serial.print(" ");
  		}
		outputU.displayGame(feedbackLED, sequence, length); 
	}

	void UserSays(ana_LED feedbackLED[], debounceButton test_button[]) 
	{
	int UserInput[length];
	int sequenceIndex = 0;
	unsigned long StartTime = millis();
	Serial.println(" ");
	pinMode(buzzerPin, OUTPUT);			// Implementation of the buzzer

	while (millis() - StartTime < TimeLimit){		
		for (int i = 0; i < 4; i++) {				
			if (test_button[i].checkNewInput()) {
				Serial.print("button ");
				Serial.print(i);
				Serial.println(" pressed");
				inputU.pressButton(feedbackLED, i);	
				UserInput[sequenceIndex++] = i;
				StartTime = millis();				
			}
		}
	}

  	if (sequenceIndex == length) {			// Once the user inputs his digit sequence, print out his input sequence
		Serial.print("User input Sequence: ");
		for (int i = 0; i < length; i++) {
     	Serial.print(UserInput[i]);
      	Serial.print(" ");
    	}
    Serial.println();
	} 

	bool correct = true;
  	for (int i = 0; i < length; i++){
    	if (UserInput[i] != sequence[i]){	// Checks whether the user's input sequence is correct/wrong according to Simon Says
      		correct = false;
    	}
  	}
  	if (correct) {
    	Serial.print("Correct! You won this round."); // If correct, User wins this round
		countUserScore += 1;
		Serial.println("");
		Serial.print("Your Score: ");
		Serial.println(countUserScore);
		Serial.print("Simon's Score: ");
		Serial.println(countSimonScore);
  	}
  	else {
    	Serial.print("Incorrect! Simon won this round."); // If wrong, Simon wins this round
		tone(buzzerPin, 1000);							  // Buzzer would play a 1kHz pitch sound when Simon wins a game round
		delay(500);										  // Duration of pitch sound by the buzzer
		noTone(buzzerPin);								  // Buzzer stops playing a pitch sound
		countSimonScore += 1;
		Serial.println("");
		Serial.print("Your Score: ");
		Serial.println(countUserScore);
		Serial.print("Simon's Score: ");
		Serial.println(countSimonScore);
  	}
		sequenceIndex = 0;	// Resets the sequenceIndex, so that user can start his sequence input again for the next round
	}

	void matchResult(ana_LED feedbackLED[], debounceButton test_button[])	
		{	
			pinMode(buzzerPin, OUTPUT);						// Implementation of the buzzer
			if (countUserScore >= 5) {						// Best of 8 games to determine the winner
				tone(buzzerPin, 3000);						// Buzzer would play a higher pitch sound of 3kHz when user wins a match
				delay(500);
				noTone(buzzerPin);
				Serial.println("");
				Serial.print("Your Score: ");
				Serial.println(countUserScore);
				Serial.print("Simon's Score: ");
				Serial.println(countSimonScore);
				Serial.println("You won!");
				countUserScore = 0;
				countSimonScore = 0;
				if (length < 4){
					length++;
				}
			}
			
			if (countSimonScore >= 5) {
				tone(buzzerPin, 1000);						// Buzzer would play a lower pitch sound of 1kHz when Simon wins a match
				delay(500);
				noTone(buzzerPin);
				Serial.println("");
				Serial.print("Your Score: ");
				Serial.println(countUserScore);
				Serial.print("Simon's Score: ");
				Serial.println(countSimonScore);
				Serial.println("Simon won!");
				countUserScore = 0;
				countSimonScore = 0;
				if (length > 2){
					length--;
				}
			}

			if (countUserScore == 4 && countSimonScore == 4){	// Tiebreaker feature when User and Simon drew 4-4
				score();
    			advoutU.countDown();
    			SequenceGenerator(feedbackLED);
    			advoutU.countDown();
    			UserSays(feedbackLED, test_button);
				matchResult(feedbackLED, test_button);
			}
		}

	bool score()	{
		Serial.println("");
		Serial.print("Your Score: ");
		Serial.println(countUserScore);
		Serial.print("Simon's Score: ");
		Serial.println(countSimonScore);
	}
};

#endif