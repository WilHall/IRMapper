#include <SPI.h>
#include <IRremote.h>

String input = "";
boolean gotLine = false;
int buttonCount = 0;
int buttonIndex = 0;
long value = -1;

//IR Receiver Setup
int RECV_PIN = 32;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  
  //Start IR Receiver
  irrecv.enableIRIn();
}

void loop()
{
  if(gotLine) {
    clearInput();
    //Get # of buttons
    Serial.println("Enter the number of buttons to record:");
    while(!readSerial()) {}
    
    char temp[input.length()+1];
    input.toCharArray(temp, input.length()+1);
    buttonCount = atoi(temp);
    clearInput();
    
    //Create parallel arrays for button values and names
    String buttonNames[buttonCount];
    long buttonValues[buttonCount];
    
    //Loop and get buttons until we're full
    while(buttonIndex < buttonCount) {
      
      if(value != 0) {
        Serial.println("");
        Serial.println("Press a button:");
      }
      
      //Wait for IR signal
      value = getIRSignal();
      if(value == 0 || value == 0xFFFFFFFF) { value = 0; continue; }
      
      //Add the signal
      buttonValues[buttonIndex] = value;
      
      //Ask for a name for the value
      Serial.println("");
      Serial.print("Received value: ");
      Serial.print(value, HEX);
      Serial.print(" - Enter a name:");
      Serial.println("");
      while(!readSerial()) {}
      
      //Add the name
      buttonNames[buttonIndex] = input;
      clearInput();
      
      buttonIndex++;
    }
    
    //Print out the arrays
    printButtons(buttonNames, buttonValues);
    
  } else {
    readSerial();
  }
}

void clearInput() {
  gotLine = false;
  input = "";
}

boolean readSerial() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    input += c;
    if (c == '\n') {
      gotLine = true;
      break;
    } 
  }
  return gotLine;
}

long getIRSignal() {
  if (irrecv.decode(&results)) {
    long v = results.value;
    irrecv.resume();
    return v;
  } else {
    return 0;
  }
}

void printButtons(String buttonNames[], long buttonValues[]) {
  Serial.println("");
  Serial.println("Recorded Buttons:");
  Serial.println("");
  Serial.print("String buttonNames[");
  Serial.print(buttonCount);
  Serial.print("] = {");
  
  String name;
  for(buttonIndex=0; buttonIndex < buttonCount; ++buttonIndex) {
    if(buttonIndex > 0) {
      Serial.print(", ");
    }
    Serial.print("\"");
    name = buttonNames[buttonIndex];
    for(int i=0; i<name.length()-1; ++i) {
      Serial.print(name.charAt(i));
    }
    Serial.print("\"");
  }
  
  Serial.print("};");
  Serial.println("");
  Serial.println("");
  Serial.print("String buttonValues[");
  Serial.print(buttonCount);
  Serial.print("] = {");
  
  for(buttonIndex=0; buttonIndex < buttonCount; ++buttonIndex) {
    if(buttonIndex > 0) {
      Serial.print(", ");
    }
    Serial.print("0x");
    Serial.print(buttonValues[buttonIndex], HEX);
  }
  
  Serial.print("};");
  Serial.println("");
  Serial.println("");
}

