# Arduino LCD project

<img align="left" src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
<img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white" />

A fun project to create the smallest possible code to fully take advantage of the HD44780U LCD.
I used Arduino Mega with the ATmega2560 chip.

Inspired by Ben Eater's video: [Connecting an LCD to our computer — 6502 part 4](https://youtu.be/FY3zTUaykVo)


## Datasheet
[https://www.sparkfun.com/datasheets/LCD/HD44780.pdf](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)


## Pinout
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


## Compiling and uploading
1. `avr-g++ -O 3 -D F_CPU=16000000UL -m mcu=atmega2560 -c lcd.cpp -o lcd.o`
2. `avr-g++ -m mcu=atmega2560 -o lcd.elf lcd.o`
3. `avr-objcopy -O ihex -R .eeprom lcd.elf lcd.hex`
4. `avrdude -C /etc/avrdude.conf -D -p atmega2560 -c wiring -P COMx -b 115200 -U flash:w:lcd.hex:i`
