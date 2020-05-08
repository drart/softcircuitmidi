#include "MIDIUSB.h"
//#include "MIDI.h"

//MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

int led = 13;

// the MIDI channel number to send messages
const int channel = 1;

// the MIDI continuous controller for each analog input
const int controllerA0 = 10; // 10 = pan position
const int controllerA1 = 11; // 11 = volume/expression
const int controllerA2 = 91; // 91 = reverb level
const int controllerA3 = 93; // 93 = chorus level

// store previously sent values, to detect changes
int previousA0 = -1;
int previousA1 = -1;
int previousA2 = -1;
int previousA3 = -1;

elapsedMillis msec = 0;


const int buttonPin = 2;

// from examples
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void aftertouch(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xA0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}


unsigned int data[500];//~1kb loop memory
unsigned int data2[500];

boolean recording = false;
int ndx = 0;

void setup(){
    pinMode(led, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    
    for (int i = 0; i < 500; i++){
        data[i] = i  % 255;
        data2[i] = i % 255; 
    }
}

void loop(){
  if(recording != true){
    if (digitalRead(buttonPin) == LOW){
      midiEventPacket_t noteOn = {0x09, 0x90 | 1, 36, 100};
      MidiUSB.sendMIDI(noteOn);    
      recording = true;
      ndx = 0;
    }
  }

  if (recording){
    data[ndx] = analogRead(0) / 8;
    data2[ndx] = analogRead(1) / 8;
  }
  
  aftertouch(0, 20, data[ndx] / 2);
  aftertouch(0, 21, data2[ndx] / 2);
  
  ndx++;
  if (ndx == 500){
    recording = false;
  }
  ndx = ndx % 500; // loop length
  
  delay(10);
}
