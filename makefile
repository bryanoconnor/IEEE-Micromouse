#Example Makefile

F_CPU = 20000000
MCU = atmega328p
CCOPTS= -g -Wall -Os -std=gnu99

default: test

all: program

push_btn.o: push_btn.c push_btn.h
	avr-gcc -c $(CCOPTS) -mmcu=$(MCU) -DF_CPU=$(F_CPU) push_btn.c -o push_btn.o

led.o: led.c led.h
	avr-gcc -c $(CCOPTS) -mmcu=$(MCU) -DF_CPU=$(F_CPU) led.c -o led.o

motor.o: motor.c motor.h
	avr-gcc -c $(CCOPTS) -mmcu=$(MCU) -DF_CPU=$(F_CPU) motor.c -o motor.o

OrangutanTime.o: OrangutanTime.cpp OrangutanTime.h
	avr-gcc -c -g -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) OrangutanTime.cpp -o OrangutanTime.o
 
OrangutanLCD.o: OrangutanLCD.cpp OrangutanLCD.h
	avr-gcc -c -g -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) OrangutanLCD.cpp -o OrangutanLCD.o

OrangutanAnalog.o: OrangutanAnalog.cpp OrangutanAnalog.h
	avr-gcc -c -g -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) OrangutanAnalog.cpp -o OrangutanAnalog.o

IRSensor.o: IRSensor.c IRSensor.h 
	avr-gcc -c $(CCOPTS) -mmcu=$(MCU) -DF_CPU=$(F_CPU) IRSensor.c -o IRSensor.o

test: test.c push_btn.o led.o motor.o OrangutanTime.o OrangutanLCD.o OrangutanAnalog.o IRSensor.o
	avr-gcc  $(CCOPTS) -mmcu=$(MCU) -DF_CPU=$(F_CPU) -o test test.c push_btn.o led.o motor.o OrangutanTime.o OrangutanLCD.o OrangutanAnalog.o IRSensor.o

test.hex: test
	avr-strip test
	avr-objcopy -R .eeprom -O ihex test test.hex

program: test.hex
	avrdude -p m328p -c avrisp2 -P /dev/tty.usbmodem00144321 -U flash:w:test.hex

clean:
	rm test test.hex push_btn.o led.o motor.o OrangutanLCD.o OrangutanTime.o OrangutanAnalog.o IRSensor.o
