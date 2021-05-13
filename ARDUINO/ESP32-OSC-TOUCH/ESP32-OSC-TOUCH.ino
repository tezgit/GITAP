#include "WiFi.h"
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include "NETWORK.h"


////////////////////////
/// READ OSC MESSAGES ///
void osc_message_pump() {  
  OSCMessage in;
  int size;
  if( (size = Udp.parsePacket()) > 0)
  {
    Serial.println("processing OSC package");
    // parse incoming OSC message
    while(size--) {
      in.fill( Udp.read() );
    }
    if(!in.hasError()) {
      in.route("/touch", on_touch);  

    }
     Serial.println("OSC MESSAGE RECEIVED");    
  } // if 
}


///////////////////////////////
// not used!  only for receive with esp32
void on_touch(OSCMessage &msg, int addrOffset) {
    float var;
    int vv;
    
    if(msg.isFloat(0)){
        vv = int(msg.getFloat(0));
      }else if(msg.isInt(0)){
        vv = msg.getInt(0);
      } 

}


/////////////////////////////
void sendTouchOSC(int touchnum, int touchvalue){

  OSCMessage msg("/touch/");
  msg.add(touchnum);
  msg.add(touchvalue);
    
  Udp.beginPacket(dest, rxport);
    msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message

}



/////////////////////////
void  readTouchSensors() {
  int touch_1 = touchRead(T0);  
  int touch_2 = touchRead(T1);  
  int touch_3 = touchRead(T2);  
  int touch_4 = touchRead(T3);  
  int touch_5 = touchRead(T4);  
  int touch_6 = touchRead(T5);  
  int touch_7 = touchRead(T6);  
  int touch_8 = touchRead(T7);  

  sendTouchOSC(1, touch_1);
  sendTouchOSC(2, touch_2);
  sendTouchOSC(3, touch_3);
  sendTouchOSC(4, touch_4);
  sendTouchOSC(5, touch_5);
  sendTouchOSC(6, touch_6);
  sendTouchOSC(7, touch_7);
  sendTouchOSC(8, touch_8);
    
}


/////////////////////////
void setup() {
  Serial.begin(115200);
 // WiFiConnect(); // connect to Wifi
  APConnect(); // create Access Point
  Udp.begin(rxport); // start UDP socket
 
}


/////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  
  readTouchSensors();
  delay(10);
  

}
