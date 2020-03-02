#include <iostream>
#include <math.h>
#include "synth.h"
#include "voice.h"
#include "defs.h"
#include "libs/maximilian.h"
Synth::Synth() {
  std::cout << "init" << std::endl;
  amplitude = 1.0f;
  set_lfo_freq(settings.lfo_freq);
  settings.detune_amt = 1;
  settings.modulator_freq = 100;
  settings.cutoff = 1;
  settings.lfo_freq = 1;
  settings.adsr.attack = 50;
  settings.adsr.release = 300;
}

double Synth::tick() {
  prune_voices();
  float wave = 0.0f;
  int voice_count = voices.size();
  int active_voices = 0;
  float lfo_freq_calc;
  float output;
  int current_voice_status = -1;
  /* combine any active voices */
  for(int i = 0; i < voice_count; i++){
    current_voice_status = voices.at(i)->get_status();
    if((current_voice_status == VSTATE_KEYDOWN) ||
        (current_voice_status == VSTATE_KEYUP)) {
      wave += voices.at(i)->tick();
      active_voices++;
    }
  }
  /* scale the voice for 8 channels */
  if(active_voices > 0)
  wave = wave / 8;
  
  /* Calculate the filters cutoff value using LFO, use it to filter wave */
  lfo_freq_calc = settings.cutoff * abs(lfo.sinewave(settings.lfo_freq));
  output = filter.lopass(wave, lfo_freq_calc);

  /* If any erronious values meet the filter causing a NaN, restart it */
  if(isnan(output)) {
    printf("NAN ERROR at filter \n");
    filter = maxiFilter();
  }
  return output;
}

void Synth::set_modulator_freq(float freq) {
  settings.modulator_freq = freq;
  int voice_count = voices.size();
  for(int i = 0; i < voice_count; i++){
    voices.at(i)->set_modulator_freq();
  }
}

void Synth::trigger_note(int note)
{
//  printf("Triggering note: %d\n", note);
  int voice_count = voices.size();
//  if(voice_count > 7) return;
  for(int i = 0; i < voice_count; i++) {
    if((voices.at(i)->get_note_num() == note) &&
        (voices.at(i)->get_status() == VSTATE_KEYDOWN))
      return;
  }
  Voice* temp = new_voice();
  temp->trigger(note);
  voices.push_back(temp);
}

void Synth::trigger_note_off(int note){
 // printf("Detriggering note: %d\n", note);
  int voice_count = voices.size();
  for(int i = 0; i < voice_count; i++){
    if(voices.at(i)->get_note_num() == note)
      voices.at(i)->trigger_off();
  }
}

void Synth::set_detune_freq(float freq)
{
  settings.detune_amt = freq;
}

void Synth::set_attack(float val) {
  settings.adsr.attack = val;
  int voice_count = voices.size();
  for(int i = 0; i < voice_count; i++){
    voices.at(i)->set_attack();
  }
}

void Synth::set_release(float val){
  settings.adsr.release = val;
  int voice_count = voices.size();
  for(int i = 0; i < voice_count; i++){
    voices.at(i)->set_release();
  }
}

void Synth::set_cutoff(float freq) {
  settings.cutoff = freq;
}

Voice* Synth::new_voice() {
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
void Synth::prune_voices() {
  int voice_count = voices.size();
  for(int i = 0; i < voice_count; i++){
    if(voices.at(i)->get_status() == VSTATE_DEAD){
      delete voices.at(i);
      voices.erase(voices.begin() + i);
      return;
    }
  }

}
