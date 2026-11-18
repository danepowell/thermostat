<!--
SPDX-FileCopyrightText: 2026 Dane Powell

SPDX-License-Identifier: GPL-3.0-or-later
-->

# ESPHome E-Paper Thermostat

This is an ESPHome touch e-paper thermostat based on the following hardware:

- [XIAO ESP32C6](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/)
- [Waveshare 2.9in E-Paper Touch HAT](https://www.waveshare.com/2.9inch-Touch-e-Paper-HAT.htm)
- [Pololu U1V11F5 5V regulator](https://www.pololu.com/product/2562)
- 240 mAh 1S LiPo battery

> [!NOTE]
> This is a work in progress and still in a pre-protoype phase. Use at your own risk.

Depends on:

- https://github.com/danepowell/kicad-pololu/

## Case

Copy my design in OnShape: https://cad.onshape.com/documents/da84725b03bf912abcd9079c/w/40e4bec9f83454897f6fe609/e/7877d9c784235c98f72ce537?renderMode=0&uiState=6af4c48c539eb27832d8ffcd

A 3mf export (suitable for printing in Bambu Studio) is also available in the `case` directory.

## ESPHome

The `esphome` directory contains the software which you can flash to the XIAO ESP32C6.

## KiCad

The `kicad` directory contains the KiCad PCB and schematic which you can use to manufacture your own board.

The assembly should be straightforward and self-explanatory with the exception of the battery terminals on the ESP32. Since these are on the rear of the chip, they must be flush-soldered to the PCB. The best technique I've found is to apply a tiny amount of solder paste to the battery terminals, clamp the ESP32 to the PCB, then apply heat and solder from the back through the corresponding vias.

## Still in progress

- Improve battery life (currently only ~5 hours)
- Add a temperature sensor (currently this is more of a remote control than a thermostat, strictly speaking)

The challenge with battery life is the touch sensor and wifi. While the E-Paper display and ESP32 can theoretically go into a deep sleep and consume only a few microamps, this presents two problems:

- We won't receive updates from Home Assistant during this time. One of my biggest grievances with my current IR-based heat pump remote control is that it gets out of sync with changes in Home Assistant, so this is non-negotiable. But maybe we can at least use light sleep and a regular (~15 min) wakeup timer as a compromise.
- The touch display can't be put into any kind of sleep mode without disabling touch updates completely, and it draws quite a bit of power even when idle.

Supposedly the icnt86 touch controller has a low power scan (gesture) wakeup mode that draws only 1-3 mA, which is still more than desired but an order of magnitude less than normal. It could then pulse on INT to wake the ESP32.

Or we could put the icnt86 into deep sleep and poll every ~300 ms. Not actually sure if this would work.

If we ever get to this point, check that our SCL and SDA lines are explicitly put into INPUT_PULLUP on sleep to avoid leakage current.
