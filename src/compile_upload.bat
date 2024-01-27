avr-gcc -c -std=gnu99 -Os -Wall --function-sections -fdata-sections -mmcu=atmega328p main.c -o Main.o

avr-gcc -Os -mmcu=atmega328p -ffunction-sections -fdata.sections Main.o -oExecutable.elf

avr-objcopy -O ihex -R .eeprom Executable.elf Executable.ihex

rm Main.o

rm Executable.elf

avrdude -p atmega328p -c arduino -b 115200 -P COM6 -U flash:w:Executable.ihex:i

