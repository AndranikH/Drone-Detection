# Drone Detection

A ground-based, multi-sensor drone detection project built on an ESP32-S3. The goal is to detect drones by combining **RF sensing** (WiFi/BLE, including Remote ID broadcasts) with an **acoustic microphone array** (rotor sound signatures and direction of arrival).



## Status

- [x] Toolchain set up (VS Code + PlatformIO)
- [x] Board verified (ESP32-S3, 16 MB flash, 8 MB PSRAM)
- [x] WiFi scan and RSSI averaging
- [x] External antenna test (large RSSI gain with antenna attached)
- [ ] Range test (RSSI vs. distance)
- [ ] BLE scan
- [ ] WiFi promiscuous mode / packet capture
- [ ] Remote ID parsing
- [ ] 4-mic I2S array + Goertzel detection
- [ ] Direction of arrival (TDOA)
- [ ] Phase 2: Raspberry Pi + computer vision

## Hardware

| Part | Notes |
|---|---|
| Lonely Binary ESP32-S3 N16R8 (Gold Edition, IPEX) | 16 MB flash, 8 MB octal PSRAM, WiFi + BLE 5, external IPEX antenna |
| IPEX cable + antenna | External antenna for WiFi/BLE range |
| 4x SPH0645LM4H I2S MEMS mics (Adafruit) | Planned acoustic array |

## Quick start

1. Install [VS Code](https://code.visualstudio.com/) and the **PlatformIO IDE** extension.
2. Clone this repo and open the folder in VS Code.
3. Plug in the board, then **Build** (checkmark) and **Upload** (arrow) from the blue bar at the bottom.
4. Open the **Serial Monitor** (plug icon) at 115200 baud.

### `platformio.ini`

```ini
[env:esp32-s3]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
monitor_speed = 115200
board_build.arduino.memory_type = qio_opi
board_upload.flash_size = 16MB
build_flags =
  -DARDUINO_USB_CDC_ON_BOOT=1
  -DBOARD_HAS_PSRAM
upload_port = COM4
monitor_port = COM4
```

This is set for the **native USB port**. For the UART port, use `-DARDUINO_USB_CDC_ON_BOOT=0` and its COM port instead.



## Experiments

### Antenna test
Averaged RSSI to a known router (20 readings) with the antenna attached vs. detached, in the same spot. Result: roughly -48 dBm attached vs. -80 dBm detached, about a 32 dB difference, confirming the external antenna is the active path.

(Add range test, channel survey, and BLE results here as they're done.)

## Useful docs

### WiFi
- [Arduino WiFi library reference](https://docs.arduino.cc/libraries/wifi/): the official API reference for the `WiFi` library.
- [ESP32 Useful Wi-Fi Library Functions (Random Nerd Tutorials)](https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/): a practical cheat sheet covering WiFi modes (station, access point, both), scanning networks, connection status, `WiFi.RSSI()`, static IPs, reconnecting, WiFi events, WiFiMulti, and hostnames.

### Board
- [Lonely Binary: ESP32-S3 guide](https://learn.lonelybinary.com/esp32/chips/s3): specs, pin notes, board settings for Arduino, MicroPython, and PlatformIO, and the common S3 gotchas (native USB port, CDC On Boot, octal PSRAM pins, ADC2 and WiFi). Its guide list also covers I2S audio, BLE, ESP-NOW, and dual-core tasks, which map onto the next steps here.

### Tools and further reading
- [PlatformIO docs](https://docs.platformio.org/): `platformio.ini` options and CLI.
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/): the full reference, including WiFi promiscuous mode and I2S.
- [PySDR](https://pysdr.com/): free online textbook on DSP and software-defined radio.
- [OpenDroneID](https://github.com/opendroneid): open-source Remote ID parsing.

