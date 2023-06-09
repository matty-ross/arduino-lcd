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
*/

// https://www.sparkfun.com/datasheets/LCD/HD44780.pdf


#define DELAY 100 // ms
#define MESSAGE "Hello, world!"


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
  FiveEight_Dots = 0,
  FiveTen_Dots = 1,
};


inline void ClearDisplay()
{
  PORTC = (1 << 0);

  PORTA = 0b00000000;
  PORTA = 0b00000100;
  PORTA = 0b00000000;
}

inline void ReturnHome()
{
  PORTC = (1 << 1);

  PORTA = 0b00000000;
  PORTA = 0b00000100;
  PORTA = 0b00000000;
}

inline void EntryModeSet(CursorMoveDirection cursorMoveDirection, DisplayShift displayShift)
{
  PORTC = (1 << 2) | ((uint8_t)cursorMoveDirection << 1) | ((uint8_t)displayShift << 0);

  PORTA = 0b00000000;
  PORTA = 0b00000100;
  PORTA = 0b00000000;
}

inline void DisplayOnOffControl(Display display, Cursor cursor, BlinkCursor blinkCursor)
{
  PORTC = (1 << 3) | ((uint8_t)display << 2) | ((uint8_t)cursor << 1) | ((uint8_t)blinkCursor << 0);

  PORTA = 0b00000000;
  PORTA = 0b00000100;
  PORTA = 0b00000000;
}

inline void CursorOrDisplayShift(ShiftMode shiftMode, ShiftDirection shiftDirection)
{
  PORTC = (1 << 4) | ((uint8_t)shiftMode << 3) | ((uint8_t)shiftDirection << 2);

  PORTA = 0b00000000;
  PORTA = 0b00000100;
  PORTA = 0b00000000;
}

inline void FunctionSet(DataLength dataLength, Lines lines, CharacterFont characterFont)
{
  PORTC = (1 << 5) | ((uint8_t)dataLength << 4) | ((uint8_t)lines << 3) | ((uint8_t)characterFont << 2);

  PORTA = 0b00000000;
  PORTA = 0b00000100;
  PORTA = 0b00000000;
}

inline void WriteData(uint8_t data)
{
  PORTC = data;

  PORTA = 0b00000001;
  PORTA = 0b00000101;
  PORTA = 0b00000001;
}


void setup()
{
  DDRA = 0b00000111;
  DDRC = 0b11111111;
  delay(DELAY);

  PORTA = 0b00000000;
  PORTC = 0b00000000;
  delay(DELAY);

  ClearDisplay();
  delay(DELAY);

  FunctionSet(DataLength::EightBits, Lines::OneLine, CharacterFont::FiveEight_Dots);
  delay(DELAY);

  DisplayOnOffControl(Display::On, Cursor::Off, BlinkCursor::Off);
  delay(DELAY);

  EntryModeSet(CursorMoveDirection::Increment, DisplayShift::Off);
  delay(DELAY);

  PORTA = 0b00000000;
  PORTC = 0b00000000;
  delay(DELAY);

  for (int i = 0; i < sizeof(MESSAGE) - 1; ++i)
  {
    WriteData(MESSAGE[i]);
    delay(DELAY);
  }
}

void loop()
{
}