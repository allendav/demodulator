#include <iostream>
#include <inttypes.h>
#include "demodulator.h"

int main() {

	std::cout << "Demodulate, starting up" << std::endl;

	FILE *f;
	long size_in_bytes;
	long size_in_shorts;

	f = fopen( "onepacket.raw", "rb" );
	if ( f != NULL ) {

		fseek( f, 0, SEEK_END );
		size_in_bytes = ftell( f );
		size_in_shorts = size_in_bytes / 2;
		rewind( f );

		std::cout << "Processing " << size_in_shorts << " samples" << std::endl;

		int16_t *buffer = new int16_t[ size_in_shorts ];
		fread( (void *) buffer, 2, size_in_shorts, f );
		fclose( f ) ;

		Demodulator *demodulator = new Demodulator();

		demodulator->processBuffer( buffer, size_in_shorts ); // only handles int16_t for now

		delete demodulator;
		delete[] buffer;
	}

	std::cout << "Demodulate, shutting down" << std::endl;

	return 0;
}