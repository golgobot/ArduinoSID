#include "Filter.h"

Filter::Filter():
	_cutoffFreqLo(0x15),
	_cutoffFreqHi(0x16),
	_resFilter(0x17),
	_modeVol(0x18)
{

}

void Filter::setCutoffFreq(float freq)
{
	freq = freq > 11818.0 ? 11818.0 : freq;
	unsigned short fn = (unsigned short)(freq * 0.173210357);
	_cutoffFreqLo.data = fn & 0x7;
	_cutoffFreqHi.data = fn >> 3;
}

void Filter::setResonance(char val)
{
	_resFilter.resonance = val;
}

void Filter::setVoiceFiltered(int voiceNum, bool filter)
{
	if(filter)
	{
		_resFilter.voiceSelects |= 1 << voiceNum;
	}
	else
	{
		_resFilter.voiceSelects &= ~(1 << voiceNum);
	}
}

void Filter::setLowPassEnabled(bool enabled)
{
	_modeVol.lowPassEnabled = enabled;
}

void Filter::setHiPassEnabled(bool enabled)
{
	_modeVol.hiPassEnabled = enabled;
}

void Filter::setBandPassEnabled(bool enabled)
{
	_modeVol.bandPassEnabled = enabled;
}

void Filter::set3OffEnabled(bool enabled)
{
	_modeVol.threeOffEnabled = enabled;
}

void Filter::setVolume(char vol)
{
	_modeVol.volume = vol;
}

Register Filter::getCutoffFreqLo()
{
	return _cutoffFreqLo;
}

Register Filter::getCutoffFreqHi()
{
	return _cutoffFreqHi;
}

ResonanceFilterRegister Filter::getResFilter()
{
	return _resFilter;
}

ModeVolumeRegister Filter::getModeVol()
{
	return _modeVol;
}