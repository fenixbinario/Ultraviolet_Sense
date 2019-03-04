/*
INFO:
UV index explanation:	http://www2.epa.gov/sunwise/uv-index-scale
UV index explanation:	http://www.epa.gov/sunwise/doc/what_is_uvindex.html
RGB colours:			https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/

AUTOR:
Name:		Ultraviolet_Sense.ino
Created:	27/02/2019 16:04:00
Author:	@fenixbinario | www.fenixbinario.com
 
SOFTWARE:
* Instalar	Tarjeta:	------------------	by **Spence Konde**		https://github.com/SpenceKonde/ATTinyCore.
* Instalar	Librería:	------------------	by **Adafruit**			https://github.com/adafruit/Adafruit_NeoPixel.
* Instalar	Librería:	`<EasyNeoPixels.h>`	by **Evelyn Masso**		https://github.com/outofambit/easy-neopixels.

HARDWARE:
* Atiny85		* 1	Unidad.
* GUVA-S12SD	* 1 Unidad.
* WS2812		* 2 Unidades.
* Led RGB		* 1 Unidad.
* Motor			* 3 Unidades.
* Diodo			* 3 Uidades.
* 330 ohm		* 3 Unidades.
* 33 uF			* 1 Unidad.
* Power 5v		* 1 Unidad.

CONNECTION:
|	Attiny85	|		POWER		|		GUVA-S12SD		|		WS2812		|		Motor		|
|		----	|		----		|		----			|		----		|		----		|
|	PB4			|		GND			|		GND	-			|		GND	-		|		GND	-		|
|	PB8			|		VCC			|		5V	+			|		5V	+		|		5V	+		|
|	PB3	ADC3	|		x			|		OUT				|		x			|		x			|
|	PB1 PCNINT1	|		x			|		x				|		DATA		|DATA->FlyBack Diode|


*/

#include <EasyNeoPixels.h>

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
int DATA_Pin = PCINT0;
int time = 1000;

// Fuction Prototype
void setUV(void);								// setup();
void loopUV(void);								// loop();
void setColor(int, int, int);					// ON Set Color on ws2812
void Colour(bool);								// OFF
void Colour(void);								// UV Index Scale Universal choose Colour
void Vibration(int);							// ON void Vibration(int); // Motor Vibration
void Vibration(bool);							// OFF
void mathUV(void);								// Logic & Math

void setup()
{
	setUV();
}

void loop()
{
	loop();
}

void setUV(void)
{
	// Pixel RGB & Motor Vibration
	setupEasyNeoPixels(DATA_Pin, 2);

	// Pin Analog IN
	pinMode(UV_Analog, INPUT);

}

void loopUV(void)
{
	mathUV();
	Colour();
	Vibration(Vibrator);
	delay(time);
	Colour(LOW);
	Vibration(LOW);
	delay(time/4);
}


void setColor(int redValue, int greenValue, int blueValue)
{
	writeEasyNeoPixel(0, redValue, greenValue, blueValue);
}

void Colour(bool _LOW)
{
	writeEasyNeoPixel(0, _LOW);
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

void Vibration(int _pwm)
{
	writeEasyNeoPixel(1, _pwm, _pwm, _pwm);
}

void Vibration(bool _LOW)
{
	writeEasyNeoPixel(1, _LOW);
}

void mathUV(void)
{
	int sensorValue;
	long  sum = 0;
	for (int i = 0; i < 1024; i++)
	{
		sensorValue = analogRead(UV_Analog);
		sum = sensorValue + sum;
		delay(0);
	}
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
}