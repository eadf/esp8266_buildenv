# esp8266_buildenv
Build environment for Raspberry Pi and Beaglebone Black

This is (or will be) the build environment i use to compile, flash and test esp8266 applications on the Pi/BB platforms.

I don't expect this to be useful for anybody but myself, but maybe you will find it useful.

* First install the toolchain as described [here.](http://www.esp8266.com/wiki/doku.php?id=toolchain)
You can place the git repository anywhere you like. But /opt/local seemed like a good place to me.
This will take several hours to compile.

* Copy or softlink the content of pi_bin or bb_bin to your ~/bin folder
* adjust the content of ~/bin/esp_test.sh so that the variables point to the right places (sdk and tty port).
* Connect the GPIO pins of your Raspberry Pi or Beaglebone Black
* cd into the root directory of the project you want to build
* call ~/bin/esp_test.sh and see the project compile & flash. A screen console will be opened as well


###Why use an underpowered computer as a build platform?
* When you are a bit rusty on the electronics, like I am, it feels much safer to only risk a now obsolete Raspberry Pi instead of a $1000 PC. Specially when youre dabbling with [mains power](https://github.com/eadf/esp8266_bitseq).
* Pi and BB already has the correct 3V3 voltage, no need for any level shifters and crud.
* The actual development can be done on a 'real' computer, with a full fledged IDE. It's just the flashing part i delegate to the Pi/BB.
* The Pi and BB has easy access, programmable GPIOs that i use to control relays. These relays temporarily disconnects any hardware from the esp while i flash it. So i don't have to manually disconnect any cables each time i want to flash the esp. 
