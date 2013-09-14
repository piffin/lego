

int main(int argc, char* argv[]) {

	switch(argc) {
		case 2:
			serial sp(argv[1]);
			lego(sp);
		break;		
		case 3:
			serial sp(argv[1]);
			
		break;
	}

	printf("USAGE: lego port [program]");
	return 1;
}
