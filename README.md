<!--
SPDX-FileCopyrightText: 2026 Dane Powell

SPDX-License-Identifier: GPL-3.0-or-later
-->

# ESPHome E-Paper Thermostat

This is an ESPHome touch e-paper thermostat based on the following hardare:

- [XIAO ESP32C6](https://wiki.seeedstudio.com/xiao_esp32c6_getting_started/)
- [Waveshare 2.9in E-Paper Touch HAT](https://www.waveshare.com/2.9inch-Touch-e-Paper-HAT.htm)
- [Pololu U1V11F5 5V regulator](https://www.pololu.com/product/2562)
- 240 mAh 1S LiPo battery

Depends on:

- https://github.com/danepowell/kicad-pololu/

Still in progress:

- Improve battery life (currently only ~5 hours)
- Add a temperature sensor (currently this is more of a remote control than a thermostat, strictly speaking)

The challenge with battery life is the touch sensor and wifi. While the E-Paper display and ESP32 can theoretically go into a deep sleep and consume only a few microamps, this presents two problems:

- We won't receive updates from Home Assistant during this time. One of my biggest grievances with my current IR-based heat pump remote control is that it gets out of sync with changes in Home Assistant, so this is non-negotiable. But maybe we can at least use light sleep and a regular (~15 min) wakeup timer as a compromise.
- The touch display can't be put into any kind of sleep mode without disabling touch updates completely, and it draws quite a bit of power even when idle.

Supposedly the icnt86 touch controller has a low power scan (gesture) wakeup mode that draws only 1-3 mA, which is still more than desired but an order of magnitude less than normal. It could then pulse on INT to wake the ESP32.

Or we could put the icnt86 into deep sleep and poll every ~300 ms. Not actually sure if this would work.

If we ever get to this point, check that our SCL and SDA lines are explicitly put into INPUT_PULLUP on sleep to avoid leakage current.
