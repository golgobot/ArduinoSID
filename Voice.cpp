#include "Voice.h"

Voice::Voice(char id):
	_freqLo(7 * id + 0),
	_freqHi(7 * id + 1),
	_pwLo(7 * id + 2),
	_pwHi(7 * id + 3),
	_control(7 * id + 4),
	_ad(7 * id + 5),
	_sr(7 * id + 6)
{
	_id = id;
	_freq = 0.0;

	//set pwm to even pulses for now
	_pwLo.data = 0;
	_pwHi.data = 8;
}

void Voice::setGate(bool val)
{
	_control.gated = val;
}

void Voice::toggleGated()
{
	_control.gated = !_control.gated;
}

void Voice::setMode(Mode m)
{
	_control.data = m;
}

void Voice::setFrequency(float freq)
{
	_freq = 0;
	unsigned short fn = (unsigned short)(freq / 0.0596);
	_freqLo.data = fn & 0xFF;
	_freqHi.data = fn >> 8;
}

void Voice::setADSR(char a, char d, char s, char r)
{
	_ad.data = (a << 4) | d;
	_sr.data = (s << 4) | r;
}

ControlRegister Voice::getControlRegister()
{
	return _control;
}

Register Voice::getFreqLo()
{
	return _freqLo;
}

Register Voice::getFreqHi()
{
	return _freqHi;
}

Register Voice::getAD()
{
	return _ad;
}

Register Voice::getSR()
{
	return _sr;
}

Register Voice::getPwLo()
{
	return _pwLo;
}

Register Voice::getPwHi()
{
	return _pwHi;
}