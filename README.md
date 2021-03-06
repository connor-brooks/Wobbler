![](wobbler.png)
*A software synth (WORK IN PROGRESS)*

Wobbler is a software FM synthesiser. It can be controlled by the user in a number of ways:
* GUI and computer keyboard
* MIDI keyboard
* Scriptable command line interface

Although Wobbler is still under heavy development, most of the core features have been implemented: 
* User selectable waveforms (sine, square, sawtooth, triangle)
* Detune
* FM synthesis
* ADSR (Well, attack and release)
* Low pass filter
* LFO for lowpass filter cutoff
* MIDI note input
* Command line parameter and note control

Wobbler is a GUI for Mick Grierson's [Maximilian](https://github.com/micknoise/Maximilian), a C++ DSP and synthesis library. However, due to some bugs in Maximilian's library, synthesis functions will be rewritten from scratch for Wobbler (at some point).

## Dependencies 
* SDL2
* rtmidi 

## How to use (Mac)
* Install dependencies: `brew install sdl2 rtmidi`
* Clone the repo: `https://github.com/connor-brooks/Wobbler.git`
* Enter the director: `cd Wobbler`
* Build: `make`
* To run in GUI mode: `./wob`
* To run in CLI mode: `./wob --no-gui`

Note: Currently there is no Makefile for Linux, but a slight bit of tweaking and it should compile fine.

## What is Wobbler for?
In short, it is to enable quick experimentation with synthesis parameters, in a way that mimics the experience of a hardware synth. In addition to offering a typical GUI, the synth can also be controlled via MIDI and your terminals standard input. This opens up allows the synth to be easily scripted.

## Controls

### MIDI
Notes can be played by connecting a MIDI keyboard to your computer before starting Wobbler, changing synth parameters via CC will be added soon.

### GUI
Currently the GUI controls aren't labeled, however, here is a reference:

![](screenshot.png)

| Carrier waveform | Carrier detune | Modulator waveform | Carrier/modulator ratio | Attack time | Release time | Cutoff frequency | LFO rate |
|------------------|----------------|--------------------|-------------------------|-------------|--------------|------------------|----------|


### Computer Keyboard
If you don't have a MIDI keyboard, you can use your computer's keyboard to play notes and change octave:
![](keyboard.png)

### Command line
Additionally, the synth can be controlled via the command line, below is a list of commands:

| Command name | Arguments | Description                                       |
|--------------|-----------|---------------------------------------------------|
| rand         | n/a       | Randomise synth parameters                        |
| help         | n/a       | Display a list of commands                        |
| quit         | n/a       | Quit the program                                  |
| noteon       | midi note | Turn a note on                                    |
| noteoff      | midi note | Turn a note off                                   |
| car_wave     | 0.0 - 1.0 | Set the carrier wave                              |
| detune       | 0.0 - 1.0 | Set the detune amount                             |
| mod_wave     | 0.0 - 1.0 | Set the modulator wave                            |
| mod_ratio    | 0.0 - 1.0 | Set the modulators ratio w.r.t. carrier frequency |
| attack       | 0.0 - 1.0 | Set the attack time                               |
| release      | 0.0 - 1.0 | Set the release time                              |
| cutoff       | 0.0 - 1.0 | Set the cutoff                                    |
| lfo          | 0.0 - 1.0 | Set the LFO speed                                 |

If you are soley interested in using the synth via scripting or command line, it is possible to start the program without a GUI, in order to do this, run `./wob --no-gui`

### Scripting
As Wobbler accepts commands from standard console input, is possible to script sequences and synth changes using any language you'd like. To see an example of this, please check out `test.sh`

## Notes
* Sometimes notes will randomly be dropped, especially when notes are played very fast. This is due to a bug in Maximilian's envelope function. Currently there is little that can be done about this, however, eventually Maximilian's synthesis functions will be replaced by custom Wobbler specific functions, remedying this issue.
* Currently there is no Linux Makefile, however Wobbler should compile fine on any Linux machine given a bit of tinkering. One will be added shortly. 
