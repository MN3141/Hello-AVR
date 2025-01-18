c:
	rm -rf build
	cmake -S . -B build -G "Unix Makefiles"

b:
	cd build; make -j16

flash:
	cd build; make flash

serial:
	screen /dev/ttyACM0 9600
