#include <ESP8266WiFi.h>
const char* ssid = "Besoo";
//const char* password = "Beso6694967";
const char* password = "beso1212";
int currentstate[]={0,0,0,0,0};
int myPins[]={5,4,0,2,14,12,13,15};
int ledstrip1;
char ledstrip[]="123456789";
char data[]="123456789FFFFF";
int R,G,B=0;
WiFiServer server(80);
void setup() {
for(int i=0;i<8;i++){
 pinMode(myPins[i],OUTPUT);
  digitalWrite(myPins[i],0);
 }
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop() {
WiFiClient client = server.available();
 
  

  if(client){
String text=client.readStringUntil('\n');
Serial.println(text);
text.remove(0,5);
text.remove(14,text.length());

if(text!="favic"){
strncpy( data, text.c_str(),14);
strncpy ( ledstrip, data, 9 );

Serial.println(data);
ledstrip1=atoi(ledstrip);
R=ledstrip1/1000000;
G=(ledstrip1/1000)%1000;
B=ledstrip1%1000;
R=map(R,0,255,0,1023);
G=map(G,0,255,0,1023);
B=map(B,0,255,0,1023);
analogWrite(myPins[5],R);
analogWrite(myPins[6],G);
analogWrite(myPins[7],B);
Serial.print("R : ");
Serial.print(R);
Serial.print(" G : ");
Serial.print(G);
Serial.print(" B : ");
Serial.println(B);


for (int i=0;i<5;i++) {
        if (data[i+9]=='F'){
digitalWrite(myPins[i],0);
     }
   else if(data[i+9]=='N'){
  digitalWrite(myPins[i],1);
         }
   currentstate[i]=digitalRead(myPins[i]);
   
       }


if(data[0]=='D'){
  
   client.print("<title>");
for(int i=0;i<5;i++){
  if(currentstate[i]==1){
client.print("N");}
else if(currentstate[i]==0){
client.print("F");
}
}
client.println("</title>");
}
}
client.flush();  
}
}
