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
 * This sketch shows how the library can be used, together with UnoJoy, to turn
 * a MegaDrivePad controller into an USB one that can be used on PCs or on a
 * Raspberry Pi running a MegaDrivePad emulator :).
 *
 * For details on UnoJoy, see https://github.com/AlanChatham/UnoJoy.
 */

#include <MegaDrivePad.h>
#include <UnoJoy.h>

MegaDrivePad pad;

void setup () {
  pinMode (LED_BUILTIN, OUTPUT);

  // Init library
  pad.begin ();

  // Init UnoJoy
  setupUnoJoy ();
}


void loop () {
  pad.read ();

  digitalWrite (LED_BUILTIN, pad.buttons != 0);

  // Convert data for UnoJoy
  dataForController_t controllerData = getBlankDataForController ();

  controllerData.crossOn = (pad.buttons & MegaDrivePad::BTN_A) != 0;
  controllerData.squareOn = (pad.buttons & MegaDrivePad::BTN_B) != 0;
  controllerData.triangleOn = (pad.buttons & MegaDrivePad::BTN_C) != 0;
  controllerData.dpadUpOn = (pad.buttons & MegaDrivePad::BTN_UP) != 0;
  controllerData.dpadDownOn = (pad.buttons & MegaDrivePad::BTN_DOWN) != 0;
  controllerData.dpadLeftOn = (pad.buttons & MegaDrivePad::BTN_LEFT) != 0;
  controllerData.dpadRightOn = (pad.buttons & MegaDrivePad::BTN_RIGHT) != 0;
  controllerData.startOn = (pad.buttons & MegaDrivePad::BTN_START) != 0;

  /* Also emulate the analog sticks. UnoJoy wants a uint8_t value like this:
   * - 0 is fully left or up
   * - 255 is fully right or down
   * - 128 is centered
   */
  if (pad.buttons & MegaDrivePad::BTN_LEFT)
    controllerData.leftStickX = 0;
  else if (pad.buttons & MegaDrivePad::BTN_RIGHT)
    controllerData.leftStickX = 255;
  else
    controllerData.leftStickX = 128;

  if (pad.buttons & MegaDrivePad::BTN_UP)
    controllerData.leftStickY = 0;
  else if (pad.buttons & MegaDrivePad::BTN_DOWN)
    controllerData.leftStickY = 255;
  else
    controllerData.leftStickY = 128;

  // Go!
  setControllerData (controllerData);
}
