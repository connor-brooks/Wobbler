#ifndef VOICE_H
#define VOICE_H
#include "libs/maximilian.h"
#include "defs.h"

class Voice {
  public:
    Voice();
    double tick();
    void set_carrier_freq(float freq);
    void set_modulator_freq();
    void trigger(int _note);
    void trigger_off();
    void set_attack();
    void set_release();
    void set_settings(Voice_settings* ptr);
    int get_status();
  private:
    int note_on;
    maxiOsc carrier, modulator;
    maxiEnv env;
    float carrier_freq;
    Voice_settings* settings;
    float note_to_freq(int note);
    int voice_status;
};

#endif
