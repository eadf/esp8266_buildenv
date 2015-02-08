# esp8266_buildenv
Build environment for Raspberry pi and Beaglebone Black

This is (or will be) the build environment i use to compile, flash and test esp8266 applications on the Pi/BB platforms.

I don't expect this to be useful for anybody but myself, but maybe you will find it useful.

* First install the toolchain as described [here.](http://www.esp8266.com/wiki/doku.php?id=toolchain)
You can place the git repository anywhere you like. But /opt/local seemed like a good place to me.
This will take several hours.

* Copy or softlink the content of pi_bin or bb_bin to your ~/bin folder
* adjust the content of ~/bin/esp_test.sh so that the variables point to the right places.
* Connect the GPIO pins of your Raspberry Pi or Beaglebone Black
* cd into the root directory of the project you want to build
* call ~/bin/esp_test.sh and see the project compile & flash. A screen console will be opened as well
