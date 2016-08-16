
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>



const String ApSsid = "kriFram-"+String(ESP.getChipId());
const char *ApPassword = "1234567890";

ESP8266WebServer server ( 80 );
int mdnsStatus = 0;
int wifiStatus;


const String cssFile = "body{ margin:auto; padding:5px; font-size: 22px; max-width: 600px;}a{text-decoration: none;color: inherit}h1{font-size: 22px;}#menu{ border-radius: 10px; height:60px; background: linear-gradient(white, lightgray);font-size:10px; padding-left: 20px; padding-right: 20px;}input {height:28px;font-size:22px;margin:5px;border:solid 2px blue;width:180px;border-radius: 8px;}#menu a { text-decoration: none; text-align: center; width:40px; float:left;}#menu a:last-child{ float:right;}#menu .icon { font-size:30px; color:greenyellow;}ul{ list-style-type: none; padding:0px;}li{ margin-left:auto; height:30px; font-size: 20px; border: solid 2px; border-radius: 5px; padding: 5px; margin:5px; }#levelContainerBorder{margin:auto;margin-top:20px;border:10px solid blue;height:300px;width:200px;border-radius: 30px;z-index:1;}#levelContainer{position:absolute;height:300px;width:200px;background-color: lightblue;z-index:-3;}#level{z-index:-2;width:100%position:absolute;z-index:100;height:90%;background-color: white;border-radius: 20px;border-bottom-left-radius:0px;border-bottom-right-radius:0px;}#text{display:block;position: absolute;font-size:30px;bottom: 150px;right: 70px;}";
const String kriFramHeadder = "<!DOCTYPE html><html lang='en'> <head> <meta name='viewport' content='width=device-width, user-scalable=no'> <meta charset='utf-8'> <title>S2016 Home</title> <link rel='stylesheet' type='text/css' href='style.css' /> </head> <body> <div id='menu'> <a href='home'><span class='icon'>&#x1F3E0;</span> Home</a> <a href='settings'><span class='icon'>&#x1f527;</span> Settings</a> </div>";
const String kriFramFooter = "</body></html>";



String kriFramCustomSetting = "";

void kriFramAddSettings(String link, String displayName) {
  kriFramCustomSetting += "<a href='" + link + "'><li>" + displayName + "</li></a>";
}


void kriFramHandleCss(){
    server.send ( 200, "text/css", cssFile );
  Serial.println ( "css page sent" );
  }

void kriFramHandleStatus() {
  uint8_t APmac[6];
  WiFi.softAPmacAddress(APmac);
  uint8_t staMac[6];
  WiFi.macAddress(staMac);
  String wifistatus;
  if (WiFi.status() == WL_CONNECTED) {
    wifistatus = "Connected to WiFi Network";
  } else if (WiFi.status() == WL_NO_SSID_AVAIL) {
    wifistatus = "SSID are not available";
  } else if (WiFi.status() == WL_CONNECTION_LOST) {
    wifistatus = "Connection Lost";
  } else {
    wifistatus = "Disconnected";
  }
  String temp = "<h1>System Status</h1><table border='1' cellspacing='0'><tr><td colspan='2'><b>AP</b></td></tr><tr><td>Ip Address</td><td>" + WiFi.softAPIP().toString() + "</td></tr><tr><td>MAC Address</td><td>" + String(APmac[5], HEX) + ":" + String(APmac[4], HEX) + ":" + String(APmac[3], HEX) + ":" + String(APmac[2], HEX) + ":" + String(APmac[1], HEX) + ":" + String(APmac[0], HEX) + "</td></tr><tr><td colspan='2'><b>Station</b></td></tr><tr><td>WiFi Status</td><td>" + wifistatus + "</td></tr><tr><td>SSid</td><td>" + WiFi.SSID() + "</td></tr><tr><td>IP Address</td><td>" + WiFi.localIP().toString() + "</td></tr><tr><td>MAC Address</td><td>" + String(staMac[5], HEX) + ":" + String(staMac[4], HEX) + ":" + String(staMac[3], HEX) + ":" + String(staMac[2], HEX) + ":" + String(staMac[1], HEX) + ":" + String(staMac[0], HEX) + "</td></tr><tr><td colspan='2'><b>System</b></td></tr><tr><td>Chip ID</td><td>" + String(ESP.getChipId()) + "</td></tr></table>";
  server.send ( 200, "text/html", kriFramHeadder + temp + kriFramFooter );
  Serial.println ( "status page sent" );


}


void kriFramHandleAjaxConnect() {
  if (server.hasArg("pass") and server.hasArg("ssid")) {
    char ssid[28];
    char pass[50];
    Serial.println("ssid is:" + server.arg("ssid"));
    Serial.println("password is:" + server.arg("pass"));

    server.arg("ssid").toCharArray(ssid, 28);
    server.arg("pass").toCharArray(pass, 50);
    server.send ( 200, "text/html", "good" );
    delay(50000);
    WiFi.begin(ssid, pass);
    delay(20000);
  }
}

