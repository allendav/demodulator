# demodulator
A packet radio demodulator designed to work with rtl_fm

TODO
====

- [ ] Finish the framer
- [ ] Extract frame meta data
- [ ] Detect and handle loss of carrier
- [ ] Accept sample rate and format parameters on the command line
- [ ] Accept samples via STDIN from rtl_fm
- [ ] Use a Makefile for building

Building
========

    g++ demodulate.cpp demodulator.cpp framer.cpp -o demodulate
    chmod +x demodulate

Running
=======

    ./demodulate

(assumes the test file onepacket.raw is in the same directory)
