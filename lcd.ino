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


void ClearDisplay()
{
  PORTA = 0b00000000;
  PORTC = (1 << 0);

  PORTA = 0b00000100;
  PORTA = 0b00000000;

  delayMicroseconds(1500);
}

void ReturnHome()
{
  PORTA = 0b00000000;
  PORTC = (1 << 1);
  
  PORTA = 0b00000100;
  PORTA = 0b00000000;

  delayMicroseconds(1600);
}

void EntryModeSet(CursorMoveDirection cursorMoveDirection, DisplayShift displayShift)
{
  PORTA = 0b00000000;
  PORTC = (1 << 2) | ((uint8_t)cursorMoveDirection << 1) | ((uint8_t)displayShift << 0);
  
  PORTA = 0b00000100;
  PORTA = 0b00000000;

  delayMicroseconds(50);
}

void DisplayOnOffControl(Display display, Cursor cursor, BlinkCursor blinkCursor)
{
  PORTA = 0b00000000;
  PORTC = (1 << 3) | ((uint8_t)display << 2) | ((uint8_t)cursor << 1) | ((uint8_t)blinkCursor << 0);
  
  PORTA = 0b00000100;
  PORTA = 0b00000000;

  delayMicroseconds(50);
}

void CursorOrDisplayShift(ShiftMode shiftMode, ShiftDirection shiftDirection)
{
  PORTA = 0b00000000;
  PORTC = (1 << 4) | ((uint8_t)shiftMode << 3) | ((uint8_t)shiftDirection << 2);
  
  PORTA = 0b00000100;
  PORTA = 0b00000000;

  delayMicroseconds(50);
}

void FunctionSet(DataLength dataLength, Lines lines, CharacterFont characterFont)
{
  PORTA = 0b00000000;
  PORTC = (1 << 5) | ((uint8_t)dataLength << 4) | ((uint8_t)lines << 3) | ((uint8_t)characterFont << 2);

  PORTA = 0b00000100;
  PORTA = 0b00000000;

  delayMicroseconds(50);
}

void WriteData(uint8_t data)
{
  PORTA = 0b00000001;
  PORTC = data;

  PORTA = 0b00000101;
  PORTA = 0b00000000;

  delayMicroseconds(50);
}


void setup()
{
  DDRA = 0b00000111;
  DDRC = 0b11111111;
  delayMicroseconds(1000);

  ClearDisplay();
  FunctionSet(DataLength::EightBits, Lines::OneLine, CharacterFont::FiveEight_Dots);
  DisplayOnOffControl(Display::On, Cursor::Off, BlinkCursor::Off);
  EntryModeSet(CursorMoveDirection::Increment, DisplayShift::Off);

  for (uint8_t data = 'A'; data <= 'Z'; ++data)
  {
    WriteData(data);
  }
}

void loop()
{
}