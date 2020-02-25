#ifndef VOICE_H
#define VOICE_H
#include "libs/maximilian.h"
class Voice {
  public:
    Voice();
    double tick();
    void set_carrier_freq(float freq);
    void set_modulator_freq(float freq);
    void trigger();
    void trigger_off();
  private:
    int note_on;
    maxiOsc carrier, modulator;
    maxiEnv env;
    float carrier_freq;
    float modulator_freq;
    float amplitude;
};

#endif
