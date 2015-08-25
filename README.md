# demodulator
A packet radio demodulator designed to work with rtl_fm

TODO
====

o Finish the framer
o Extract frame meta data
o Detect and handle loss of carrier
o Accept sample rate and format parameters on the command line
o Accept samples via STDIN from rtl_fm
o Use a Makefile for building

Building
========

    g++ demodulate.cpp demodulator.cpp framer.cpp -o demodulate
    chmod +x demodulate

Running
=======

    ./demodulate

(assumes the test file onepacket.raw is in the same directory)
