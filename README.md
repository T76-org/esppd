# ESPPD: a ESP32-S3 board with built-in USB-C PD controller

![ESPPD](https://github.com/T76-org/esppd/wiki/img/esppd_small.png)

ESPPD is an ESP32-S3 breakout board that incorporates the ability to interface with a USB-C PD-compatible power supply to request a specific voltage. It features:

- **Hacker-friendly design**
  - Plug-and-play compatibility with Arduino and PlatformIO
  - Fits a standard breadboard, leaving a row of pins on each side for easy connectivity
  - Most ESP32-S3 pins available at the headers
  - 3.3V, VBUS (USB-PD input voltage), and GND pins on both sides
- **ESP32-S3-WROOM-1 module**
  - Dual 240 MHz dual-core Tensilica LX7 CPU
  - 2.4 GHz Wi-Fi (802.11n) and Bluetooth 5.0
  - 8MB SPI flash
  - 384 KB SRAM
- **USB-C PD 2.0 compatible controller**
  - Ability to request 5V, 9V, 12V, 15V, or 20V from a compatible supply
  - Ability to request a fixed voltage using hardwired jumpers, or dynamically via code
  - Ability to detect whether the requested voltage has actually been supplied (power-good signal)
- **Separate USB-C connectors for power and data**
  - Direct programming via USB; no UART required
  - USB 2.0 data connection
  - Support for USB host and client configuration
  - Serial I/O via USB supported out of the box
- **Indicators**
  - Power LED (red)
  - Software-controllable blue LED

## Hardware

The ESPPD incorporates a [CH224K](https://www.wch-ic.com/downloads/file/302.html) USB-PD controller that handles the negotiation with a PD-compatible power supply to request a specific voltage. The CH224K is configured to request 5V by default, but [can be configured](https://github.com/T76-org/esppd/wiki/Interfacing-with-USB-PD-devices) to request 5V, 9V, 12V, 15V, or 20V using either hardwired jumpers or dynamically via firmware. The CH224K also monitors the voltage supplied by the power supply and can report whether the requested voltage has actually been supplied, thus allowing your code to only operate under the correct conditions.

## ESP32-S3 compatibility

The board is compatible with the [ESP32-S3-WROOM-1](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf) module from Espressif. The module features a dual-core 240 MHz Tensilica LX7 CPU, 4MB of SPI flash, up to 8MB of PSRAM, and 384 KB of SRAM. The module also features 2.4 GHz Wi-Fi (802.11n) and Bluetooth 5.0.

## Pinout

![Pinout](https://github.com/T76-org/esppd/wiki/img/pinout.png)

For additional information on the features associated with each pin, you can consult [Espressif's ESP32-S3 datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf).

## Further reading

For more information on how to build and upload your code to the board, interact with a USB-PD power supply, and troubleshoot any problems, see the [wiki](https://github.com/T76-org/esppd/wiki).
