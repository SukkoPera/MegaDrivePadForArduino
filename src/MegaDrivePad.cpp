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
 * See the following links for some references on the N64 controller protocol:
 * - http://www.msarnoff.org/gen2usb/
 * - http://www.cs.cmu.edu/~chuck/infopg/segasix.txt
 */


#include "MegaDrivePad.h"

bool MegaDrivePad::begin () {
  return begin (DEFAULT_UP_PIN, DEFAULT_DOWN_PIN, DEFAULT_LEFT_PIN,
                DEFAULT_RIGHT_PIN, DEFAULT_A_B_PIN, DEFAULT_START_C_PIN,
                DEFAULT_SELECT_PIN);
}

bool MegaDrivePad::begin (byte upPin, byte downPin, byte leftPin, byte rightPin,
                          byte abPin, byte startcPin, byte selectPin) {
  pinMapping.up = upPin;
  pinMapping.down = downPin;
  pinMapping.left = leftPin;
  pinMapping.right = rightPin;
  pinMapping.ab = abPin;
  pinMapping.startc = startcPin;
  pinMapping.select = selectPin;

  pinMode (pinMapping.up, INPUT);
  pinMode (pinMapping.down, INPUT);
  pinMode (pinMapping.left, INPUT);
  pinMode (pinMapping.right, INPUT);
  pinMode (pinMapping.ab, INPUT);
  pinMode (pinMapping.startc, INPUT);

  // The select line is normally high
  pinMode (pinMapping.select, OUTPUT);
  digitalWrite (pinMapping.select, HIGH);

  buttons = 0;

  // This cant't really fail
  return true;
}

void MegaDrivePad::read () {
  byte pad_status = 0;

  // Read UP and DOWN, which are always ready
  byte up = digitalRead (pinMapping.up);
  byte down = digitalRead (pinMapping.down);
  pad_status |= (down << BB_DOWN | (up << BB_UP));

  // Read A and START, with SELECT low
  digitalWrite (pinMapping.select, LOW);
  byte a = digitalRead (pinMapping.ab);
  byte start = digitalRead (pinMapping.startc);
  pad_status |= ((start << BB_START) | (a << BB_A));

  // Read LEFT, RIGHT, B and C with SELECT high
  digitalWrite (pinMapping.select, HIGH);
  byte left = digitalRead (pinMapping.left);
  byte right = digitalRead (pinMapping.right);
  byte b = digitalRead (pinMapping.ab);
  byte c = digitalRead (pinMapping.startc);
  pad_status |= ((c << BB_C) | (b << BB_B)
              | (right << BB_RIGHT) | (left << BB_LEFT));

  // We report buttons as 1 when pressed, while controller does the opposite
  buttons = ~pad_status;
}
