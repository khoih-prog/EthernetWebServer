/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.
  Copyright (c) 2016 Sandeep Mistry All right reserved.
  Copyright (c) 2018, Adafruit Industries (adafruit.com)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

#include "wiring_constants.h"
#include "wiring_digital.h"
#include "nrf.h"

//https://www.u-blox.com/sites/default/files/NINA-B1_DataSheet_UBX-15019243.pdf
//https://www.u-blox.com/sites/default/files/EVK-NINA-B1_UserGuide_%28UBX-15028120%29_C1-Public.pdf

const uint32_t g_ADigitalPinMap[] = {
   // D0 .. D13
  5,   // D0  is P0.05 (UART RX)
  6,   // D1  is P0.06 (UART TX) 
  7,   // D2  is P0.07 
  31,  // D3  is P0.31 
  18,  // D4  is P0.18 (LED Blue)
  99,  // D5  (NC)
  9,   // D6  is P0.09 NFC1
  10,  // D7  is P0.10 (Button) NFC2
  99,  // D8  (NC)
  8,   // D9  is P0.08
  11,  // D10 is P0.11 CS
  13,  // D11 is P0.13 MOSI
  12,  // D12 is P0.12 MISO
  14,  // D13 is P0.14 SCK
  //I2C
  2,  // D14 is P0.2 (SDA)
  3,  // D15 is P0.3 (SCL)
  // D16 .. D21 (aka A0 .. A5)
  3,  // D16 is P0.03 (A0)
  2,  // D17 is P0.02 (A1)
  4,  // D18 is P0.04 (A2)
  30, // D19 is P0.30 (A3) SW2
  29, // D20 is P0.29 (A4)
  28, // D21 is P0.28 (A5)
  9,  // P0.09 NFC
  10, // P0.10 NFC
  16, // SW1 (LED Green)
};