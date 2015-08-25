#ifndef DEMODULATOR_H
#define DEMODULATOR_H

#include <inttypes.h>

#include "framer.h"

class Demodulator {
	public:
		Demodulator();
		~Demodulator();
		void processBuffer( int16_t *buffer, long numSamples );
	private:
		Framer *framer;
};

#endif
