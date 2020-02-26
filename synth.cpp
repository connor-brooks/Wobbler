#include <iostream>
#include <math.h>
#include "synth.h"
#include "voice.h"
#include "defs.h"
#include "libs/maximilian.h"
Synth::Synth() {
  std::cout << "init" << std::endl;
  detune = 0;
  modulator_freq = 1;
  amplitude = 1.0f;
  Voice main;
  cutoff = 1;
  voices.push_back(main);
  adsr.attack = 50;
  adsr.release = 300;
}

double Synth::tick() {
  float wave = voices.at(0).tick();
  /* debug, add switch */
  return filter.lopass(wave, cutoff);
}

void Synth::set_carrier_freq(float freq) {
  voices.at(0).set_carrier_freq(freq);
}

void Synth::set_modulator_freq(float freq) {
  voices.at(0).set_modulator_freq(freq);
}

void Synth::trigger_note(int note)
{
  voices.at(0).set_carrier_freq(midi_to_freq(note) + detune);
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
  detune = freq;
}
void Synth::set_attack(float val) {
  adsr.attack = val;
  voices.at(0).set_attack(adsr.attack);
}
void Synth::set_release(float val){
  adsr.release = val;
  voices.at(0).set_release(adsr.release);
}
void Synth::set_cutoff(float freq) {
  cutoff = freq;
}

Voice* Synth::new_voice(int note, float detune, float modulator_f) {
  Voice* temp = new Voice;
  temp->set_modulator_freq(modulator_freq);
  temp->set_attack(adsr.attack);
  temp->set_release(adsr.release);
  // set default note (move note conversion to voice)
  return temp;
}
