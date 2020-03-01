#include <iostream>
#include <math.h>
#include "synth.h"
#include "voice.h"
#include "defs.h"
#include "libs/maximilian.h"
Synth::Synth() {
  std::cout << "init" << std::endl;
  amplitude = 1.0f;
  Voice main;
  voices.push_back(main);
  set_lfo_freq(settings.lfo_freq);
  settings.detune_amt = 1;
  settings.modulator_freq = 100;
  settings.cutoff = 1;
  settings.lfo_freq = 1;
  settings.adsr.attack = 50;
  settings.adsr.release = 300;
  voices.at(0).set_settings(&settings);
}

double Synth::tick() {
  float wave = voices.at(0).tick();
  /* Calculate the filters cutoff value using LFO */
  float lfo_freq_calc = settings.cutoff * abs(lfo.sinewave(settings.lfo_freq));

/*  if(voices.at(0).get_status() == VSTATE_PRETRIG)
    printf("pretrig voice \n");
  else if(voices.at(0).get_status() == VSTATE_KEYDOWN)
    printf("voice down \n");
  else if(voices.at(0).get_status() == VSTATE_KEYUP)
    printf("voice up \n");
  else if(voices.at(0).get_status() == VSTATE_DEAD)
    printf("voice dead \n"); */

  return filter.lopass(wave, lfo_freq_calc);
}

void Synth::set_modulator_freq(float freq) {
  settings.modulator_freq = freq;
  voices.at(0).set_modulator_freq();
}

void Synth::trigger_note(int note)
{
  printf("Triggering note: %d\n", note);
  voices.at(0).trigger(note);
}

void Synth::trigger_note_off(int note){
  printf("Detriggering note: %d\n", note);
  voices.at(0).trigger_off();
}

void Synth::set_detune_freq(float freq)
{
  settings.detune_amt = freq;
}

void Synth::set_attack(float val) {
  settings.adsr.attack = val;
  voices.at(0).set_attack();
}

void Synth::set_release(float val){
  settings.adsr.release = val;
  voices.at(0).set_release();
}

void Synth::set_cutoff(float freq) {
  settings.cutoff = freq;
}

Voice* Synth::new_voice(int note, float detune, float modulator_f) {
  Voice* temp = new Voice;
  temp->set_settings(&settings);
  temp->set_modulator_freq();
  temp->set_attack();
  temp->set_release();
  // set default note (move note conversion to voice)
  return temp;
}

void Synth::set_lfo_freq(float freq) {
  settings.lfo_freq = freq;
//lfo_freq = freq;
}
