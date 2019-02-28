/*
UV index explanation: http://www2.epa.gov/sunwise/uv-index-scale
 UV index explanation: http://www.epa.gov/sunwise/doc/what_is_uvindex.html
 Name:		Ultraviolet_Sense.ino
 Created:	27/02/2019 16:04:00
 Author:	@fenixbinario | www.fenixbinario.com
 Hardware: Attiny85 

Connection:

Arduino           Ultraviolet(UV) sensor
A0(Analog 0)          SIG
+ 5V                    VCC
GND                    GND

Attiny85
PB7 ADC1 pin2 (Analog) SIG
PB4 GND
PB8 VCC
PB0 Pin0 PWM

*/


// Global 
float Vsig = -1;
int	Vibrator = -1;
int UV_Analog = ADC1D;
int PWM_Pin = PCINT0;
int red = PCINT5;
int green = PCINT3;
int blue = PCINT4;
int time = 0;
// Fuction Prototyp3e
void Color(int, int, int); // UV Index Scale Universal

void setup()
{
	pinMode(red, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(blue, OUTPUT);
	pinMode(PWM_Pin, OUTPUT);
}


void loop()
{
	int sensorValue;
	long  sum = 0;
	for (int i = 0; i < 1024; i++)
	{
		sensorValue = analogRead(UV_Analog);
		sum = sensorValue + sum;
		delay(0);
	}
	digitalWrite(PWM_Pin, LOW);
	sum = sum >> 10;
	Vsig = sum * 4980.0 / 1023.0; // Vsig is the value of voltage measured from the SIG pin of the Grove interface
	Vibrator = map(int(Vsig), 0, 1200, 0, 255);

	if (Vsig < 50) 
	{
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 50 && Vsig < 227) // UV Index 1 | Exposure level - LOW  green
	{ 
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 227 && Vsig < 318) { // UV Index: 2  Exposure level - LOW    green
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 318 && Vsig < 408) {// UV Index: 3  Exposure level - MODERATE  yellow
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 408 && Vsig < 503) {  //UV Index: 4   Exposure level - MODERATE  yellow
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 503 && Vsig < 606) {	// UV Index: 5   Exposure level - MODERATE    yellow
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 606 && Vsig < 696) { // UV Index: 6 Exposure level - HIGH  orange
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 696 && Vsig < 795) { // UV Index: 7    Exposure level - HIGH   orange
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 795 && Vsig < 881) {	//  UV Index: 8    Exposure level - VERY HIGH   red
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 881 && Vsig < 976) {	//	UV Index: 9    Exposure level - VERY HIGH   red
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 976 && Vsig < 1079) {	//	UV Index: 10    Exposure level - VERY HIGH   red
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 1079 && Vsig < 1170) {	//	UV Index: 11	   Exposure level - EXTREME   purple
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
	if (Vsig > 1170) {		//	UV Index: 11+    Exposure level - EXTREME   purple
		digitalWrite(PWM_Pin, Vibrator);
		delay(time);
	}
}


void Color(int _red, int _green, int _blue)
{
	analogWrite(red, _red);
	analogWrite(green, _green);
	analogWrite(blue, _blue);
}