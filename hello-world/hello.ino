//include the framework
#include "kriFram-0.h"

void setup() {
  // initialize framework.
  kritagyaSetup();

  
//home page is not declared by framework app should make it
server.on ( "/home", handleRoot );
server.on ( "/", handleRoot );

//add custom link on settings page
addCustomSetting("call","Callibrate");
//map custom setting page to function
server.on("/call", handleCall );


//start webServer
server.begin();

}

// the loop function runs over and over again forever
void loop() {
  //loop framework
  kritagyaLoop();
}



void handleRoot() {
  String temp = "Hello World!";
  server.send ( 200, "text/html", headder + temp + footer );
  Serial.println ( "root page sent" );
}

void handleCall(){
  String temp = "Hello World!";
  server.send ( 200, "text/html", headder + temp + footer );
  Serial.println ( "callibration page sent" );
}
