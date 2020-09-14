void setup(){
    pinMode(3,OUTPUT);
    Serial.begin(9600);
    //Serial.println("Hello");

    String s = "";
    char msg[8] = {0x01,0x04,0x00,0x07,0x00,0x07,0x40,0x08};
    //Serial.println("Send Message");
    digitalWrite(3,1);
    Serial.print(msg);
    delay(1000); 
    digitalWrite(3,0);
    delay(1000); 
    while (Serial.available()) {
        //Serial.println("Serial.available");
        char c = (char) Serial.read();
        if(c!='\n'){
            s += c;
        }
        delay(1); 

    }
}

void loop(){
}
