cmd_/home/debian/fish_fear_us/modules.order := {   echo /home/debian/fish_fear_us/gpiod_driver.ko; :; } | awk '!x[$$0]++' - > /home/debian/fish_fear_us/modules.order
