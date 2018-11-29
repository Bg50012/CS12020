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
  task_3();
  }

boolean isDeviceOnPort(const char name[], int port){
  //sets the messages Sender and its destination
  SerialShield.setMessageSender("coh24");
  SerialShield.setMessageDestination(name);
  
  //sends the message to the desired port with the message "ping"
  SerialShield.setMessageContent("ping");
  while(SerialShield.sendASSPMessage(port) == false){
    ;
  }
 

  //loop the fetch message 50 times to ensure that it has time to recieve the message
  for(int i = 0; i<50; i++){
    if(SerialShield.fetchASSPMessage()){
      //if the port returns a message return the function as true and then break out of the loop
      return true;
      break; 
    }
    //if it does not return true within 50 attempts return the function as false
  }return false;
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

unsigned long getTimeToDevice(const char name[], int port){
unsigned long timeBeforeMessageSent = millis();
  if(isDeviceOnPort(name, port) == true){
    unsigned long timeAfterMessageRecieved = millis();
    return (timeAfterMessageRecieved - timeBeforeMessageSent);  
  }else{
    return 0;
  }
}


void task_1(){
  for(int i = 0; i<NUMNAMES; i++){
    int deviceResponseTime = getTimeToDevice(names[i], 1);
    if(deviceResponseTime == 0){
      Serial.print(names[i]);
      Serial.print("  ");
      Serial.println("NC");
    }else{
    Serial.print(names[i]);
    Serial.print("  ");
    Serial.println(deviceResponseTime);
    } 
  }
}

int getPortForDevice(const char name[]){
   if(isDeviceOnPort(name, 1) == true){
      return 1;
    }else if(isDeviceOnPort(name, 2) == true){
      return 2;
  }else if(isDeviceOnPort(name, 3) == true){
      return 3;
  }else if (isDeviceOnPort(name, 4) == true){
    return 4;
  }else{
    return 0;
  }
}


void task_2(){
  for(int i =0; i<NUMNAMES; i++){
    int devicePort = getPortForDevice(names[i]);
    if(devicePort == 0){
      Serial.print(names[i]);
      Serial.print("    ");
      Serial.println("NC");
    }else{
    Serial.print(names[i]);
    Serial.print("    ");
    Serial.println(devicePort);
    }
  }
}

void task_3(){
  int portChecks = 0;
  int devicePort[NUMNAMES];
  for(int i =0; i<NUMNAMES; i++){
    if(isDeviceOnPort(names[i], 1)){
      portChecks += 1;
      devicePort[i] = 1;
      Serial.println("PORT 1 COMPLETE");
      continue;
    }else if(isDeviceOnPort(names[i], 2)){
      portChecks += 2;
      devicePort[i] = 2;
      Serial.println("PORT 2 COMPLETE");
      continue;
    }else if(isDeviceOnPort(names[i], 3)){
      portChecks += 3;
      devicePort[i] = 3;
      Serial.println("PORT 3 COMPLETE");
      continue;
    }else if(isDeviceOnPort(names[i], 4)){
      portChecks += 4;
      devicePort[i] = 4;
      Serial.println("PORT 4 COMPLETE");
      continue;
    }else{
      portChecks += 4;
      devicePort[i] = 0;
      Serial.println("NC COMPLETE");
    }
  }
  
  Serial.print("1 ");
  for(int i =0; i<NUMNAMES; i++){
    if(devicePort[i] == 1){
      Serial.print(names[i]);
      Serial.print("  ");
    }
  } Serial.println();
  Serial.print("2 ");
  for(int i =0; i<NUMNAMES; i++){
    if(devicePort[i] == 2){
      Serial.print(names[i]);
      Serial.print("  ");
    }
  }Serial.println();
  Serial.print("3 ");
  for(int i =0; i<NUMNAMES; i++){
    if(devicePort[i] == 3){
      Serial.print(names[i]);
      Serial.print("  ");
    }
  }Serial.println();
  Serial.print("4 ");
  for(int i =0; i<NUMNAMES; i++){
    if(devicePort[i] == 4){
      Serial.print(names[i]);
      Serial.print("  ");
    }
  }Serial.println();
  Serial.print("NC  ");
  for(int i =0; i<NUMNAMES; i++){
    if(devicePort[i] == 0){
      Serial.print(names[i]);
      Serial.print("  ");
    }
  }Serial.println();
  Serial.print("Port Checks:  ");
  Serial.print(portChecks);
  
  
}
  
void loop() // run over and over
{
 
}
