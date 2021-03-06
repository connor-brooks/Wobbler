#ifndef SYNTH_H
#define SYNTH_H
#include "libs/maximilian.h"
#include "voice.h"
#include "defs.h"
//http://subsynth.sourceforge.net/midinote2freq.html
class Synth {
  public:
    Synth();
    double tick();
    //void set_carrier_freq(float freq);
    void set_detune_freq(float freq);
    void set_modulator_ratio(float ratio);

    void trigger_note(int note);
    void trigger_note_off(int note);
    void set_attack(float val);
    void set_release(float val);
    void set_cutoff(float freq);
    void set_lfo_freq(float freq);
    void set_carrier_wave(float val);
    void set_mod_wave(float val);
    void prune_voices();

  private:
    maxiOsc lfo;
    maxiFilter filter;
    float amplitude;
    Voice* new_voice();
    std::vector<Voice*> voices;
    struct Voice_settings settings;
};

#endif
