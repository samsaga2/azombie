ext debugdevice
set debugoutput stdout
debug set_watchpoint read_io 0x2E

set throttle off
after time 18 "set throttle on"
