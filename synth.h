#ifndef SYNTH_H
#define SYNTH_H
#include "libs/maximilian.h"
class Synth {
  public:
    Synth();
    double tick();
    void set_carrier_freq(float freq);
    void set_modulator_freq(float freq);
  private:
    float carrier_freq;
    float modulator_freq;
    maxiOsc carrier, modulator;
};

#endif
