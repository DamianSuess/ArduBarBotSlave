// 
// 
// 

#include "DrinkMixer.h"

void DrinkMixerClass::SetLiquidToStartPos()
{
	TurnOffAllRelays();
	Serial.println("- Set Liquid To Start Pos");

	for (size_t i = 2; i < 8; i++)
	{
		digitalWrite(soleniod[i], HIGH);
		digitalWrite(_motor, HIGH);
		delay(1050);
		digitalWrite(soleniod[i], LOW);
	}

	CleanCenterTube();
}

void DrinkMixerClass::TurnOffAllRelays()
{
	Serial.println("- Turn off all relays");
	for (size_t i = 0; i < 8; i++)
	{
		digitalWrite(soleniod[i], LOW);
	}
}

void DrinkMixerClass::CleanCenterTube()
{
	Serial.println("- CleanCenterTube");
	TurnOffAllRelays();
	digitalWrite(soleniod[0], HIGH);
	digitalWrite(_motor, HIGH);
	delay(2000);
	digitalWrite(soleniod[0], LOW);
	digitalWrite(_motor, LOW);
}

void DrinkMixerClass::CleanAllTubes()
{
	TurnOffAllRelays();
	Serial.println("- Running clean all tubes");
	for (size_t v = 2; v < 8; v++)
	{
		digitalWrite(soleniod[v], HIGH);
		digitalWrite(_motor, HIGH);
		delay(2500);
		digitalWrite(soleniod[v], LOW);
	}
}

void DrinkMixerClass::RunDrinkOrder(unsigned int amountCentiliter, unsigned int bottleNr) {

	// Open the bottle soleniod
	unsigned short const indexAdjustment = 1;
	digitalWrite(soleniod[bottleNr + indexAdjustment], HIGH);

	Serial.print("  Bottle open :");
	Serial.println(soleniod[bottleNr + indexAdjustment]);

	// Add transport time 2450ms, that is also 1cl, and then multiply 
	unsigned short const
		second = 1000,
		liquidInThePipe = 1,
		transportPipe = 2450;

	unsigned int delayPumpTime = transportPipe + ((amountCentiliter - liquidInThePipe) * second);

	// Give the soliniod time to open
	delay(100);

	// Begin pumping
	digitalWrite(_motor, HIGH);

	delay(delayPumpTime);

	digitalWrite(soleniod[bottleNr + indexAdjustment], LOW);

}

void DrinkMixerClass::init(int tmpairPump, int tmpmotor, int tmpbottle1, int tmpbottle2, int tmpbottle3, int tmpbottle4, int tmpbottle5, int tmpbottle6)
{

	_airPump = tmpairPump;
	_motor = tmpmotor;
	_bottle1 = tmpbottle1;
	_bottle2 = tmpbottle2;
	_bottle3 = tmpbottle3;
	_bottle4 = tmpbottle4;
	_bottle5 = tmpbottle5;
	_bottle6 = tmpbottle6;

	soleniod[0] = _airPump;
	soleniod[1] = _motor;
	soleniod[2] = _bottle1;
	soleniod[3] = _bottle2;
	soleniod[4] = _bottle3;
	soleniod[5] = _bottle4;
	soleniod[6] = _bottle5;
	soleniod[7] = _bottle6;

	


	Serial.println("Init, solenoid pos: ");
	for (size_t i = 0; i < 8; i++)
	{
		Serial.print(soleniod[i]);
		Serial.print("  ");
	}
	Serial.println();
}

DrinkMixerClass DrinkMixer;
