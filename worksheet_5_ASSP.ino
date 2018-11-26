/*
 * Definitions for the  LEDS, switches and potentiometer on the 
 * software serial Sheild
 *
 * author: nns
 * created 15 Oct 2014
 * modified 07 Nov 2017
 */

// hardware port definitions
#define LED_RED 3
#define LED_YELLOW 5
#define LED_PINK 6
#define LED_WHITE 9
#define LED_GREEN 10
#define LED_BLUE 11

#define EMU A1

#define SWITCH1 A4
#define SWITCH2 A5

#define POTENTIOMETER A0

#include "SSBasicUtilities.h"
#include "ASSP.h"

#define PORT 6

#define NUMNAMES 29
const char* names[NUMNAMES] = {
  "Art",    "Hal",    "Mel",    "Vic",
  "Bob",    "Ivy",    "Ned",    "Wes",
  "Bee",    "Jan",    "Nia",    "Xao",
  "Bev",    "Jem",    "Obe",    "Yao",
  "Coy",    "Del",    "Eva",    "Fey",
  "Jen",    "Ken",    "Leo",    "Lee",
  "Pam",    "Ron",    "Sam",    "Tom",
  "Zoe"
};


int led_list[6] = {LED_PINK, LED_WHITE, LED_GREEN, LED_BLUE, LED_RED, LED_YELLOW};
/**
 * configuration
 */
void setup()  
{
  // initialize the digital pins as an output.
  pinMode(LED_RED, OUTPUT); 
  pinMode(LED_YELLOW, OUTPUT); 
  pinMode(LED_PINK, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);   

  // Open hardware serial communications and wait for port to open:
  Serial.begin(57600);
  Serial.println("Software serial LED test program");

  // now setup the switches
  pinMode(SWITCH1, INPUT_PULLUP); 
  pinMode(SWITCH2, INPUT_PULLUP); 

  // now setup the POTENTIOMETER
  pinMode(POTENTIOMETER, INPUT); 

  
  SerialShield.setEmuMode(6);
  //SerialShield.showASSPmessages = true;
  task_1();
  }

boolean isDeviceOnPort(const char name[], int port){
  SerialShield.setMessageSender("coh24");
  SerialShield.setMessageDestination(name);

  SerialShield.setMessageContent("ping");
  SerialShield.sendASSPMessage(port);

  for(int i = 0; i<50; i++){
    if(SerialShield.fetchASSPMessage()){
      return true;
      break; 
    }
  }return false;
}

unsigned long getTimeToDevice(const char name[], int port){
unsigned long timeBeforeMessageSent = millis();
  if(isDeviceOnPort(name, port) == true){
    unsigned long timeAfterMessageRecieved = millis();
    return (timeAfterMessageRecieved - timeBeforeMessageSent);  
  }else{
    return 0;
  }
}

void task_0(){
  Serial.print("Device");
  Serial.println("  Port 1?");
  for(int i = 0; i<10; i++){
    if(isDeviceOnPort(names[i], 1) == true){
      Serial.print(names[i]);
      Serial.println("     Y");
    }else{Serial.print(names[i]);
     Serial.println("     N");
    }
  }
}

void task_1(){
  for(int i = 0; i<10; i++){
    Serial.print(names[i]);
    Serial.print("  ");
    Serial.println(getTimeToDevice(names[i], 1));
  }
}
void loop() // run over and over
{
 
}
