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
// Thanks to great work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip). 
// See [u-blox nina b](https://github.com/khoih-prog/WiFiNINA_Generic/issues/1)

#include "variant.h"
#include "wiring_constants.h"
#include "wiring_digital.h"
#include "nrf.h"

const uint32_t g_ADigitalPinMap[] =
{
   // D0 .. D13
  29,  // D0  is P0.29 (UART TX)
  45,  // D1  is P1.13 (UART RX 
  44,  // D2  is P1.12 (NFC2)
  31,  // D3  is P0.31 (LED1)
  13,  // D4  is P0.13 (LED2)
  11,  // D5  is P0.11
  9,   // D6  is P0.09
  10,  // D7  is P0.10 (Button)
  41,  // D8  is P1.09 
  12,  // D9  is P0.12
  14,  // D10 is P0.14
  15,  // D11 is P0.15
  32,  // D12 is P1.00
  7,  // D13 is P0.07

  // D14 .. D21 (aka A0 .. A5)
  4,  // D14 is P0.04 (A0)
  30,  // D15 is P0.30 (A1)
  5,  // D16 is P0.05 (A2)
  2,  // D17 is P0.02 (A3)
  28,  // D18 is P0.28 (A4)
  3,  // D19 is P0.03 (A5)

  // D20 .. D21 (aka I2C pins)
  16,  // D20 is P0.16 (SDA)
  24,  // D21 is P0.24 (SCL)
   
  // QSPI pins (not exposed via any header / test point)
  19,  // D22 is P0.19 (QSPI CLK)
  17,  // D23 is P0.17 (QSPI CS)
  20,  // D24 is P0.20 (QSPI Data 0)
  21,  // D25 is P0.21 (QSPI Data 1)
  22,  // D26 is P0.22 (QSPI Data 2)
  26,  // D27 is P0.23 (QSPI Data 3)
  
  40,  // D28 is P1.08 - IO34
  41,  // D29 is P1.01 - IO35
  44,  // D30 is P1.02 - IO36
  45,  // D31 is P1.03 - IO37
  42, // D32 is P1.10 - IO38
  43, // D33 is P1.11 - IO39
  47, // D34 is P1.15 - IO40
  46, // D35 is P1.14 - IO41 
  26, // D36 is P0.26 - IO42
  6,  // D37 is P0.6  - IO43
  27, // D38 is P0.27 - IO44  
};

void initVariant()
{
  // LED1 & LED2
  pinMode(PIN_LED1, OUTPUT);
  ledOff(PIN_LED1);

  pinMode(PIN_LED2, OUTPUT);
  ledOff(PIN_LED2);
}
