#include "demodulator.h"
#include <iostream>
#include <math.h>

const double PI = 3.14159265;
const double MARKFREQ = 2200;
const double SPACEFREQ = 1200;
const double SAMPLERATE = 44100; // fixed for now
const double BAUDRATE = 1200;

#define MARK 1
#define SPACE 0

Demodulator::Demodulator() {
	framer = new Framer();
}

Demodulator::~Demodulator() {
	delete framer;
}

void Demodulator::processBuffer( int16_t *buffer, long numSamples ) {

	double markCoeff = 2.0 * cos( 2.0 * PI * MARKFREQ / SAMPLERATE );
	double spaceCoeff = 2.0 * cos( 2.0 * PI * SPACEFREQ / SAMPLERATE );

	std::cout << "markCoeff=" << markCoeff << std::endl;
	std::cout << "spaceCoeff=" << spaceCoeff << std::endl;

	long blockCount = floor( BAUDRATE * numSamples / SAMPLERATE ) - 1;

	long previousSymbol = MARK;
	long currentSymbol;

	double markSpaceDifference = 0;

	for ( long blockIndex = 0; blockIndex < blockCount; blockIndex++ ) {
		long startSampleIndex = floor( blockIndex * SAMPLERATE / BAUDRATE );

		double fMark[3] = { 0. };
		double fSpace[3] = { 0. };

		for ( long sampleIndex = startSampleIndex; sampleIndex < startSampleIndex + 36; sampleIndex++ ) {

			fMark[0] = buffer[ sampleIndex ] + markCoeff * fMark[1] - fMark[2];
			fMark[2] = fMark[1];
			fMark[1] = fMark[0];

			fSpace[0] = buffer[ sampleIndex ] + spaceCoeff * fSpace[1] - fSpace[2];
			fSpace[2] = fSpace[1];
			fSpace[1] = fSpace[0];
		}

		double markMagSq = fMark[1] * fMark[1] + fMark[2] * fMark[2] - markCoeff * fMark[1] * fMark[2];
		double spaceMagSq = fSpace[1] * fSpace[1] + fSpace[2] * fSpace[2] - spaceCoeff * fSpace[1] * fSpace[2];

		// TODO - sum the absolute differences within a single symbol markMag and spaceMag and maximize that

		if ( markMagSq > spaceMagSq ) {
			currentSymbol = MARK;
		} else {
			currentSymbol = SPACE;
		}

		framer->addBit( currentSymbol == previousSymbol );

		// TODO - handle loss of carrier

		previousSymbol = currentSymbol;
	}

	std::cout << std::endl;

}