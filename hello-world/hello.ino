#include "kriFram.h"

void setup() {
  // initialize framework.
  kriFramSetup();

  kriFramAddSettings("call","Callibrate");
  server.on ( "/home", handleRoot );
  server.on ( "/", handleRoot );

  server.begin();
}

// the loop function runs over and over again forever
void loop() {
  //loop framework
  kriFramLoop();



}



void handleRoot() {
  String body = "Hello World!";
  server.send ( 200, "text/html", kriFramHeadder + body + kriFramFooter );
  Serial.println ( "root page sent" );
}
