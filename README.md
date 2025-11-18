
# Interfacing SD Card Module with Raspberry Pi Pico

Interfacing an SD card module with the Raspberry Pi Pico using the Arduino framework. Through a simple Serial Monitor menu, users can create, write, read, and delete files on a microSD card, gaining hands-on experience with SPI communication, FAT32 storage, and basic embedded data handling.
## Project Overview

This project breaks down SD card operations into an easy menu system that the user controls in real time. The Raspberry Pi Pico executes file system operations based on selections entered in the Serial Monitor.

Users can:
- Create a new file
- Add custom text
- Read contents back
- Delete the file
- Observe responses instantly

This interactive format makes the learning process clearer and more engaging.
## SD Card Module

The SD card module is a compact, SPI-based storage interface designed to let microcontrollers read and write data to microSD cards. Most modules include:
- A 3.3V regulator
- Basic level shifting circuitry
- A standard microSD socket
It acts as the bridge between the SD card’s memory architecture and the Pico’s SPI bus.

<p align="center">
    <img src="Images%20&%20Videos/components_in_sd_module.png" width="400">
  </a>
</p>

## SD Card Module Pinout

| SD Module Pin | Description                              |
| ------------- | ---------------------------------------- |
| VCC           | Power supply (3.3V recommended for Pico) |
| GND           | Ground                                   |
| MISO / DO     | Data from SD card to Pico                |
| MOSI / DI     | Data from Pico to SD card                |
| SCK           | SPI clock signal                         |
| CS            | Chip Select                              |

<p align="center">
    <img src="Images%20&%20Videos/sd_card_module_pinout.png" width="400">
<p align="center"> SD Card Module Pinout </p>
  </a>
</p>

## Circuit Diagram

The SD module connects to the Pico via SPI0:

| Pico Pin | SD Pin |
| -------- | ------ |
| 3V3      | VCC    |
| GND      | GND    |
| GP19     | MOSI   |
| GP16     | MISO   |
| GP18     | SCK    |
| GP17     | CS     |

<p align="center">
    <img src="Images%20&%20Videos/wiring_diagram.png" width="400">
<p align="center"> Circuit Diagram </p>
  </a>
</p>

## Preparing the SD Card

To ensure compatibility, format the card as:
- Partition Table: MBR
- File System: FAT32

SDHC cards (8–32GB) work best.
SDXC cards (64GB+) must be reformatted to FAT32 using tools like Rufus or GUIFormat.
## Library used

- SD.h <a href="https://github.com/arduino-libraries/SD" target="_blank">(Github Link)</a>
## Troubleshooting

**SD init FAILED**
- Using exFAT instead of FAT32
- Wrong wiring (DI/MOSI or DO/MISO swapped)
- Faulty or incompatible SD module level shifter
- Incorrect CS pin
- Card not fully inserted
- Problematic Class-10 SDXC card

**File can’t be opened**
- Wrong or missing FAT32 partition
- File not created previously
- Card write-protected

**Unreadable / Garbled output**
- Baud rate mismatch (must be 115200)
- Power instability during reads/writes
## License

[MIT](https://choosealicense.com/licenses/mit/)

