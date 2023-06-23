# Arduino Low Level

<img align="left" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
<img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white" />

A fun project to learn low level fundamentals of Arduino.
I used Arduino Mega with the ATmega2560 chip.

Inspired by [Ben Eater's videos](https://www.youtube.com/@BenEater).


## Compiling and uploading
```
avr-g++ -O3 -DF_CPU=16000000UL -mmcu=atmega2560 -c src/{name}.cpp -o out/{name}.o
avr-g++ -mmcu=atmega2560 -o out/{name}.elf out/{name}.o
avr-objcopy -Oihex -R .eeprom out/{name}.elf out/{name}.hex
avrdude -C/etc/avrdude.conf -D -patmega2560 -cwiring -P{port} -b115200 -Uflash:w:out/{name}.hex:i
```


## Programs

### Liquid Crystal Display
#### Datasheet
[https://www.sparkfun.com/datasheets/LCD/HD44780.pdf](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)
#### Pinout
- `RS = PORTA0`
- `RW = PORTA1`
- `E  = PORTA2`
- `D0 = PORTC0`
- `D1 = PORTC1`
- `D2 = PORTC2`
- `D3 = PORTC3`
- `D4 = PORTC4`
- `D5 = PORTC5`
- `D6 = PORTC6`
- `D7 = PORTC7`

### Seven Segment Display
#### Pinout
```
  A  
F   B
  G  
E   C
  D   DP
```
- `A   = PORTC7`
- `B   = PORTC6`
- `C   = PORTC5`
- `D   = PORTC4`
- `E   = PORTC3`
- `F   = PORTC2`
- `G   = PORTC1`
- `DP  = PORTC0`
- `1st = PORTA0`
- `2nd = PORTA1`
- `3rd = PORTA2`
- `4th = PORTA3`
