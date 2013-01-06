#include "Arduino.h"
#include "SID.h"

#define MODE_READ 1
#define MODE_WRITE 2

char SID::data[8] = {0,0,0,0,0,0,0,0};
int SID::dataBusMap[8] = {32,34,36,38,40,42,44,46};
int SID::addressBusMap[5] = {30,28,26,24,22};
int SID::chipSelect[3] = {50, 52, 53};



SID::SID(int address):_address(address), _v0(0), _v1(1), _v2(2), _mode(0)
{
	Serial.print("New SID addres: ");
	Serial.println(_address, DEC);
	
	_voices = (Voice*) malloc(sizeof(Voice) * 3);
	_voices[0] = _v0;
	_voices[1] = _v1;
	_voices[2] = _v2;

	for(int i = 0; i < 3; i++)
	{
		pinMode(chipSelect[i], OUTPUT);
		digitalWrite(chipSelect[i], LOW);
	}
	
	//select();
	
	//select();
	pinMode(RW, OUTPUT);

	//set to always read
	digitalWrite(RW, LOW);

	for(int i = 0; i < 5; i++)  
	{
		pinMode(addressBusMap[i], OUTPUT);
	}
  
	for(int i = 0; i < 8; i++)  
	{
		pinMode(dataBusMap[i], OUTPUT);
	}
	
	//readMode();
	//deselect();
}

void SID::readMode()
{
	select();
	digitalWrite(RW, HIGH);
	if(_mode == MODE_READ)
	{
		delayMicroseconds(2);
		return;
	}
	_mode = MODE_READ;
	for(int i = 0; i < 8; i++)  
	{
		pinMode(dataBusMap[i], INPUT);
	}
	delayMicroseconds(2);
	deselect();
}

void SID::writeMode()
{
	select();
	digitalWrite(RW, LOW);
	if(_mode == MODE_WRITE)
	{
		delayMicroseconds(2);
		return;
	}
	_mode = MODE_WRITE;
	for(int i = 0; i < 8; i++)  
	{
		pinMode(dataBusMap[i], OUTPUT);
	}
	delayMicroseconds(2);
	deselect();
}

void SID::select()
{
	//chip select the SID this class is controlling
	for(int i = 0; i < 3; i++)
	{
		digitalWrite(chipSelect[i], i == _address ? LOW : HIGH);
	}
}

void SID::deselect()
{
	//deselect all sids
	for(int i = 0; i < 3; i++)
	{
		digitalWrite(chipSelect[i], HIGH);
	}
}

void SID::writeData(ControlRegister cr)
{
	writeData(cr.address,  cr.getData());
}

void SID::writeData(ResonanceFilterRegister rfr)
{
	writeData(rfr.address,  rfr.getData());
}

void SID::writeData(ModeVolumeRegister mvr)
{
	writeData(mvr.address,  mvr.getData());
}

void SID::writeData(Register r)
{
	writeData(r.address,  r.getData());
}

void SID::writeData(unsigned char address, unsigned char data)
{
	select();
	for(int i = 0; i < 8; i++)  
	{
		pinMode(dataBusMap[i], OUTPUT);
	}
	//Put address on address bus
	int val = 1;
	for(int i = 0; i < 5; i++)  
	{
		digitalWrite(addressBusMap[i], (address & val) > 0 ? HIGH : LOW);
		val = val << 1;
	}
	
	//Put data on data bus
	val = 1;
	for(int i = 0; i < 8; i++)  
	{
		digitalWrite(dataBusMap[i], (data & val) > 0 ? HIGH : LOW);
		val = val << 1;
	}
	
	digitalWrite(RW, LOW);
	delay(1);
	digitalWrite(RW, HIGH);
	for(int i = 0; i < 8; i++)  
	{
		pinMode(dataBusMap[i], INPUT);
	}
	deselect();
}

void SID::setVoiceFrequency(int voiceNum, float frequency)
{
	Voice* v = &_voices[voiceNum];
	v->setFrequency(frequency);
	writeData(v->getFreqLo());
	writeData(v->getFreqHi());
}

void SID::setADSR(int voiceNum, char a, char d, char s, char r)
{
	Voice* v = &_voices[voiceNum];
	v->setADSR(a, d, s, r);
	writeData(v->getAD());
	writeData(v->getSR());
}

void SID::setCutoffFreq(float freq)
{
	_filter.setCutoffFreq(freq);
	writeData(_filter.getCutoffFreqLo());
	writeData(_filter.getCutoffFreqHi());
}

void SID::setVoiceFiltered(char voiceId, bool enabled)
{
	_filter.setVoiceFiltered(voiceId, enabled);
	writeData(_filter.getResFilter());
}

void SID::setResonance(char val)
{
	_filter.setResonance(val);
	writeData(_filter.getResFilter());
}

void SID::setLowPassEnabled(bool enabled)
{
	_filter.setLowPassEnabled(enabled);
	writeData(_filter.getModeVol());
}

void SID::setHiPassEnabled(bool enabled)
{
	_filter.setHiPassEnabled(enabled);
	writeData(_filter.getModeVol());
}

void SID::setBandPassEnabled(bool enabled)
{
	_filter.setBandPassEnabled(enabled);
	writeData(_filter.getModeVol());
}

void SID::set3OffEnabled(bool enabled)
{
	_filter.set3OffEnabled(enabled);
	writeData(_filter.getModeVol());
}

void SID::setVolume(char val)
{
	_filter.setVolume(val);
	writeData(_filter.getModeVol());
}

void SID::setGate(int voiceNum, int value)
{
	Serial.print("Playing note on address ");
	Serial.println(_address, DEC);
	Voice* v = &_voices[voiceNum];
	v->setGate(value == HIGH ? true : false);
	writeData(v->getControlRegister());
}

void SID::setSquare(int voiceNum)
{
	Voice* v = &_voices[voiceNum];
	v->setMode(Voice::SQUARE);
	writeData(v->getPwLo());
	writeData(v->getPwHi());
	writeData(v->getControlRegister());
}

void SID::setTriangle(int voiceNum)
{
	Voice* v = &_voices[voiceNum];
	v->setMode(Voice::TRIANGLE);
	writeData(v->getControlRegister());
}

void SID::setSawTooth(int voiceNum)
{
	Voice* v = &_voices[voiceNum];
	v->setMode(Voice::SAWTOOTH);
	writeData(v->getControlRegister());
}

void SID::setNoise(int voiceNum)
{
	Voice* v = &_voices[voiceNum];
	v->setMode(Voice::NOISE);
	writeData(v->getControlRegister());
}

void SID::setRingMod(int voiceNum)
{
	Voice* v = &_voices[voiceNum];
	v->setMode(Voice::RINGMOD);
	writeData(v->getControlRegister());
}
