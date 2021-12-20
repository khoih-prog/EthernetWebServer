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

//https://www.u-blox.com/sites/default/files/NINA-B1_DataSheet_UBX-15019243.pdf
//https://www.u-blox.com/sites/default/files/EVK-NINA-B1_UserGuide_%28UBX-15028120%29_C1-Public.pdf

#ifndef _VARIANT_NINA_B112_UBLOX_
#define _VARIANT_NINA_B112_UBLOX_

#define NRF_CLOCK_LFCLKSRC {.source = NRF_CLOCK_LF_SRC_XTAL, \
 .rc_ctiv = 0, \
.rc_temp_ctiv = 0, \
.xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}

/** Master clock frequency */
#define VARIANT_MCK       (64000000ul)

#define USE_LFXO      // Board uses 32khz crystal for LF
// define USE_LFRC    // Board uses RC for LF

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

// Number of pins defined in PinDescription array
#define PINS_COUNT           (32u)
#define NUM_DIGITAL_PINS     (32u)
#define NUM_ANALOG_INPUTS    (6u)
#define NUM_ANALOG_OUTPUTS   (0u)

// LEDs
#define PIN_LED              LED1
#define LED_BUILTIN          PIN_LED

//LEDs onboard
#define LED1 (0)  // Red
#define LED2 (24) // Green/SW1
#define LED3 (4) // Blue

#define LED_STATE_ON         1         // State when LED is litted

//Switch
#define SW1 (24)
#define SW2 (19)

// NFC
#define PIN_NFC_1	(6)  // P0.9
#define PIN_NFC_2	(7)  // P0.10

/*
 * Analog pins
 */
#define PIN_A0               (16) // P0.03
#define PIN_A1               (17) // P0.02
#define PIN_A2               (18) // P0.04
#define PIN_A3               (19) // P0.30
#define PIN_A4               (20) // P0.29
#define PIN_A5               (21) // P0.28

static const uint8_t A0  = PIN_A0 ;
static const uint8_t A1  = PIN_A1 ;
static const uint8_t A2  = PIN_A2 ;
static const uint8_t A3  = PIN_A3 ;
static const uint8_t A4  = PIN_A4 ;
static const uint8_t A5  = PIN_A5 ;

#define ADC_RESOLUTION    14

#define PIN_D0               (0) // P0.05
#define PIN_D1               (1) // P0.06
#define PIN_D2               (2) // P0.07
#define PIN_D3               (4) // P0.31
#define PIN_D4               (5) // P0.18
#define PIN_D6               (6) // P0.09
#define PIN_D7               (7) // P0.10
#define PIN_D9               (9) // P0.08
#define PIN_D10              (11) // P0.11
#define PIN_D11              (13) // P0.13
#define PIN_D12              (12) // P0.12
#define PIN_D13              (14) // P0.14
#define PIN_D14              (2) // P0.02
#define PIN_D15              (3) // P0.03

static const uint8_t D0   = PIN_D0 ;
static const uint8_t D1   = PIN_D1 ;
static const uint8_t D2   = PIN_D2 ;
static const uint8_t D3   = PIN_D3 ;
static const uint8_t D4   = PIN_D4 ;
static const uint8_t D6   = PIN_D6 ;
static const uint8_t D7   = PIN_D7 ;
static const uint8_t D9   = PIN_D9 ;
static const uint8_t D10  = PIN_D10 ;
static const uint8_t D11  = PIN_D11 ;
static const uint8_t D12  = PIN_D12 ;
static const uint8_t D13  = PIN_D13 ;
static const uint8_t D14  = PIN_D14 ;
static const uint8_t D15  = PIN_D15 ;

// Other pins
//static const uint8_t AREF = PIN_AREF;

//#define PIN_AREF           (24)
//#define PIN_VBAT           PIN_A7

/*
 * Serial interfaces
 */
#define PIN_SERIAL_RX       (0) // P0.05
#define PIN_SERIAL_TX       (1) // P0.06
#define PIN_SERIAL_CTS      (2) // P0.07
#define PIN_SERIAL_RTS      (3) // P0.31
#define PIN_SERIAL_DTR      (28) // P0.28
#define PIN_SERIAL_DSR      (29) // P0.29

/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MISO         (12) // P0.12
#define PIN_SPI_MOSI         (11) // P0.13
#define PIN_SPI_SCK          (13) // P0.14

static const uint8_t SS   = 10 ;  // P0.11
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SCK  = PIN_SPI_SCK ;

/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (14) // P0.02
#define PIN_WIRE_SCL         (15) // P0.03

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;


#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/


#endif    //_VARIANT_NINA_B112_UBLOX_
