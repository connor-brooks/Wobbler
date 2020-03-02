#ifndef MIDI_H
#define MIDI_H
#include <rtMidi.h>

class Midi {
  private:
    RtMidiIn *midi_in;
    int num_bytes;
    int num_ports;
    int last_check;
    std::vector<unsigned char> msgs;
    bool has_connection;
    std::function<void (int)> keydown_callback;
    std::function<void (int)> keyup_callback;
  public:
    Midi();
    void get_messages();
    void handle_messages();
    void set_keydown_callback(std::function<void (int)> callb);
    void set_keyup_callback(std::function<void (int)> callb);
};

#endif
