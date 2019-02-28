/*
UV index explanation:	http://www2.epa.gov/sunwise/uv-index-scale
UV index explanation:	http://www.epa.gov/sunwise/doc/what_is_uvindex.html
RGB colours:			https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/
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

enum  colours : int
{
	green = 0,
	yellow = 1,
	orange = 2,
	red = 3,
	purple = 4,
	none = 5
};

colours color;


// Global 
float Vsig = -1;
int	Vibrator = -1;
int UV_Analog = ADC1D;
int PWM_Pin = PCINT0;
int redPin = PCINT5;
int greenPin = PCINT3;
int bluePin = PCINT4;
int time = 0;

// Fuction Prototype
void setColor(int, int, int);
void Colour(void); // UV Index Scale Universal
void Vibration(int); //void Vibration(int); // Motor Vibration

void setup()
{
	pinMode(UV_Analog, INPUT);
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
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
		color = none;
	}
	if (Vsig > 50 && Vsig < 227) // UV Index 1 | Exposure level - LOW  green
	{	
		color = green;
	}
	if (Vsig > 227 && Vsig < 318) { // UV Index: 2  Exposure level - LOW    green
		color = green;
	}
	if (Vsig > 318 && Vsig < 408) {// UV Index: 3  Exposure level - MODERATE  yellow
		color = yellow;
	}
	if (Vsig > 408 && Vsig < 503) {  //UV Index: 4   Exposure level - MODERATE  yellow
		color = yellow;
	}
	if (Vsig > 503 && Vsig < 606) {	// UV Index: 5   Exposure level - MODERATE    yellow
		color = yellow;
	}
	if (Vsig > 606 && Vsig < 696) { // UV Index: 6 Exposure level - HIGH  orange
		color = orange;
	}
	if (Vsig > 696 && Vsig < 795) { // UV Index: 7    Exposure level - HIGH   orange
		color = orange;
	}
	if (Vsig > 795 && Vsig < 881) {	//  UV Index: 8    Exposure level - VERY HIGH   red
		color = orange;
	}
	if (Vsig > 881 && Vsig < 976) {	//	UV Index: 9    Exposure level - VERY HIGH   red
		color = red;
	}
	if (Vsig > 976 && Vsig < 1079) {	//	UV Index: 10    Exposure level - VERY HIGH   red
		color = red;
		Vibration(Vibrator);
	}
	if (Vsig > 1079 && Vsig < 1170) {	//	UV Index: 11	   Exposure level - EXTREME   purple
		color = purple;;
	}
	if (Vsig > 1170) {	//	UV Index: 11+    Exposure level - EXTREME   purple
		color = purple;	
	}
	Vibration(Vibrator);
}



void setColor(int redValue, int greenValue, int blueValue) {
	analogWrite(redPin, redValue);
	analogWrite(greenPin, greenValue);
	analogWrite(bluePin, blueValue);
}

void Colour(void)
{
	switch (color)
	{
	case green:		setColor(0, 255, 0); // Green Color
		break;
	case yellow:	setColor(255, 255, 0); // Red Yellow
		break;
	case orange:	setColor(255, 170, 0); // Red Orange
		break;
	case red:		setColor(255, 0, 0); // Red Color
		break;
	case purple:	setColor(170, 0, 255); // Purple Color
		break;
	default:
		break;
	}
}

void Vibration(	int _pwm)
{
	digitalWrite(PWM_Pin, _pwm);
	Colour();
	delay(time);
}