void kriFramHandleConnect() {
  String temp = "<h1>Connect to WiFi</h1>" + server.arg("ssid") + "<div id='passwordForm'>Password: <input type='text' id='pass'><br><button onClick='connect()'>Save And Connect</button></div><script>function connect() { var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() { if (xhttp.readyState == 4 && xhttp.status == 200) { document.getElementById('passwordForm').innerHTML =xhttp.responseText; } }; xhttp.open('POST', 'ajax/connect', true); xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded'); xhttp.send('ssid=" + server.arg("ssid") + "&pass='+document.getElementById('pass').value);}window.onload = function(){updateLevel();setInterval(updateLevel,2000);}</script>";
  server.send ( 200, "text/html", kriFramHeadder + temp + kriFramFooter );
  Serial.println ( "connect page sent" );
};

void kriFramHandleSettings() {
  String temp = " <h1>Settings</h1> <ul><a href='status'><li>System Status</li></a> <a href='scan'><li>WiFi Connection</li></a>" + kriFramCustomSetting + "<a href='advSettings'><li>Advance Settings</li></a> </ul>";
  server.send ( 200, "text/html", kriFramHeadder + temp + kriFramFooter );
  Serial.println ( "settigns page sent" );
}

void kriFramHandleScan() {
  String temp = "<h1>WiFi Network Scan</h1>Click the ssid you want to connect to.<br>";
  int n = WiFi.scanNetworks();
  Serial.println("wifi scan completed");
  if (n == 0)
    temp += "No Wifi Networks were found";
  else
  {
    temp += "<ul>";
    for (int i = 0; i < n; ++i)
    {
      temp += "<a href='connect?ssid=" + (WiFi.SSID(i)) + "&enc=" + WiFi.encryptionType(i) + "'><li>" + (WiFi.SSID(i)) + "</li></a>";
      delay(10);
    }
    temp += "</ul>";
  }
  server.send ( 200, "text/html", kriFramHeadder + temp + kriFramFooter );
}



void kriFramHandleNotFound() {
  server.send ( 404, "text/html", kriFramHeadder + "<h2>Web Page not Found</h2>" + kriFramFooter);
}

void kriFramHandleReboot() {
  String temp = " <h1>Reboot</h1> <div id='rebootingMsg'>Click the button below to reboot your device.</div> <button id='reboot' onclick='rebootNow()'>Reboot Now</button> <script>function rebootNow() {var xhttp = new XMLHttpRequest();xhttp.onreadystatechange = function() {if (xhttp.readyState == 4 && xhttp.status == 200) { document.getElementById('reboot').style.display = 'none'; document.getElementById('rebootingMsg').innerHTML = 'Your device is rebooting please wait.';setTimeout(function(){window.location.href='home'},30000); }}; xhttp.open('GET', 'ajax/reboot', true); xhttp.send();}</script>";
  server.send ( 200, "text/html", kriFramHeadder + temp + kriFramFooter );
  Serial.println ( "reboot page sent" );
}

void kriFramHandleAjaxReboot() {
  server.send ( 200, "text/html", "");
  Serial.println ( "reboot ajax page sent" );
  delay(10000);
  ESP.restart();
}



void kriFramSetup () {



char ApSsidChar[50];
ApSsid.toCharArray(ApSsidChar,50);
//const char *ApSsid = "kriFram-" + char(ESP.getChipId());


  
  Serial.begin ( 115200 );
  delay(10);
  WiFi.mode(WIFI_AP_STA);
  delay(10);
  WiFi.softAP(ApSsidChar, ApPassword);
  delay(10);




  server.on ( "/settings", kriFramHandleSettings);
  server.on ( "/reboot", kriFramHandleReboot);
  server.on ( "/scan", kriFramHandleScan);
  server.on ( "/ajax/reboot", kriFramHandleAjaxReboot);
  server.on ( "/ajax/connect", kriFramHandleAjaxConnect);
  server.on ( "/connect", kriFramHandleConnect);
  server.on ( "/status", kriFramHandleStatus );
  server.on ( "/style.css", kriFramHandleCss );
  server.onNotFound ( kriFramHandleNotFound );

  Serial.println ( "" );
  Serial.println ( "HTTP server started on setup()" );
}



void kriFramLoop () {

  if (wifiStatus != WiFi.status()) {
    wifiStatus = WiFi.status();
    Serial.println ( "wifi status change detected to:" + wifiStatus );
    delay(5);
  }

  server.handleClient();

  if ( mdnsStatus == 0 and WiFi.status() == WL_CONNECTED) {
    if ( MDNS.begin ( "kritagya" ) ) {
      delay(10);
      mdnsStatus = 1;
      MDNS.addService("http", "tcp", 80);
      Serial.println ( "MDNS responder started" );
    }
  }
  if ( mdnsStatus == 1 and WiFi.status() != WL_CONNECTED) {
    mdnsStatus = 0;
    Serial.println ( "MDNS responder status changed to zero" );
  }
}

