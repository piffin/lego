#include "serial.h"
#include "dacta.h"
#include <stdio.h>

int main(int argc, char* argv[]) {

	switch(argc) {
		case 2: {
			Serial sp(argv[1]);
			Dacta lego;
			lego.setPort(sp.getPort());
			while(true) {
				//lego.run();
			}
		}
		break;		
		case 3: {
			Serial sp(argv[1]);
		}
		break;
	}

	printf("USAGE: lego port [program]");
	return 1;
}
