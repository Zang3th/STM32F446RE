#!/bin/sh

sudo openocd -c "gdb_port 50000" -c "tcl_port 50001" -c "telnet_port 50002" -s "/home/zanget3u/Dev/STM32F446RE" -f "interface/stlink.cfg" -f "target/stm32f4x.cfg"