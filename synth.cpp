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

}

double Synth::tick() {
  float wave = voices.at(0).tick();
  /* Calculate the filters cutoff value using LFO */
  float lfo_freq_calc = settings.cutoff * abs(lfo.sinewave(settings.lfo_freq));
  return filter.lopass(wave, lfo_freq_calc);
}

void Synth::set_carrier_freq(float freq) {
  voices.at(0).set_carrier_freq(freq);
}

void Synth::set_modulator_freq(float freq) {
  settings.modulator_freq = freq;
  voices.at(0).set_modulator_freq(settings.modulator_freq);
}

void Synth::trigger_note(int note)
{
  /* todo: push new voice to vector */
  float note_freq = midi_to_freq(note) * settings.detune_amt;
  voices.at(0).set_carrier_freq(note_freq);
  voices.at(0).trigger();
}

void Synth::trigger_note_off(int note){
  voices.at(0).trigger_off();
}
float Synth::midi_to_freq(int note) {
  return pow(2, (note-69)/12.0)*440;

}

void Synth::set_detune_freq(float freq)
{
  settings.detune_amt = freq;
}

void Synth::set_attack(float val) {
  settings.adsr.attack = val;
  voices.at(0).set_attack(settings.adsr.attack);
}

void Synth::set_release(float val){
  settings.adsr.release = val;
  voices.at(0).set_release(settings.adsr.release);
}

void Synth::set_cutoff(float freq) {
  settings.cutoff = freq;
}

Voice* Synth::new_voice(int note, float detune, float modulator_f) {
  Voice* temp = new Voice;
  temp->set_modulator_freq(settings.modulator_freq);
  temp->set_attack(settings.adsr.attack);
  temp->set_release(settings.adsr.release);
  // set default note (move note conversion to voice)
  return temp;
}

void Synth::set_lfo_freq(float freq) {
  settings.lfo_freq = freq;
//lfo_freq = freq;
}
