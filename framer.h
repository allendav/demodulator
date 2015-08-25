#ifndef FRAMER_H
#define FRAMER_H

#include <inttypes.h>

class Framer {
	public:
		Framer();
		void addBit( bool isOne );
	private:
		long shiftCount;
		unsigned char shiftRegister;
		bool foundFlag;
};

#endif