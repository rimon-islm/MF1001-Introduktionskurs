/* MF1001
* Elise Bengtsson, Lukas Dahle, Rimon Islam, Jonna Pettersson, Arvid Viklund
* Hysch
* Ett redskap för att begränsa ljudnivåer
*/
#include "thingProperties.h" // includes the other auto generated file to this
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  //Serial.println("Grove - Sound Sensor Test...");
  pinMode(7, OUTPUT); // Set buzzer - pin 7 as an output
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  // Defined in thingProperties.h
  initProperties();
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
 
 /*
 The following function allows you to obtain more information
 related to the state of network and IoT Cloud connection and errors
 the higher number the more granular information you’ll get.
 The default is 0 (only errors).
 Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}
const int pinAdc = A0; // The pin for the soundsensor
int test;

void loop() { // loops the code
 ljud = 0; // the variable ljud is updated to be 0 every loop
 long sum = 0; // the sum is also updated to be 0
 for (int i = 0; i < 32; i++) // loops i 32 times and add together the results into sum
 {
  sum += analogRead(pinAdc); // the sum is the noise level
  delay(10); // delays for 1 hundred of a second
 }

 if (sum > 900) // if the sum is bigger then 900, this runs
 { 
  digitalWrite(7, HIGH); // sends a signal to the speaker
  delay(1000); // Waits for 1 sec
 }
 
 else // If the if statement did not run, then this else statment vill run
 {
  digitalWrite(7, LOW); // The speaker gives no sound
  delay(1000); // Waits for one second
 }
 
 sum >>= 5; // if the sound is bigger than 5
 Serial.println(sum); // Prints the value of sum
 ljud = sum;
 ArduinoCloud.update(); // The method updates the value of the varibel ljud on the cloud
 delay(10); // wait for a hundred of a second
}
/*
 Since Ljud is READ_WRITE variable, onLjudChange() is
 executed every time a new value is received from IoT Cloud.
*/
void onLjudChange() {
 // Add your code here to act upon Ljud change
}