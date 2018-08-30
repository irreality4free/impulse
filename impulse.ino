int sig = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(sig, OUTPUT);
  digitalWrite(sig, LOW);
  Serial.begin(9600);
  Serial.println("Impulse driver v1.0");
  Serial.println();
  Serial.println("Modes: single, loop");
  Serial.println("Enter command - mode:delayMS:delayUS (max delay uS - 16383)");
  Serial.println();
  Serial.println("Example:");
  Serial.println("single:2000:0");
  Serial.println("loop:2000:0");
  Serial.println("to exit loop enter command - exit");
  Serial.println();
  Serial.println();

}

void loop() {
  if (Serial.available() > 0) {
    String com = Serial.readString();
    int str_l = com.length();
    Serial.println(com);
    int spliter = com.lastIndexOf(':');
    int micro = com.substring(com.lastIndexOf(':') + 1, str_l).toInt();
    com = com.substring(0,com.lastIndexOf(':') );
    String mode = com.substring(0, com.lastIndexOf(':'));
    long len = com.substring(com.lastIndexOf(':') + 1, str_l).toInt();
    Serial.print("mode - ");
    Serial.println(mode);
    Serial.print("length of signal (mS) - ");
    Serial.println(len);
    Serial.print("length of signal (uS) - ");
    Serial.println(micro);
    

    if (mode == "single") {
      digitalWrite(sig, HIGH);
      delay(len);
      delayMicroseconds(micro);
      digitalWrite(sig, LOW);
      Serial.println("done");
    }

    if (mode == "loop") {

      bool cycle = true;
      Serial.println("Enter loop");

      while (cycle) {
        if (Serial.available() > 0) {
          String exit_com = Serial.readString();
          Serial.println(exit_com);
          if (exit_com == "exit\n")cycle = false;
        }

        digitalWrite(sig, HIGH);
        delay(len);
        delayMicroseconds(micro);
        digitalWrite(sig, LOW);
        delay(len);
        delayMicroseconds(micro);
      }
      digitalWrite(sig, LOW);
      Serial.println("Exit loop");
    }
  }
}




