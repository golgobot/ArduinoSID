#ifndef REGISTER_H
#define REGISTER_H

#include "HardwareSerial.h"

struct Register
{
	Register(){}
	Register(char a):address(a), data(0)
	{
		
	}
	char address;
	char data;
	char getData()
	{
		return data;
	}
};

struct ControlRegister
{
	ControlRegister(char a):address(a), data(0){}
	bool gated;
	char address;
	char data;
	char getData()
	{
		return data | gated; 
	}
};

struct ResonanceFilterRegister
{
	ResonanceFilterRegister(char a):address(a){}
	char address;
	char voiceSelects;
	char resonance;
	
	char getData()
	{
		return (resonance << 4) | voiceSelects;
	}
};

struct ModeVolumeRegister
{
	ModeVolumeRegister(char a):address(a), data(0){}
	char address;
	char data;
	char volume;
	bool lowPassEnabled;
	bool hiPassEnabled;
	bool bandPassEnabled;
	bool threeOffEnabled;
	char getData()
	{
		return (threeOffEnabled << 7) | (hiPassEnabled << 6) | (bandPassEnabled << 5) | (lowPassEnabled << 4) | volume;
	}
};
#endif