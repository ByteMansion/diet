# Define required Macros here

MAKE = make
MAKECLEAN = make clean
EXPLORER = ./explorer/src/ 

subsystem:
	cd ${EXPLORER} && ${MAKE}

clean:
	-rm -f solution
	cd ${EXPLORER} && ${MAKECLEAN} 

