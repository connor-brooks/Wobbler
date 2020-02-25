#include <iostream>
#include "synth.h"
#include "voice.h"
#include "defs.h"
#include "libs/maximilian.h"
Synth::Synth() {
  std::cout << "init" << std::endl;
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
  voices.at(0).trigger();
}
void Synth::trigger_note_off(int note){
  voices.at(0).trigger_off();
}
