cmd_/home/debian/fish_fear_us/Module.symvers := sed 's/ko$$/o/' /home/debian/fish_fear_us/modules.order | scripts/mod/modpost -m    -o /home/debian/fish_fear_us/Module.symvers -e -i Module.symvers   -T -
