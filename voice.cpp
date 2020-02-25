#include <iostream>
#include "voice.h"
#include "defs.h"
#include "libs/maximilian.h"
Voice::Voice() {
  std::cout << "init" << std::endl;
  carrier_freq = 440;
  modulator_freq = 1;
  amplitude = 1.0f;
  note_on = 0;

  this->env.setAttack(50);
  this->env.setDecay(1);
  this->env.setSustain(1);
  this->env.setRelease(300);
}

double Voice::tick() {
  float wave = AMPLITUDE * amplitude *
    carrier.square(carrier_freq +
        (modulator.sinewave(modulator_freq)*100)
        );
  return env.adsr(wave, note_on);
}

void Voice::set_carrier_freq(float freq) {
  carrier_freq = freq;
}

void Voice::set_modulator_freq(float freq) {
  modulator_freq = freq;
}

void Voice::trigger() {
note_on = 1;
}

void Voice::trigger_off() {
note_on = 0;
}
