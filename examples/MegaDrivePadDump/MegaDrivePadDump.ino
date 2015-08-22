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
 *******************************************************************************
 *
 * Sketch that shows basic usage of the library, reading the controller status
 * and continuously reporting its state.
 *
 * When looking straight at the connector on the controller cable, pinout is as
 * follows:
 *
 *                                5 4 3 2 1
 *                              _____________
 *                              \ o o o o o /
 *                               \_o_o_o_o_/
 *
 *                                 9 8 7 6
 *
 * Default pin assignments are as follows:
 * - Pad Pin 1 -> Arduino pin 2
 * - Pad Pin 2 -> Arduino pin 3
 * - Pad Pin 3 -> Arduino pin 4
 * - Pad Pin 4 -> Arduino pin 5
 * - Pad Pin 6 -> Arduino pin 6
 * - Pad Pin 7 -> Arduino pin 8
 * - Pad Pin 9 -> Arduino pin 7
 *
 * (Notice that 7 -> 8 and 9 -> 7!)
 *
 * To power the controller, also connect:
 * - Pad Pin 5 -> +5V
 * - Pad Pin 8 -> GND
 */

#include <MegaDrivePad.h>

MegaDrivePad pad;

void setup () {
  Serial.begin (9600);

  pad.begin ();

  pinMode (LED_BUILTIN, OUTPUT);
}

void loop () {
  pad.read ();

  digitalWrite (LED_BUILTIN, pad.buttons != 0);

  Serial.print ("Pressed: ");
  if (pad.buttons & MegaDrivePad::BTN_UP)
    Serial.print ("Up ");
  if (pad.buttons & MegaDrivePad::BTN_DOWN)
    Serial.print ("Down ");
  if (pad.buttons & MegaDrivePad::BTN_LEFT)
    Serial.print ("Left ");
  if (pad.buttons & MegaDrivePad::BTN_RIGHT)
    Serial.print ("Right ");
  if (pad.buttons & MegaDrivePad::BTN_A)
    Serial.print ("A ");
  if (pad.buttons & MegaDrivePad::BTN_B)
    Serial.print ("B ");
  if (pad.buttons & MegaDrivePad::BTN_C)
    Serial.print ("C ");
  if (pad.buttons & MegaDrivePad::BTN_START)
    Serial.print ("Start ");
  Serial.println ("");

  // Wait a bit
  delay (100);
}
