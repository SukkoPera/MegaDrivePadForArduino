/*******************************************************************************
 * This file is part of MegaDrivePad for Arduino.                              *
 *                                                                             *
 * Copyright (C) 2015 by SukkoPera                                             *
 *                                                                             *
 * MegaDrivePad is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * MegaDrivePad is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with MegaDrivePad. If not, see <http://www.gnu.org/licenses/>.        *
 ******************************************************************************/

#include <Arduino.h>

// Default pin mappings
#define DEFAULT_UP_PIN 2
#define DEFAULT_DOWN_PIN 3
#define DEFAULT_LEFT_PIN 4
#define DEFAULT_RIGHT_PIN 5
#define DEFAULT_A_B_PIN 6
#define DEFAULT_START_C_PIN 7
#define DEFAULT_SELECT_PIN 8

class MegaDrivePad {
private:
  enum ButtonBits {
    BB_UP = 0,
    BB_DOWN,
    BB_LEFT,
    BB_RIGHT,
    BB_B,
    BB_C,
    BB_A,
    BB_START
  };

  struct PinMapping {
    byte up;
    byte down;
    byte left;
    byte right;
    byte ab;
    byte startc;
    byte select;
  };

  PinMapping pinMapping;


public:
  enum PadButton {
    BTN_START = 1 << BB_START,
    BTN_A =     1 << BB_A,
    BTN_C =     1 << BB_C,
    BTN_B =     1 << BB_B,
    BTN_RIGHT = 1 << BB_RIGHT,
    BTN_LEFT =  1 << BB_LEFT,
    BTN_DOWN =  1 << BB_DOWN,
    BTN_UP =    1 << BB_UP
  };

  // Button status register. Use PadButton values to test this. 1 means pressed.
  byte buttons;

  // Initializes the library using the default pin mapping
  bool begin ();

  // Initializes the library using a custom pin mapping
  bool begin (byte upPin, byte downPin, byte leftPin, byte rightPin, byte abPin,
              byte startcPin, byte selectPin);


  // Reads the current state of the joystick.
  void read ();
};
