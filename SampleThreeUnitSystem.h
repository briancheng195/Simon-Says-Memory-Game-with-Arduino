#ifndef SAMPLETHREEUNITSYS_h
#define SAMPLETHREEUNITSYS_h

#include "SampleInputUnit.h"
#include "SampleOutputUnit.h"
#include "SampleControlUnit.h"


class TU_basicSystem
{
protected:
	// this is just a sample; it is essentially empty
	basicInputUnit inU;
	basicOutputUnit outU;
	basicControlUnit ctrlU;
public:
	void progressSystem()
	{
		bool result = false;
		if (ctrlU.isTimeToChekInput())
			result = inU.detectInput();
		if (result)
			outU.displayOutput();
	}

	void SimonSays(ana_LED feedbackLED[], debounceButton test_button[], int number)		// To execute Simon Says match for basic features
		{	
			for (int i=1; i <= 3; i++){													// Best of 3 games
				ctrlU.score();
    			outU.countDown();
    			ctrlU.SequenceGenerator(feedbackLED);
    			outU.countDown();
    			ctrlU.UserSays(feedbackLED, test_button);
				ctrlU.matchResult();
  			}	
		}
};


class TU_advancedSystem
{
protected:
	// this is just a sample; it is essentially empty
	advancedInputUnit inU;
	advancedOutUnit outU;
	advancedControlUnit ctrlU;
public:
	void progressSystem()
	{
		bool result = false;
		if (ctrlU.isTimeToChekInput())
			result = inU.detectInput();
		if (result)
			outU.displayOutput();
	}
	void SimonSays(ana_LED feedbackLED[], debounceButton test_button[], int number)		// To execute Simon Says match for advanced features
	{	
		for (int i=1; i <= 8; i++){														// Best of 8 games
			ctrlU.score();
    		outU.countDown();
    		ctrlU.SequenceGenerator(feedbackLED);
    		outU.countDown();
    		ctrlU.UserSays(feedbackLED, test_button);
			ctrlU.matchResult(feedbackLED, test_button);
  			}	
	}
};	


#endif