# KriFram
Opensource framework for esp8266 platform.

KriFram helps you get stated with your IoT projects on ESP8266 chips right away.
Download kriFram.h and include the file on your arduino sketch.

# what are included on kriFram

ajax requests
Ajax requests can be called by mobile or pc apps to perform basic operations
ajax/connect //connects to ap via ajax request
ajax/reboot  //reboots device
ajax/scan  //performs AP scanning
ajax/scanResult //returns scanning results

html pages
Settings //list of setting
reboot  //reboot page
scan //scan and connect to AP
404 not found page
status //system status


Learning to code on KriFram
Only handfull of functions to learn

kriFramSetup() //call on the setup() of your app
kriFramLoop() //call on the loop() of your app

kriFramAddMenu(String "icom emoji", String "human readable name", "url") // adds link to the menu
kriFramAddSettigns(String "url" , String ) // adds link to the settings menu
