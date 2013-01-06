#ifndef FILTER_H
#define FILTER_H

#include "Registers.h"

class Filter
{
public:
	Filter();

	void setCutoffFreq(float freq);
	void setResonance(char val);
	void setLowPassEnabled(bool enabled);
	void setHiPassEnabled(bool enabled);
	void setBandPassEnabled(bool enabled);
	void set3OffEnabled(bool enabled);
	void setVolume(char vol);
	void setVoiceFiltered(int voiceNum, bool filter);
	
	Register getCutoffFreqLo();
	Register getCutoffFreqHi();
	ResonanceFilterRegister getResFilter();
	ModeVolumeRegister getModeVol();
private:
	Register _cutoffFreqLo;
	Register _cutoffFreqHi;
	ResonanceFilterRegister _resFilter;
	ModeVolumeRegister _modeVol;
	void updateModeVol();
};

#endif