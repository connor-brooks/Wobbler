#ifndef SYNTH_H
#define SYNTH_H
#include "libs/maximilian.h"
#include "voice.h"
//http://subsynth.sourceforge.net/midinote2freq.html
class Synth {
  public:
    Synth();
    double tick();
    void set_carrier_freq(float freq);
    void set_detune_freq(float freq);
    void set_modulator_freq(float freq);

    void trigger_note(int note);
    void trigger_note_off(int note);
    void set_attack(float val);
    void set_release(float val);

    void set_cutoff(float freq);

  private:
    maxiFilter filter;
    float cutoff;
    float modulator_freq;
    float amplitude;
    float midi_to_freq(int note);
    float detune;
    std::vector<Voice> voices;

};

#endif
