#include <iostream>
#include "voice.h"
#include "defs.h"
#include "libs/maximilian.h"
Voice::Voice() {
  carrier_freq = 440;
  note_on = 1;
  this->env.setAttack(30);
  this->env.setDecay(1);
  this->env.setSustain(1);
  this->env.setRelease(300);
  voice_status = VSTATE_PRETRIG;
  note_num = 0;
}

float Voice::get_wave(maxiOsc *osc, int wavetype, float freq) {
  float output = 0.0f;
  switch(wavetype) {
    case WAVE_SINE:
      output = osc->sinewave(freq);
      break;
    case WAVE_SQUARE:
      output = osc->square(freq);
      break;
    case WAVE_TRI:
      output = osc->triangle(freq);
      break;
    case WAVE_SAW:
      output = osc->saw(freq);
      break;
    default:
      break;
  };
  return output;
}

double Voice::tick() {
  float output = 0.0f;
  bool errors = false;
  float modulator_freq = carrier_freq * settings->modulator_ratio;
  float modulator_wave = 0.0f;
  float wave = 0.0f;
  float envolope;

  /* Create modulator wave, scale it by 100 to use for FM */
  modulator_wave = get_wave(&modulator, settings->mod_wave, modulator_freq);
  modulator_wave *= 100;

  /* Create carrier wave, scale it by global amplitude settings to
   * be written to buffer */
  wave = get_wave(&carrier, settings->carrier_wave, carrier_freq + modulator_wave);
  wave *= AMPLITUDE;

  envolope = env.adsr(1, note_on);
  /* If env is dead, set status to dead, but only if the key is past being triggered and release (prevents ramp up values causing death  */
  if(envolope < 0.0001 && voice_status == VSTATE_KEYUP)
    voice_status = VSTATE_DEAD;

  output = wave * envolope;

  /* Catch any voice errors before the propagate up to the synth's main filter. After a lot of investigation it turns out occasionally Maximilian splits out a NaN as a value for a voice or envelope. There isn't much I can do about this right now, other than to drop any voice that does this to prevent further issues..*/
  if(isinf(envolope)) {
    printf("INF error at voice env\n");
    envolope = 0.0f;
    errors = true;
  }

  if(isnan(wave)) {
    printf("NAN error at voice wave\n");
    errors = true;
  }
  if(isnan(envolope)) {
    printf("NAN error at voice env\n");
    errors = true;
  }
  if(isnan(output)) {
    printf("NAN error at voice output (%f * %f)\n", wave, envolope);
    output = 0.0f;
    errors = true;
  }
  if(errors == true) voice_status = VSTATE_DEAD;

  return output;
}

void Voice::set_carrier_freq(float freq) {
  carrier_freq = freq;
}

void Voice::set_modulator_ratio() {
  // Do nothing, mod freq grabbed in tick()
}

void Voice::trigger(int _note) {
  note_on = 1;
  note_num = _note;
  voice_status = VSTATE_KEYDOWN;
  float voice_freq = note_to_freq(note_num) * settings->detune_amt;
  set_carrier_freq(voice_freq);
}

void Voice::trigger_off() {
  note_on = 0;
  voice_status = VSTATE_KEYUP;
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

int Voice::get_status() {
  return voice_status;
}

int Voice::get_note_num() {
  return note_num;
}
