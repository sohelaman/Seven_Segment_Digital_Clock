
Simple digital clock program using timer.
Using Arduino/Atmega uC and common anode 4 digit 7-segment display.

If Atmega8 chip is used then following definition codes needs to be included in TimerOne Class.
    #if defined(__AVR_ATmega8__)
    #define TIMSK1 TIMSK
    #define GTCCR SFIOR
    #define PSRSYNC PSR10
    #endif
