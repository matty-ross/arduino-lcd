#include <avr/io.h>
#include <util/delay.h>


/*
    RS = PORTA0
    RW = PORTA1
    E  = PORTA2
    D0 = PORTC0
    D1 = PORTC1
    D2 = PORTC2
    D3 = PORTC3
    D4 = PORTC4
    D5 = PORTC5
    D6 = PORTC6
    D7 = PORTC7
    
    https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
*/


enum class CursorMoveDirection : uint8_t
{
    Decrement = 0,
    Increment = 1,
};

enum class DisplayShift : uint8_t
{
    Off = 0,
    On = 1,
};

enum class Display : uint8_t
{
    Off = 0,
    On = 1,
};

enum class Cursor : uint8_t
{
    Off = 0,
    On = 1,
};

enum class BlinkCursor : uint8_t
{
    Off = 0,
    On = 1,
};

enum class ShiftMode : uint8_t
{
    CursorMove = 0,
    DisplayShift = 1,
};

enum class ShiftDirection : uint8_t
{
    Left = 0,
    Right = 1,
};

enum class DataLength : uint8_t
{
    FourBits = 0,
    EightBits = 1,
};

enum class Lines : uint8_t
{
    OneLine = 0,
    TwoLines = 1,
};

enum class CharacterFont : uint8_t
{
    FiveEight = 0,
    FiveTen = 1,
};


void ClearDisplay()
{
    PORTA = 0b00000000;
    PORTC = (1 << 0);

    PORTA = 0b00000100;
    PORTA = 0b00000000;

    _delay_us(1500);
}

void ReturnHome()
{
    PORTA = 0b00000000;
    PORTC = (1 << 1);

    PORTA = 0b00000100;
    PORTA = 0b00000000;

    _delay_us(1600);
}

void EntryModeSet(CursorMoveDirection cursorMoveDirection, DisplayShift displayShift)
{
    PORTA = 0b00000000;
    PORTC = (1 << 2) | ((uint8_t)cursorMoveDirection << 1) | ((uint8_t)displayShift << 0);

    PORTA = 0b00000100;
    PORTA = 0b00000000;

    _delay_us(50);
}

void DisplayOnOffControl(Display display, Cursor cursor, BlinkCursor blinkCursor)
{
    PORTA = 0b00000000;
    PORTC = (1 << 3) | ((uint8_t)display << 2) | ((uint8_t)cursor << 1) | ((uint8_t)blinkCursor << 0);

    PORTA = 0b00000100;
    PORTA = 0b00000000;

    _delay_us(50);
}

void CursorOrDisplayShift(ShiftMode shiftMode, ShiftDirection shiftDirection)
{
    PORTA = 0b00000000;
    PORTC = (1 << 4) | ((uint8_t)shiftMode << 3) | ((uint8_t)shiftDirection << 2);

    PORTA = 0b00000100;
    PORTA = 0b00000000;

    _delay_us(50);
}

void FunctionSet(DataLength dataLength, Lines lines, CharacterFont characterFont)
{
    PORTA = 0b00000000;
    PORTC = (1 << 5) | ((uint8_t)dataLength << 4) | ((uint8_t)lines << 3) | ((uint8_t)characterFont << 2);

    PORTA = 0b00000100;
    PORTA = 0b00000000;

    _delay_us(50);
}

void SetDDRAMAddress(uint8_t address)
{
    PORTA = 0b00000000;
    PORTC = (1 << 7) | (address & 0b01111111);

    PORTA = 0b00000100;
    PORTA = 0b00000000;
    
    _delay_us(50);
}

void WriteData(uint8_t data)
{
    PORTA = 0b00000001;
    PORTC = data;

    PORTA = 0b00000101;
    PORTA = 0b00000000;

    _delay_us(50);
}


int main()
{
    DDRA = 0b00000111;
    DDRC = 0b11111111;

    _delay_ms(10);

    FunctionSet(DataLength::EightBits, Lines::TwoLines, CharacterFont::FiveEight);
    DisplayOnOffControl(Display::On, Cursor::Off, BlinkCursor::Off);
    
    while (true)
    {
        constexpr int speed = 300;
        
        ClearDisplay();
        EntryModeSet(CursorMoveDirection::Increment, DisplayShift::Off);
        
        static constexpr char helloWorldMessage[] = "Hello, world!";
        for (int i = 0; i < sizeof(helloWorldMessage) - 1; ++i)
        {
            WriteData(helloWorldMessage[i]);
            _delay_ms(speed);
        }
        
        for (int n = 0; n < 20; ++n)
        {
            CursorOrDisplayShift(ShiftMode::DisplayShift, ShiftDirection::Left);
            _delay_ms(speed);
        }

        SetDDRAMAddress(39);
        EntryModeSet(CursorMoveDirection::Decrement, DisplayShift::Off);

        static constexpr char goodbyeWorldMessage[] = "Goodbye, world!";
        for (int i = sizeof(goodbyeWorldMessage) - 2; i >= 0; --i)
        {
            WriteData(goodbyeWorldMessage[i]);
            _delay_ms(speed);
        }

        _delay_ms(1000);
    }
}