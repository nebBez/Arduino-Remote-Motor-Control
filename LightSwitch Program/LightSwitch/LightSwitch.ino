#include <IRremote.h>

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

const int RECV_PIN = 12;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);
  
  irrecv.enableIRIn();
}


void stepper(int stepAmmount, bool directioN)
{
  int step_count = 0;

  for (int i = 0; i < stepAmmount; i++)
  {
    if (directioN)
    {
       switch(step_count)
       {
        case 0:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          break;
        case 1:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          break;
        case 2:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          break;
        case 3:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count = 0;
          break;
       }
    }
    else
    {
      switch(step_count)
      {
        case 0:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          step_count++;
          break;
        case 1:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          step_count++;
          break;
        case 2:
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count++;
          break;
        case 3:
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          step_count = 0;
          break;
      }
    }
    delay(2);
  }
}

int swtich = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results))
  {
    switch(results.value)
    {
      case 0xFF38C7:
          if (swtich % 2 == 0)
          {
            stepper(1000, true);
            swtich++;
            delay(500);
          }
          else
          {
            stepper(1000, false);
            swtich--;
            delay(500);
          }
          break;
    }
    Serial.println(results.value, HEX);
        
    irrecv.resume();
  }
  
}
