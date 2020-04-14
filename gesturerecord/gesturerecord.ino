unsigned int data[500];//~1kb loop memory
boolean recording = false;
unsigned char index = 0;

// led pin

void setup(){
    pinMode(13, OUTPUT);
    for (int i 0; i < 500; i++){
        data[i] = i  % 255;
    }
}


void loop(){

if (recording){
    data[index] = analogRead(0);
}else{
    analogWrite(13 , data[index]);
}
  delay(10);
}
