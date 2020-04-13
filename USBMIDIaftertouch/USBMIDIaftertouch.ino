#include "MIDIUSB.h"

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





// from examples
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void aftertouch(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xA0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}


void setup() {
  pinMode(led, OUTPUT); 

}

void loop() {
  // only check the analog inputs 50 times per second,
  // to prevent a flood of MIDI messages
  if (msec >= 20) {
    msec = 0;
    int n0 = analogRead(A0) / 8;
    int n1 = analogRead(A1) / 8;
    int n2 = analogRead(A2) / 8;
    int n3 = analogRead(A3) / 8;
    if (n0 != previousA0) {

      aftertouch(0, controllerA0, n0);
      previousA0 = n0;

      // turn on leds as a sanity check
      digitalWrite(led, HIGH);
    }else{
      digitalWrite(led, LOW);
    }
    if (n1 != previousA1) {
      aftertouch(0, controllerA1, n1);
      previousA1 = n1;
    }
    if (n2 != previousA2) {
      aftertouch(0, controllerA2, n2);
      previousA2 = n2;
    }
    if (n3 != previousA3) {
      aftertouch(0, controllerA3, n3);
      previousA3 = n3;
    }
  }
}
