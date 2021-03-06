#include "Communication.h"
#include "Ingridients.h"
#include "Communication.h"

#define ledLamp 2
String readString;

Container myContainers[6];
CommunicationClass btCommunication;


void setup()
{
	Serial3.begin(230400);
	Serial.begin(115200);
	pinMode(ledLamp, OUTPUT);
	digitalWrite(ledLamp, LOW);
	SetMockDATA();
}


int count = 0;
void loop()
{

	//SendIngridents();
	//ReadBytesOfArray();
	//ReadCommand();
	//SendMessageOnCommand();

	if (Serial3.available())
	{
		int msg = Serial3.read();
		switch (msg)
		{
		case 'e':
			if (count >0)
			{
				return;
			}
			btCommunication.SendIngridients(myContainers);
			count++;
			break;
		default:
			Serial.print("Unkown command sent: ");
			Serial.println(msg);
			break;
		}
	}
}
// SET MOCKDATA
void SetMockDATA() {
	if (!myContainers[0].SetName("Margaritas") ||
		!myContainers[1].SetName("Vodka") ||
		!myContainers[2].SetName("Tequila") ||
		!myContainers[3].SetName("Whiskey") ||
		!myContainers[4].SetName("Braunstein Gylden") ||
		!myContainers[5].SetName("Ekologiska Osterlensnapsar"))
	{
		Serial.print("naming error");
	}

	for (short i = 0; i < 6; i++)
	{
		myContainers[i].SetAmount(random(100, 2500));
	}

}


// GET DATA
void ReadBytesOfArray() {

#define MAX_MILLIS_TO_WAIT 1000  //or whatever
#define MessageArrayLength 2
	unsigned long starttime;

	starttime = millis();

	while ((Serial.available() < MessageArrayLength) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT))
	{
		// hang in this loop until we either get 9 bytes of data or 1 second
		// has gone by
	}
	if (Serial.available() < MessageArrayLength)
	{
		// the data didn't come in - handle that problem here
		Serial.println("ERROR - Didn't get 9 bytes of data!");
		Serial.flush();
	}
	else
	{
		char *RFin_bytes = new char[MessageArrayLength];
		for (int n = 0; n < MessageArrayLength; n++)
			RFin_bytes[n] = Serial.read(); // Then: Get them.

		for (size_t i = 0; i < sizeof(RFin_bytes); i++)
		{
			Serial.print(RFin_bytes[i]);
			Serial.print(" ");
		}
		Serial.println();
	}
}
void ReadCommand() {

	while (Serial.available())
	{
		byte x[1];
		Serial.readBytes(x, 1);
		Serial.println((char*)x);
	}
}


// POST DATA
void SendIngridents() {

	// Send data to cellphone?

	Serial.print(567);











	//myIngridiensts[1].Refill("Vodka", 300);
	//if (Serial.available())
	//{
	//	int asd = (int)Serial.read();
	//	if (asd == 40 )
	//	{
	//		Serial.print(myIngridiensts[1].GetName());
	//	}
	//}



}
void SendMessageOnCommand() {
	while (Serial3.available() > 0)
	{

		int msg = Serial3.read();
		Serial.print(Serial3.read());
		if (msg == 'e')
		{

			//NumberSend();
			SendMessage();

		}
	}
	digitalWrite(ledLamp, LOW);
}

void SendMessage() {

	// Tv� f�rsta tecknen eller f�rsta tecknet f�rsvinner

	String myStringMsg = "## Vodka Martini: 10";
	int charCount = 21;
	Serial.println(charCount);

	byte bufferSend[1024];
	digitalWrite(ledLamp, HIGH);

	for (int i = 0; i < charCount; i++) {
		bufferSend[i] = (byte)myStringMsg[i];
		Serial3.write(bufferSend[i]);
		Serial.print((char)bufferSend[i]);
	}
	Serial.println();
	Serial3.flush();
}
void SendNumbers() {
	byte bufferSend[1024];
	for (int i = 0; i < 1024; i++) {
		bufferSend[i] = (byte)i;
		Serial3.print(bufferSend[i]);
		Serial3.print(' ');
		Serial.print((char)bufferSend[i]);
		delay(10);
	}

}