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
  voices.push_back(main);
}

double Synth::tick() {
  return voices.at(0).tick();
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
  voices.at(0).set_attack(val);
}
void Synth::set_release(float val){
  voices.at(0).set_release(val);
}
