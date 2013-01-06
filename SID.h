#ifndef SID_H
#define SID_H

#include "Voice.h"
#include "Filter.h"

#define RW 48

class SID
{
public:
	SID(int address);

	void setCutoffFreq(float freq);
	void setVoiceFiltered(char voiceId, bool enabled);
	void setResonance(char val);
	void setLowPassEnabled(bool enabled);
	void setHiPassEnabled(bool enabled);
	void setBandPassEnabled(bool enabled);
	void set3OffEnabled(bool enabled);
	void setVolume(char val);
	void setVoiceFrequency(int voiceNum, float frequency);
	void setADSR(int voiceNum, char a, char d, char s, char r);
	void setGate(int voiceNum, int value);
	void setSquare(int voiceNum);
	void setTriangle(int voiceNum);
	void setSawTooth(int voiceNum);
	void setNoise(int voiceNum);
	void setRingMod(int voiceNum);
private:
	void writeData(Register r);
	void writeData(ControlRegister r);
	void writeData(ResonanceFilterRegister r);
	void writeData(ModeVolumeRegister r);
	void writeData(unsigned char address, unsigned char data);
	void select();
	void deselect();
	void readMode();
	void writeMode();
	static char data[8];
	static int dataBusMap[8];
	static int addressBusMap[5];
	static int chipSelect[3];
	Voice* _voices;
	Voice _v0;
	Voice _v1;
	Voice _v2;
	Filter _filter;
	int _address;
	Register _register;
	char _mode;
};

#endif