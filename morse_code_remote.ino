#include <IRremote.hpp>
#include <Arduino.h>
#include <Servo.h>

//Initalize servo functions
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to read the value from the analog pin
int rest_position = 45;

//Initalize remote controller functions
#define IR_RECEIVE_PIN 7

//Initalize led functions
#define LED_PIN 13

// Initialize global values
String morse_letter; 

// Function prototypes
void dot();
void dash();

void translate_to_morse(char letter, String &morse_letter);

void morse_led(const String &morse_letter);
void morse_servo(const String &morse_letter);

void servo_down();
void servo_dot();
void servo_dash();

void setup()
{
  
  pinMode(LED_PIN, OUTPUT); 
  
  myservo.attach(9); 
  myservo.write(rest_position); 
  
  Serial.begin(9600); 
  
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.println("Enter a letter via remote : ");
}

void loop() {
  
  if (IrReceiver.decode()) {
     Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
      // USE NEW 3.x FUNCTIONS
      
     //IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
     //IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    char letter; 
    switch(IrReceiver.decodedIRData.decodedRawData){
      
      case 0xBA45FF00: Serial.println("a"); letter = 'a'; break; 
      case 0xB847FF00: Serial.println("b"); letter = 'b'; break; 
      case 0xBB44FF00: Serial.println("c"); letter = 'c';break; 
      case 0xBF40FF00: Serial.println("d"); letter = 'd';break; 
      case 0xBC43FF00: Serial.println("e"); letter = 'e';break ; 
      case 0xF807FF00: Serial.println("f"); letter = 'f';break ; 
      case 0xEA15FF00: Serial.println("g"); letter = 'g';break ; 
      case 0xF609FF00: Serial.println("h"); letter = 'h';break ; 
      case 0xE916FF00: Serial.println("i"); letter = 'i';break ; 
      case 0xE619FF00: Serial.println("j"); letter = 'j';break ; 
      case 0xF20DFF00: Serial.println("k"); letter = 'k';break ; 
      case 0xF30CFF00: Serial.println("l"); letter = 'l';break ; 
      case 0xE718FF00: Serial.println("m"); letter = 'm';break ; 
      case 0xA15EFF00: Serial.println("n"); letter = 'n';break ; 
      case 0xF708FF00: Serial.println("o"); letter = 'o';break ; 
      case 0xE31CFF00: Serial.println("p"); letter = 'p';break ; 
      case 0xA55AFF00: Serial.println("q"); letter = 'q';break ; 
      case 0xBD42FF00: Serial.println("r"); letter = 'r';break ; 
      case 0xAD52FF00: Serial.println("s"); letter = 's';break ; 
      case 0xB54AFF00: Serial.println("t"); letter = 't';break ; }
        
     translate_to_morse(letter, morse_letter); 
     Serial.println(morse_letter);
     morse_led(morse_letter);
     morse_servo(morse_letter);
     
     IrReceiver.resume(); // Enable receiving of the next value
  } 
}

void translate_to_morse(char letter, String &morse_letter){
    switch (letter) {
      case 'a': morse_letter = ".-"; break;
      case 'b': morse_letter = "-..."; break;
      case 'c': morse_letter = "-.-."; break;
      case 'd': morse_letter = "-.."; break;
      case 'e': morse_letter = "."; break;
      case 'f': morse_letter = "..-."; break;
      case 'g': morse_letter = "--."; break;
      case 'h': morse_letter = "...."; break;
      case 'i': morse_letter = ".."; break;
      case 'j': morse_letter = ".---"; break;
      case 'k': morse_letter = "-.-"; break;
      case 'l': morse_letter = ".-.."; break;
      case 'm': morse_letter = "--"; break;
      case 'n': morse_letter = "-."; break;
      case 'o': morse_letter = "---"; break;
      case 'p': morse_letter = ".--."; break;
      case 'q': morse_letter = "--.-"; break;
      case 'r': morse_letter = ".-.";
      case 's': morse_letter = "..."; break;
      case 't': morse_letter = "-"; break;
      case 'u': morse_letter = "..-"; break;
      case 'v': morse_letter = "...-"; break;
      case 'w': morse_letter = ".--"; break;
      case 'x': morse_letter = "-..-"; break;
      case 'y': morse_letter = "-.--"; break;
      case 'z': morse_letter = "--.."; break;
      default: morse_letter = " (not a letter)"; break;
    } 
}

void morse_servo(const String &morse_letter){
    for (int i = 0; i < morse_letter.length(); i++) {
      if (morse_letter[i] == '.') {
        servo_dot();
        servo_down();
        
      } else if (morse_letter[i] == '-') {
        servo_dash();
        servo_down();
      }
  }
}

void servo_down(){
    myservo.write(rest_position);                         
}

void servo_dot(){
    for (pos = 0; pos <= 45; pos += 1) { // goes from 0 to 45 degrees
    myservo.write(pos);             
    delay(5);                      
  }
}

void servo_dash(){
    for (pos = 0; pos <= 45; pos += 1) { // goes from 0 to 45 degrees
    myservo.write(pos);             
    delay(15);                      
  }
}

void morse_led(const String &morse_letter) {
    for (int i = 0; i < morse_letter.length(); i++) {
      if (morse_letter[i] == '.') {
        dot();
        
      } else if (morse_letter[i] == '-') {
        dash();
      }
  }
  delay(750); 
}

void dot() {
  digitalWrite(LED_PIN, HIGH);
  delay(500); // A dot is 1 unit
  digitalWrite(LED_PIN, LOW);
  delay(500); 
}

void dash() {
  digitalWrite(LED_PIN, HIGH);
  delay(1000); // A dash is 3 units
  digitalWrite(LED_PIN, LOW);
  delay(500); 
}
