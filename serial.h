#include <string>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

class Serial {
	private:
		std::string port;
		int file;


	public:
		Serial(std::string port) {
			this->port = port;
		}

		bool start() {
			file = open(port.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
			if (file < 0)
				return false;
			return setup(file, B9600, 0);
		}

		bool stop() {

		}

		int getPort() {
			return file;
		}

	private:
		int setup (int fd, int speed, int parity) {
			struct termios tty;
			memset (&tty, 0, sizeof tty);
			if (tcgetattr (fd, &tty) != 0)
				return false;

			cfsetospeed (&tty, speed);
			cfsetispeed (&tty, speed);

			tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;			// 8-bit chars
			tty.c_iflag &= ~IGNBRK;						// ignore break signal
			tty.c_lflag = 0;						// no signaling chars, no echo,
			tty.c_oflag = 0;						// no remapping, no delays
			tty.c_cc[VMIN]  = 0;						// read doesn't block
			tty.c_cc[VTIME] = 5;						// 0.5 seconds read timeout

			tty.c_iflag &= ~(IXON | IXOFF | IXANY);				// no xon/xoff ctrl

			tty.c_cflag |= (CLOCAL | CREAD);				// ignore modem controls, enable reading
			tty.c_cflag &= ~(PARENB | PARODD);				// no parity
			tty.c_cflag |= parity;
			tty.c_cflag &= ~CSTOPB;
			tty.c_cflag &= ~CRTSCTS;

			if (tcsetattr (fd, TCSANOW, &tty) != 0)
				return false;
		}
};
