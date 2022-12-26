//-------------VirtuinoCM  Library and settings --------------
#include "VirtuinoCM.h"
VirtuinoCM virtuino;               
#define V_memory_count 32          // the size of V memory. You can change it to a number <=255)
float V[V_memory_count];           // This array is synchronized with Virtuino V memory. You can change the type to int, long etc.

boolean debug = true;              // set this variable to false on the finale code to decrease the request time.

void setup() {
  if (debug) {
    Serial.begin(9600);
    while (!Serial) continue; //kontrtrole: Wartet bis die SerialPorts2/3 mit dem Bluetoth Modul verbunden sind 
  }
  espSerial.begin(9600);  
  espSerial.setTimeout(50);

  virtuino.begin(onReceived,onRequested,256);  //Start Virtuino. Set the buffer to 256. With this buffer Virtuino can control about 28 pins (1 command = 9bytes) The T(text) commands with 20 characters need 20+6 bytes        
  //Ein PMW port ist ein Port an dem der Spannung durch schnellen an und aus schalten von 0V (Wert=0) bis 5V(Wert=255) Variert werden kann  
}

void loop() {
  // put your main code here, to run repeatedly:


}




//============================================================== onCommandReceived
//==============================================================
/* This function is called every time Virtuino app sends a request to server to change a Pin value
 * The 'variableType' can be a character like V, T, O  V=Virtual pin  T=Text Pin    O=PWM Pin 
 * The 'variableIndex' is the pin number index of Virtuino app
 * The 'valueAsText' is the value that has sent from the app   */
 void onReceived(char variableType, uint8_t variableIndex, String valueAsText){     
    if (variableType=='V'){
        float value = valueAsText.toFloat();        // convert the value to float. The valueAsText have to be numerical
        if (variableIndex<V_memory_count) V[variableIndex]=value;              // copy the received value to arduino V memory array
    }
}

//==============================================================
/* This function is called every time Virtuino app requests to read a pin value*/
String onRequested(char variableType, uint8_t variableIndex){     
    if (variableType=='V') {
    if (variableIndex<V_memory_count) return  String(V[variableIndex]);   // return the value of the arduino V memory array
  }
  return "";
}

//============================================================== virtuinoRun
  void virtuinoRun(){
    while (espSerial.available()) {
        char tempChar=espSerial.read();
        if (tempChar==CM_START_CHAR) {               // a new command is starting...
              virtuino.readBuffer=CM_START_CHAR;     // copy the new command to the virtuino readBuffer
              virtuino.readBuffer+=espSerial.readStringUntil(CM_END_CHAR);
              virtuino.readBuffer+=CM_END_CHAR;
              if (debug) Serial.println("\nCommand= "+virtuino.readBuffer);
              String* response= virtuino.getResponse();    // get the text that has to be sent to Virtuino as reply. The library will check the inptuBuffer and it will create the response text
              if (debug) Serial.println("Response : "+*response);
              espSerial.print(*response);
              break; 
         }
    }
 }

 //============================================================== vDelay
  void vDelay(int delayInMillis){long t=millis()+delayInMillis;while (millis()<t) virtuinoRun();}
