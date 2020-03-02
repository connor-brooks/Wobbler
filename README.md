![](wobbler.png)
*A software synth (WORK IN PROGRESS)*

Wobbler is a software synth. At the moment, don't bother downloading it, as it's in a heavy state of development.

Some of the features that are currently implemented: 
* FM synthesis
* Low pass filter
* LFO for lowpass filter cutoff
* MIDI input
* ADSR (Well, attack and release)

Wobbler is a GUI for Mick Grierson's [Maximilian](https://github.com/micknoise/Maximilian), a C++ DSP and synthesis library. However, at some point synthesis functions will be rewritten especially for wobbler.

## Dependencies 
* SDL2
* rtaudio
* rtmidi 

## What is Wobbler for?
In short, it is to enable quick experimentation with synthesis parameters, in a way that mimics the experience of a hardware synth.

## How to use Wobbler
* Compile
* Connect MIDI keyboard
* Tweak the (unlabeled) parameters until you find a sound you like

## Screenshot
![](screenshot.png)
