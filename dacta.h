#include <string>

enum mode {ON, OFF, ON_LEFT, ON_RIGHT, LEFT, RIGHT, SWITCH};

class Dacta {

	private:
		int port;
		unsigned int inputs[8];
		unsigned int modeMasks[4];

	public:
		Dacta() {
			port = -1;
			modeMasks[0] = 40;
			modeMasks[1] = 48;
			modeMasks[2] = 16;
			modeMasks[3] = 17;
			modeMasks[4] = 64;
			modeMasks[5] = 72;
			modeMasks[6] = 32;
		}

		bool setPort(int port) {
			if (port < 0)
				return false;
			this->port = port;
			return true;
		}

		bool init() {
			write(port, "q\0", 2);
			write(port, "###Do you byte, when I knock?$$$", 32);
			char buff[32];
			read(port, buff, 32);
		}

		unsigned int getInput(int id) {
			return inputs[id - 1];
		}

		void setOutput(int id, mode mode) {
			unsigned int val = modeMasks[mode] & (7||id);
			write(port, val, 1);
		}
};
