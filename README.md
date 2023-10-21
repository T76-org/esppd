# ESPPD: a ESP32-S3 board with built-in USB-C PD controller

ESPPD is an ESP32-S3 breakout board that incorporates the ability to interface with a USB-C PD-compatible power supply to request a specific voltage. It features:

- ESP32-S3-WROOM module
  - Dual 240 MHz dual-core Tensilica LX7 CPU
  - 2.4 GHz Wi-Fi (802.11n) and Bluetooth 5.0
  - 4MB SPI flash (up to 16MB supported)
  - Up to 8MB of PSRAM
  - 384 KB SRAM
- Hacker-friendly design
  - Compatible with Arduino and PlatformIO
  - Fits a standard breadboard, leaving a row of pins on each side for easy connectivity
  - Makes all ESP32-S3 pins available
  - 3.3V, VBUS, and GND pins on each side
- USB-C PD 2.0 compatible controller
  - Ability to request 5V, 9V, 12V, 15V, or 20V from a compatible supply
  - Ability to request a fixed voltage using hardwired jumpers, or dynamically via firmware
  - Ability to detect whether the requested voltage has actually been supplied
- Separate USB-C connectors for power and data
  - Direct programming via USB
  - USB 2.0 data connection
  - Support for USB host and client configuration
- Power LED
- Software-controllable LED

## Hardware

The ESPPD incorporates a [CH224K](https://www.wch-ic.com/downloads/file/302.html) USB-PD controller that handles the negotiation with a PD-compatible power supply to request a specific voltage. The CH224K is configured to request 5V by default, but can be configured to request 5V, 9V, 12V, 15V, or 20V using either hardwired jumpers or dynamically via firmware. The CH224K also monitors the voltage supplied by the power supply and can report whether the requested voltage has actually been supplied, thus allowing your code to only operate under the correct conditions.

## ESP32-S3 compatibility

The board is compatible with the [ESP32-S3-WROOM-1](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf) module from Espressif. The module features a dual-core 240 MHz Tensilica LX7 CPU, 4MB of SPI flash, up to 8MB of PSRAM, and 384 KB of SRAM. The module also features 2.4 GHz Wi-Fi (802.11n) and Bluetooth 5.0.

Espressif manufactures several different versions of the module, with different amounts of flash and PSRAM. The ESPPD is compatible with all of them, but the amount of flash and PSRAM available to your code will depend on the specific module you use.

> **Note:** The pre-assembled version of the ESPPD sold on our Tindie store comes with an ESP32-S3-WROOM-1-N4 module, which features 4MB of flash RAM.

## Pinout

## Power and data

The ESPPD features two USB-C controllers; one is used to provide power, and the other to communicate with the ESP-32. In the current revision, there is no provision for powering the board via the USB-C data connection, so the power connection must be used. The two connectors are identified by markings on the bottom of the board.

## Setting the PD voltage using jumpers

There bottom of the board features a set of four jumpers that can be used to determine how the board interfaces with the PD controller. The first three jumpers, CFG1 through 3, can be used to either hardwire the PD controller to request a specific voltage, or to allow the ESP32 to dynamically request a voltage via firmware. By default, the jumpers are all set so that CFG1 is high, and CFG2 and 3 are low. This corresponds to the PD controller being hardwired to request 5V. If you with to hardware the PD controller to request a different voltage, you can selective short the jumpers as follows:

| CFG1             | CFG2             | CFG3             | Requested voltage|
| --- | --- | --- | --- |
| High             | Low              | Low              | 5V               |
| Low              | High             | Low              | 9V               |
| High             | High             | Low              | 12V              |
| Low              | Low              | High             | 15V              |
| High             | Low              | High             | 20V              |

Alternatively, you can connect the three configuration lines to three pins of the ESP32, and then set them high or low in your code to dynamically request a voltage as explained in the _Software_ section below.

The fourth jumper is connected to the “power good” pin of the CH224K; this open-collector signal is pulled low when the voltage provided by the power supply is equal to the requested voltage. By default, this jumper is not connected to anything, but, if you short the jumper, it will be available to the ESP32 as GPIO 37.

> **Note:** The PD voltage is available on the board at the `VBUS` pins. Please be careful when connecting anything to these pins, as they are directly connected to the power supply and can supply up to 20V!

## Software

By and large, the ESPPD behaves like any other ESP32 board. You can program it using the Arduino IDE or PlatformIO, and you can use ESP-IDF directly if you wish.

The board can be programmed directly through the USB-C data connection. The USB-C power connection is not used for programming, but it must be used to power the board, even when it is connected to a computer.

When you connect the board to your computer, it will appear as a USB serial device. On Linux and MacOS, it will appear as `/dev/ttyUSB0` or `/dev/tty.usbmodemNNNN`, where `NNNN` is a number that depends on your computer. On Windows, it will appear as a COM port. You can use the Arduino IDE or PlatformIO to program the board using this serial connection.

### Platformio

> **Note:** You can find a complete PlatformIO project for the ESPPD in the `/software/platformio/example` directory of this repository.

In order to program the ESPPD using PlatformIO, you must first create a definition file for the board; this file provides PlatformIO information on things like the amount of flash RAM available, the upload speed, etc. You can find a definition file for the preassembled version of the ESPPD that is available on our Tindie store in the `/software/platformio/boards` directory of this repository. Copy this file to the `boards` directory of your PlatformIO project, and reference it in the `board` property of your platformio.ini file. You can then use the PlatformIO CLI to build and upload your code to the board.

#### Communications

The board definition turns on Arduino's USB CDC support. This means that you should be able to use the `Serial` object to communicate with the board. For example, the following code will print "Hello, world!" to the serial port:

```cpp
void setup() {
  Serial.begin(115200);
  Serial.println("Hello, world!");
}
```

#### Interfacing with the PD controller

If you have shorted the CFG1…3 jumpers so that they are connected to the ESP32, you can use the CH224K library to set the PD voltage dynamically. The library can be found in the `/software/Platformio/lib/CH224K` directory of this repository. You can copy this directory to the `lib` directory of your PlatformIO project, and then use the library in your code as follows:

```cpp
#include <CH224K.h>

CH224K pd;

void setup() {
  pd.begin();         // Uses default pin numbers (GPIO 36, 35, 45 for the CFG pins, and GPIO 37 for the power good pin)
  pd.setVoltageSetPoint(V12);

  // Give the power supply time to adjust to the new voltage
  delay(300);

  // Wait for the power good signal to go high
  while (!pd.powerGood()) {
    delay(100);
  }
}
```

> **Note:** If you are not using the power good pin, you can pass 0 as the last argument to `pd.begin()`.

