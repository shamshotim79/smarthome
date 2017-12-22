# smarthome
Esp8266 code to control any device to turn it on or off with android app 
and To control any RGB Led or Led Strip.
This code is for Smart Remote app on Google Play 
You can downlod from here :
https://play.google.com/store/apps/details?id=com.basemosama.smarthome

You can configure data sent from the app in your esp8266 code.
data sent from the app like this 255255255FFFFF

every F is standing for a device you have connected to Esp8266 pin .
first F for the first device and the second F for the second device , etc.

when you turn on the first device on the app first F will be N and data sent will be 255255255NFFFF
and if you turned on all devices data sent will be 255255255NNNNN

if you want to add any device just click on plus icon .
when you added a new device a new F will be added to the data to be  255255255FFFFFF

if you want to add RGB LED Controller just press long click on plus icon .

You can choose any color you want by pressing long click on the LED Strip device 

for example if You choose the RED color 
then RED value will be 255 and both Green and blue will be 0 

so data sent ffrom the app will be 255000000FFFFF

first 255 are for RED color value and second 000 are for Green color value and last 000 are for Blue color value of the RGB LED
you can use pwm to generate the colours you want from these numbers .

This app still Beta so email us if you have any problem or you want us to add any thing to the app .
on basemosamaapps@gmail.com
