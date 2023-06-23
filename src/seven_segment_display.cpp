#include <avr/io.h>
#include <util/delay.h>


/*
      A  
    F   B
      G  
    E   C
      D   DP
    
    A  = PORTC7
    B  = PORTC6
    C  = PORTC5
    D  = PORTC4
    E  = PORTC3
    F  = PORTC2
    G  = PORTC1
    DP = PORTC0

    1st = PORTA0
    2nd = PORTA1
    3rd = PORTA2
    4th = PORTA3
*/


constexpr uint8_t k_Digits[] =
{
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110, // 9
    0b00000001, // .
};


void DisplaDigit(uint8_t digit, uint8_t place, bool decimalPoint)
{
    constexpr int duration = 5;
    
    PORTA = ~(1 << (place - 1));
    PORTC = k_Digits[digit] | (decimalPoint ? k_Digits[10] : 0b00000000);
    _delay_ms(duration);
    PORTA = ~(0b00000000);
}


int main()
{
    DDRA = 0b00001111;
    DDRC = 0b11111111;
    
    while (true)
    {
        DisplaDigit(1, 1, false);
        DisplaDigit(2, 2, false);
        DisplaDigit(3, 3, true);
        DisplaDigit(4, 4, false);
    }
}