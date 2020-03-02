#include <rtMidi.h>
#include "midi.h"

Midi::Midi() {
  has_connection = false;
  midi_in = new RtMidiIn();
  num_ports = midi_in->getPortCount();
  if(num_ports == 0) {
    has_connection = false;
    return;
  }
  else {
    midi_in->openPort(0);
    midi_in->ignoreTypes(false, false, false);
    has_connection = true;
  }
}

void Midi::get_messages() {
  if(!has_connection) return;
  midi_in->getMessage(&msgs);
  num_bytes = msgs.size();
}


void Midi::handle_messages() {
  if(num_bytes > 0 ) {
    if(msgs[0] == 144) {
      printf("NOTE %d DOWN\n", msgs[1]);
      keydown_callback(msgs[1]);
    }
    if(msgs[0] == 128) {
      printf("NOTE %d UP\n", msgs[1]);
      keyup_callback(msgs[1]);
    }
  }
}

void Midi::set_keydown_callback(std::function<void (int)> callb){
  keydown_callback = callb;
}

void Midi::set_keyup_callback(std::function<void (int)> callb){
  keyup_callback = callb;
}
