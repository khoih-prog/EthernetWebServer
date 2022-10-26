#pragma once
#include <macros.h>
#include <stdint.h>

#ifndef __PINS_ARDUINO__
#define __PINS_ARDUINO__

#ifdef __cplusplus
	extern "C" unsigned int PINCOUNT_fn();
#endif

// Pin count
// ----
#define PINS_COUNT           (PINCOUNT_fn())
#define NUM_DIGITAL_PINS     (30u)
#define NUM_ANALOG_INPUTS    (4u)
#define NUM_ANALOG_OUTPUTS   (0u)

extern PinName digitalPinToPinName(pin_size_t P);

// LEDs
// ----
#define PIN_LED     (25u)
#define LED_BUILTIN PIN_LED

// Digital pins
// ----
#define PIN_D0 (26u)
#define PIN_D1 (27u)
#define PIN_D2 (28u)
#define PIN_D3 (29u)
#define PIN_D4 (6u)
#define PIN_D5 (7u)
#define PIN_D6 (0u)
#define PIN_D7 (1u)
#define PIN_D8 (2u)
#define PIN_D9 (4u)
#define PIN_D10 (3u)

static const uint8_t D0 = PIN_D0;
static const uint8_t D1 = PIN_D1;
static const uint8_t D2 = PIN_D2;
static const uint8_t D3 = PIN_D3;
static const uint8_t D4 = PIN_D4;
static const uint8_t D5 = PIN_D5;
static const uint8_t D6 = PIN_D6;
static const uint8_t D7 = PIN_D7;
static const uint8_t D8 = PIN_D8;
static const uint8_t D9 = PIN_D9;
static const uint8_t D10 = PIN_D10;


// Analog pins
// -----------
#define PIN_A0 (26u)
#define PIN_A1 (27u)
#define PIN_A2 (28u)
#define PIN_A3 (29u)

static const uint8_t A0  = PIN_A0;
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;

#define ADC_RESOLUTION 12

// Serial
#define PIN_SERIAL_TX (0ul)
#define PIN_SERIAL_RX (1ul)

// SPI
//#define PIN_SPI_MISO  (16u)
//#define PIN_SPI_MOSI  (19u)
//#define PIN_SPI_SCK   (18u)
//#define PIN_SPI_SS    (17u)
// KH fix wrong pin
#define PIN_SPI_MISO  (D9)
#define PIN_SPI_MOSI  (D10)
#define PIN_SPI_SCK   (D8)
#define PIN_SPI_SS    (D7)
//////

static const uint8_t SS   = PIN_SPI_SS;   // SPI Slave SS not used. Set here only for reference.
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

// Wire
#define SDA        (6u)
#define SCL        (7u)

#define SERIAL_HOWMANY    1
#define SERIAL1_TX      (digitalPinToPinName(PIN_SERIAL_TX))
#define SERIAL1_RX      (digitalPinToPinName(PIN_SERIAL_RX))

#define SERIAL_CDC      1
#define HAS_UNIQUE_ISERIAL_DESCRIPTOR
#define BOARD_VENDORID    0x2886
#define BOARD_PRODUCTID   0x8042
#define BOARD_NAME      "RaspberryPi Pico"

uint8_t getUniqueSerialNumber(uint8_t* name);
void _ontouch1200bps_();

#define SPI_HOWMANY   (1)
#define SPI_MISO    (digitalPinToPinName(PIN_SPI_MISO))
#define SPI_MOSI    (digitalPinToPinName(PIN_SPI_MOSI))
#define SPI_SCK     (digitalPinToPinName(PIN_SPI_SCK))

#define WIRE_HOWMANY  (1)
#define I2C_SDA     (digitalPinToPinName(SDA))
#define I2C_SCL     (digitalPinToPinName(SCL))

#define digitalPinToPort(P)   (digitalPinToPinName(P)/32)

#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         SerialUSB
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

#define USB_MAX_POWER (500)

#endif //__PINS_ARDUINO__
