# Tiny Coin Ticker


## Hardware Setup

Using an ESP32 module [Heltec WiFi Kit 32](https://github.com/HelTecAutomation/Heltec_ESP32)

Install the [drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) to recognize the serial port connection to the board.

After installing and connecting the board the serial port should be listed:

```
> ls /dev/tty.*

...
/dev/tty.SLAB_USBtoUART
```

## Software Setup

[Platformio](https://docs.platformio.org/en/latest/core/quickstart.html) is the main development platform.

Create a new conda environment:

```
> conda create -n arduino python=3.7
> conda activate arduino
```

Install Platformio:

```
> conda install -c conda-forge platformio
```

Find the ESP32 board:

```
> platformio boards | egrep -i heltec
```

Initialize the directory structure for our board:

```
> pio project init --board heltec_wifi_kit_32
```
