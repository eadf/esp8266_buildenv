# esp8266_buildenv
Build environment for Raspberry Pi and Beaglebone Black

This is (or will be) the build environment i use to compile, flash and test esp8266 applications on the Pi/BB platforms.

I don't expect this to be useful for anybody but myself, but maybe you will find it useful.

### Install
* First install the toolchain as described [here.](http://www.esp8266.com/wiki/doku.php?id=toolchain)
You can place the git repository anywhere you like. But /opt/local seemed like a good place to me.
This will take several hours to compile.
* copy or softlink the content of pi_bin or bb_bin to your ~/bin folder.
* adjust the content of ~/bin/esp_test.sh so that the variables point to the right places (sdk and tty port).
* connect the GPIO pins of your Raspberry Pi or Beaglebone Black.
* cd into the root directory of the project you want to build.
* call ~/bin/esp_test.sh and see the project compile & flash. A screen console will be opened as well.

### Circuit
The intention is to be able disconnect the esp8266 from whatever hardware you are using, and setting it up so that the esp enter flash mode when the scripts reset it. For this purpose i used some old Arduino relays i had in my junk drawer.

#### normal mode
The inactive state of the relays connects whatever gadgets you are using to the GPIO0, GPIO2 and RX pins of the esp8266.

#### bypass mode
The active state of the relays connects GPIO0 and GPIO2 to 3V3 via pullups. Esp8266 RX pin will be connected to the TX pin of the Pi/BB. 


Raspberry Pi Pins| Destination
----------------|-------------
RX (ttyAMA0)    | Esp8266 TX
TX (ttyAMA0)    | relay
GPIO.BCM.7      | relay control * 3
GPIO.BCM.8      | Esp8266 Reset

All other esp pins should be connected as per usual (Vcc, GND, CHIP_EN etc etc)


###Why use an underpowered computer as a build platform?
* When you are a bit rusty on the electronics, like I am, it feels much safer to only risk a now obsolete Raspberry Pi B instead of a $1000 PC. Specially when youre dabbling with [mains power](https://github.com/eadf/esp8266_bitseq).
* Pi and BB already have the correct 3V3 voltage, no need for any level shifters and crud like that.
* The actual development can be done on a 'real' computer, with a full fledged IDE. It's just the flashing part i delegate to the Pi/BB via ssh.
* The Pi and BB have easy access, programmable GPIOs that i use to control relays. These relays temporarily disconnects any hardware from the esp while i flash it. So i don't have to manually disconnect any cables each time i want to flash the esp. Very useful if you are using the RX pin of the esp as a GPIO.
