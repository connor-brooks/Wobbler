#include <iostream>
#include "voice.h"
#include "defs.h"
#include "libs/maximilian.h"
Voice::Voice() {
  std::cout << "init" << std::endl;
  carrier_freq = 440;
  note_on = 0;
  this->env.setAttack(30);
  this->env.setDecay(1);
  this->env.setSustain(1);
  this->env.setRelease(300);
}

double Voice::tick() {
  float wave = AMPLITUDE *
    carrier.sinewave(carrier_freq +
        (modulator.square(settings->modulator_freq)*100)
        );
  float envolope = env.adsr(1, note_on);
  /* for debug */
  //  printf("wave %f\n", envP);
  //  if(envP < 0.00001)
  //    printf("Wave ended\n");
  return wave * envolope;
}

void Voice::set_carrier_freq(float freq) {
  carrier_freq = freq;
}

void Voice::set_modulator_freq() {
  // Do nothing, mod freq grabbed in tick()
}

void Voice::trigger(int _note) {
  note_on = 1;
  float voice_freq = note_to_freq(_note) * settings->detune_amt;
  set_carrier_freq(voice_freq);
}

void Voice::trigger_off() {
  note_on = 0;
}

void Voice::set_attack() {
  env.setAttack(settings->adsr.attack);
}

void Voice::set_release() {
  env.setRelease(settings->adsr.release);
}
void Voice::set_settings(Voice_settings* ptr) {
  settings = ptr;
}

float Voice::note_to_freq(int note) {
  return pow(2, (note-69)/12.0)*440;
}
