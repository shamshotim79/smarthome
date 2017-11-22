#include <ESP8266WiFi.h>
const char* ssid = "Your WiFi Network Name";
const char* password = "Your WiFi Passward";
int currentstate[]={0,0,0,0,0};
int myPins[]={5,4,0,2,14,12,13,15};
char ledstrip[]="123456789";
char data[]="123456789FFFFF";
int R,G,B,RGB=0;
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
//Getting data from the app and converting it to char arry 
String text=client.readStringUntil('\n');
text.remove(0,5);
text.remove(15,text.length());
if(text!="favic"){
strncpy( data, text.c_str(),15);
/*data will be like 123456789FFFFF
123 are RED value, 456 Green value ,789 Blue value and
each F is a turned off device when the device is on F will be N */
Serial.println(data);

/*Getting Red , Green and Blue color values for led and converting it to be in the range from 0:1023 
1023 is the max pwm value 
and change the state of the led strip pins with the pwm values.
*/
strncpy ( ledstrip, data, 9 );
RGB=atoi(ledstrip);
R=RGB/1000000;
G=(RGB/1000)%1000;
B=RGB%1000;

R=map(R,0,255,0,1023);
G=map(G,0,255,0,1023);
B=map(B,0,255,0,1023);

analogWrite(myPins[5],R);
analogWrite(myPins[6],G);
analogWrite(myPins[7],B);

//Change state of the pins
for (int i=0;i<5;i++) {
        if (data[i+9]=='F'){
digitalWrite(myPins[i],0);
     }
   else if(data[i+9]=='N'){
  digitalWrite(myPins[i],1);
         }
   currentstate[i]=digitalRead(myPins[i]);
   
       }

/*------------Sending Data to the APP--------------*/
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
