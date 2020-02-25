#ifndef SYNTH_H
#define SYNTH_H
#include "libs/maximilian.h"
#include "voice.h"
class Synth {
  public:
    Synth();
    double tick();
    void set_carrier_freq(float freq);
    void set_modulator_freq(float freq);

    void trigger_note(int note);
    void trigger_note_off(int note);

  private:
    float modulator_freq;
    float amplitude;
    std::vector<Voice> voices;

};

#endif
