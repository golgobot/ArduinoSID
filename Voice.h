#ifndef VOICE_H
#define VOICE_H

#include "Registers.h"

class Voice
{
public:
	enum Mode {
		NOISE = 0x80,
		SQUARE = 0x40,
		SAWTOOTH = 0x20,
		TRIANGLE = 0x10,
		RINGMOD = 0x14,
		SYNC = 0x2,
	};
	Voice(char id);

	void setGate(bool val);
	void toggleGated();
	void setMode(Mode m);
	void setFrequency(float freq);
	void setADSR(char a, char d, char s, char r);

	ControlRegister getControlRegister();
	Register getFreqLo();
	Register getFreqHi();
	Register getAD();
	Register getSR();
	Register getPwLo();
	Register getPwHi();
private:
	char _id;
	float _freq;
	Register _freqLo;
	Register _freqHi;
	Register _pwLo;
	Register _pwHi;
	ControlRegister _control;
	Register _ad;
	Register _sr;
};

#endif