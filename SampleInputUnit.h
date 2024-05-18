#ifndef SAMPLEINUNIT_H
#define SAMPLEINUNIT_H
#include <Beginner_LED.h>


// sample input unit: BASIC
class basicInputUnit
{
protected:
	// this is just a sample; it is essentially empty
	int detection_pct;
public:	
	basicInputUnit() { detection_pct = 50; }
	virtual bool detectInput()
	{
		bool result = false;
		if (random(0, 100) <= detection_pct)
			result = true;
		if (result)
			Serial.println("Basic input function: detection occurred");
		else
			Serial.println("Basic input function: no detection");
		return result;
	}
	void setUpBasicInputUnit(int inp1, int inp2)
	{
		Serial.println("Mock setup function for basicInputUnit");
		Serial.print(" Input 1 val: ");
		Serial.println(inp1);
		Serial.print(" Input 2 val: ");
		Serial.println(inp2);
	}

	virtual void pressButton(ana_LED feedbackLED[], int playerInput) {	//User inputs each press button and the LED associated with the press button lights up 
		feedbackLED[playerInput].switch_on();
		delay(1000);
		feedbackLED[playerInput].switch_off();
	}
};


// sample input unit: ADVANCED
class advancedInputUnit : public basicInputUnit
{
public:
	advancedInputUnit() { detection_pct = 80; }
	virtual bool detectInput()
	{
		bool result = false;
		if (random(0, 100) <= detection_pct)
			result = true;
		if (result)
			Serial.println("Advanced input function: detection occurred");
		else
			Serial.println("Advanced input function: no detection");
		return result;
	}
	void setUpAdvancedInputUnit(int inp1, int inp2, int inp3)
	{
		Serial.println("Mock setup function for advancedInputUnit");
		Serial.print(" Input 1 val: ");
		Serial.println(inp1);
		Serial.print(" Input 2 val: ");
		Serial.println(inp2);
		Serial.print(" Input 3 val: ");
		Serial.println(inp3);
	}
	void pressButton(ana_LED feedbackLED[], int playerInput) {	//User inputs each press button and the LED associated with the press button lights up
		feedbackLED[playerInput].switch_on();
		delay(1000);
		feedbackLED[playerInput].switch_off();
	}
};

#endif