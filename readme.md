# ULTRAVIOLET SENSE 

_Este sentido te permite tener una percepción de la catidad de rayos UV que contiene la luz del sol._

## REQUISITOS

### Software
* Instalar	Tarjeta:	------------------	by **Spence Konde**		[Más INFO](https://github.com/SpenceKonde/ATTinyCore).
* Instalar	Librería:	------------------	by **Adafruit**			[Más INFO](https://github.com/adafruit/Adafruit_NeoPixel).
* Instalar	Librería:	`<EasyNeoPixels.h>`	by **Evelyn Masso**		[Más INFO](https://github.com/outofambit/easy-neopixels).

### Hardware
* Atiny85		* 1	Unidad.
* GUVA-S12SD	* 1 Unidad.
* WS2812		* 2 Unidades.
* Led RGB		* 1 Unidad.
* Motor			* 3 Unidades.
* Diodo			* 3 Uidades.
* 330 ohm		* 3 Unidades.
* 33 uF			* 1 Unidad.
* Power 5v		* 1 Unidad.

### E/S


|	Attiny85	|		POWER		|		GUVA-S12SD		|		WS2812		|		Motor		|	
|		----	|		----		|		----			|		----		|		----		|
|	PB4			|		GND			|		GND	-			|		GND	-		|		GND	-		|
|	PB8			|		VCC			|		5V	+			|		5V	+		|		5V	+		|
|	PB3	ADC3	|		x			|		OUT				|		x			|		x			|
|	PB1 PCNINT1	|		x			|		x				|		DATA		|		DATA		|





## CÓDIGO
_Comentarios sobre las funciones y sus conexiones._

### Variables Globales

*	`float Vsig = -1;`			_Señal del el sensor UV._
*	`int	Vibrator = -1;`		_Pulso modulado de **0 a 255** que se envía al motor._
*	`int UV_Analog = ADC1D;`	_Lectura en bruto se la señal del sensor UV._
*	`int DATA_Pin = PCINT0;`	_Salida a **WS2812** que comunica al **LED RGB** y a los **3 Motores**._
*	`int time = 1000;`			_Tiempo en milisegundos que se va a matener activos el Led y los motores._ 



## DESPLIEGUE
*PASOS*
* Asegurese de que tienes todo el hardware, conexiones, alimentación, tarjeta y librerías. 
* Monte en una tarjeta de desarrollo las conexiones o ensamble una PCB.
* Ten cuidado lo la alimentación.
* Añade un condensador electrolitico entre el PIN RESET y GND del programador.
* Asegurate de tener configurado el DS3231 ¿Tienes el reloj con la hora ajustada?

_Descomenta estas líneas para ajustarlo con la hora de tu pc._
``` c++
.
..
..

...
..
.
```




## DATASHEET

### ATtiny 25/45/85
![x5 pin mapping](http://drazzy.com/e/img/PinoutT85a.jpg "Arduino Pin Mapping for ATtiny 85/45/25")

