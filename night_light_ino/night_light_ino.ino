#include <Boards.h>
#include <SoftwareSerial.h>// import the serial library

#include <EEPROM.h>;


SoftwareSerial BTSerial(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

//bluetooth bridge
char c = ' ';
boolean NL = true;

String bluetoothrx;

//eeprom block size
int eepromblock=10;  //valid values 5,10,15,20,25,50,100
int pwmpinA = 9;
int pwmpinB = 13;  //shared with onboard LED


int adcpin0 = A0;
int adcpin1 = A1;
int adcpin2 = A2;
int adcpin3 = A3;


int inpin0 = 3;
int inpin1 = 4;
int inpin2 = 5;


int outpin1=6;
int outpin2=7;




#define input and output ports
  int sensor = 2;
  int led = 13;

float brightness = 0;    // how bright the LED is

#define fading speed
float fadingValue = 0.5;    // how many points to fade the LED by

int prolongTreshold = 128;
int prolongPreset = 30;
int cycleDelay = 100;
int state1Level = 12;

int lampminimum=4;


int prolong = 0;
int state = 0;
int timer = 0;
int triggered =0;
int verbose = 0;
int incomingByte;
int s = 0;
int eepromptr = 0;
byte value;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int brightnessRawValuePrev = 0;
int uptimeseconds;
int cnt;


/*
0: idle, 0 fenyero. ha triggerelodott, 1-esbe lep
1: folyamatosan emeli a fenyerot, majd 2-esbe lep at
2: adott ideig var, ha volt triggerelve akkor a 3-asba lep. ha nem akkor a 4-esbe
3: noveli a fenyerot max-ra. ha elerte, atlep a 2-esbe
4: csokkenti a fenyerot, de ha van triggereles, visszalep a 3-asba
*/


ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  cnt++;
  if (cnt==10) {  
      uptimeseconds+=1;
      cnt = 0;
      }
}






void setup() {

 
  
  BTSerial.begin(9600);
  BTSerial.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
  // end of bluetooth initialization




  
  Serial.begin(9600);
  delay(1000);
  /*while (!Serial) {
   ; 
   } // wait for serial port to connect. Needed for Leonardo only  */
  inputString.reserve(200);

  //generic pins
  pinMode(pwmpinA, OUTPUT);
  pinMode(pwmpinB, OUTPUT);


  
 
   
  // make the sensor pin an input:
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT); 

  log("Starting...");


/*
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 31250;            // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 1024 prescaler 
  TCCR1B |= (1 << CS10);     
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  interrupts();             // enable all interrupts    
*/
}


int print (String message) {
  Serial.println(message);
  BTSerial.println(message);
}



int log (String message) {
  //Serial.println ("logging!!!!");
  String S = "";
  S = "Log: " + uptimeseconds;   S = S + " ";    S = S + message;   
  Serial.println(S);
  
  
  //eepromwrite(String(uptimeseconds), &eepromptr);
  //eepromwrite("message", &eepromptr); 
}


int logcmd (String message) {
  //Serial.println ("logging!!!!");
  //Serial.println ("");
  Serial.print("Cmd: ");
  //Serial.print(uptimeseconds); 
  Serial.print(" ");
  Serial.println (message);
  
  //eepromwrite(String(uptimeseconds), &eepromptr);
  //eepromwrite("message", &eepromptr); 
}

void bluetooth() {
  

 if (BTSerial.available()){

BTSerial.println("bluetooth function");

    ///char inChar = (char)BTSerial.read(); 
    char inChar = BTSerial.read(); 
    Serial.print(inChar);

    if (inChar == '\n' || inChar == '\r' ) {
      stringComplete = true;
      return;
    } 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:











   if(BluetoothData=='1'){   // if number 1 pressed ....
   digitalWrite(ledpin,1);
   BTSerial.println("LED  On D13 ON ! ");
   }
  if (BluetoothData=='0'){// if number 0 pressed ....
  digitalWrite(ledpin,0);
   BTSerial.println("LED  On D13 Off ! ");
  }
}
}


void loop() {
  // read the sense pin:
  int sensorState = digitalRead(sensor);


  bluetooth();


//L   verbose logging
//l   non-verbose logging
//c   clear eeprom
//d   ascii eeprom read raw
//D   ascii eeprom read blocks 
//r   Read eeprom decimal

  if (stringComplete) {
/*      Serial.print(uptimeseconds); 
      Serial.print("  String Complete: ");
      Serial.println(inputString); 
      eepromwrite(inputString, &eepromptr);*/
      logcmd(inputString);

    //https://en.wikipedia.org/wiki/ASCII




  int delimindex=inputString.indexOf(" ");
  Serial.println(delimindex);
  String command = inputString.substring(0, delimindex);
  //dbg(command);
  String arg = inputString.substring(delimindex+1);
  //dbg(arg);


   if (command.equals("ATMODE")) {  
      log("ATMODE DETECTED");

      BTSerial.begin(38400);
      
      while(true) {
 
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (BTSerial.available())
    {
        c = BTSerial.read();
        Serial.write(c);
    }
      
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
        BTSerial.write(c);   
        
        // Echo the user input to the main window. The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
         }
    }
    }







   if (command.equals("out1")) {  
      log("out1 detected");
      Serial.println(arg);
      digitalWrite(outpin1, int(arg.toInt()));     
    }


   if (command.equals("out2")) {  
      log("out2 detected");
      Serial.println(arg);
      digitalWrite(outpin2, int(arg.toInt()));     
    }



   if (command.equals("adc")) {  
      log("adc detected");

      Serial.println(analogRead(adcpin0));     
      Serial.println(analogRead(adcpin1));     
      Serial.println(analogRead(adcpin2));     
      Serial.println(analogRead(adcpin3));     
    }


   if (command.equals("in")) {  
      log("in detected");

      Serial.println(digitalRead(inpin0));     
      Serial.println(digitalRead(inpin1));           
      Serial.println(digitalRead(inpin2));     
    }


   if (command.equals("pwma")) {  
      log("pwma detected");
      Serial.println(int(arg.toInt()));
      analogWrite(pwmpinA, int(arg.toInt()));     
    }

   if (command.equals("pwmb")) {  
      log("pwmb detected");
      Serial.println(int(arg.toInt()));
      analogWrite(pwmpinB, int(arg.toInt()));     
    }

   if (command.equals("r")) {  // r, dump eeprom ascii raw
      log("r char detected, dump eeprom decimal");
      dumpeeprom();     
    }

    if (command.equals("L"))  {   //L, enable verbose logging
      log("L char detected");  
      enableVerbosity(&verbose);
    } 
    
    if (command.equals("l")) {  // l, disable  verbose logging
      log("l char detected");
      disableVerbosity(&verbose);
    }

    if (command.equals("c")) {  // c, clear eeprom
      log("c char detected, clear eeprom");
      eepromclear(&eepromptr);
    }
    if (command.equals("f")) {  // f, fake message
      log("f char detected, fake message written to eeprom");
      eepromwrite("fakemsg", &eepromptr); 
    }

    if (command.equals("d")){  // d, dump eeprom
      log("d char detected, dump eeprom ascii raw");
      dumpeepromasciiraw();
    }

    if (command.equals("D")){  // D, dump eeprom ascii blocks
      log("D char detected, dump eeprom ascii blocks");
      dumpeepromblocks();
    }

  
    // clear the string:
    inputString = "";
    stringComplete = false;
  }




  switch (s) {
  case 0:    //idle status

    if (sensorState == 0) {      
      break;
    }
    else  {
      s = 1;
//      Serial.print(uptimeseconds); Serial.println("0->1");
//     eepromwrite("0->1", &eepromptr); 
      
      log("0->1");
      brightness=lampminimum;
      
      break; 
    }
    break;    

  case 1:   // dim up,, nem figyeli a triggert kozben
    if (brightness < state1Level-fadingValue) {
      brightness +=  fadingValue; // + brightness  ; 
      if (verbose) Serial.println("Dim UP in state 1"); 
    }
    else { 
      s = 2; 
      Serial.print(uptimeseconds); Serial.println("1->2"); 
      eepromwrite("1->2", &eepromptr); 
      break;
    }
    break;          

  case 2:   // brightness folyamatos erteken tartasa, figyeli a triggert
    if (timer == 0 ) {
      timer = 100;
      triggered = 0;
      break;
    }

    if (sensorState == 1) {      
        triggered=1;
        if (verbose) Serial.println("trigger during state 2"); 
   }
                       
   if (verbose) Serial.println("timer :");         
   if (verbose) Serial.println(timer); 

   timer --; 
   if (timer == 0) {
        if (verbose)    Serial.println("timer=0!!!"); 
        if ( triggered == 1) {
          s = 3;
          Serial.print(uptimeseconds); Serial.println("2->3"); 
          eepromwrite("2->3", &eepromptr); 
          break;
        }  
   else { //triggered ==0
        s = 4;
        Serial.print(uptimeseconds); Serial.println("2->4"); 
        eepromwrite("2->4", &eepromptr); 
        break;
       }  
  }
  break;



  case 3:   // movement during the half-bright period
    if (verbose)    Serial.println("movement during the half-bright period"); 
    if (brightness < 255-fadingValue) {
      brightness += fadingValue ; 
      if (verbose)      Serial.println("Dim UP in state 3"); 
      break;
    }
    else { 
      s = 2; 
      Serial.print(uptimeseconds); Serial.println("3->2"); 
      eepromwrite("3->2", &eepromptr); 
      break;
    }
    s = 2;
    break;



  case 4: // no movement during the half-bright period, dim down to idle state
    if (brightness != 0) {      //FIXME, ennel pontosabb szures kell majd!!!!
      brightness -= fadingValue ; 
    }
    else { 
      s = 0; 
      Serial.println("no trigger during state 4 (dim down)");
      Serial.print(uptimeseconds); Serial.println("4->0"); 
      eepromwrite("4->0", &eepromptr); 
    }
    
    if (sensorState == 1) {      
      Serial.println("trigger during state 4 (dim down)");
      Serial.print(uptimeseconds); Serial.println("4->3"); 
      eepromwrite("4->3", &eepromptr); 
      s = 3; 

    }
    break;
  }


  if (verbose) {
    Serial.print("Brightness: ");  
    Serial.println(brightness);
  }

  //  analogWrite(led, brightness); 
  pwm(led, int(brightness)); 
  delay(cycleDelay);        // delay in between reads for stability
}

//*****************************************************************


int pwm(int ledpin, int brightnessRawValue){
  int brightnessTransformedValue;

  if (brightnessRawValue <= 30 ) {
    brightnessTransformedValue = brightnessRawValue/5;
  }
  if (brightnessRawValue > 30 && brightnessRawValue < 50 ) {
    brightnessTransformedValue = (brightnessRawValue-30) / 4 + 6;
  }
  if (brightnessRawValue >= 50 && brightnessRawValue < 100 ) {
    brightnessTransformedValue = (brightnessRawValue -50 ) / 2 + 12;
  }
  if (brightnessRawValue >= 100 && brightnessRawValue < 150 ) {
    brightnessTransformedValue = (brightnessRawValue - 100 ) / 1.3 + 37;
  }
  if (brightnessRawValue >= 150 ) {
    brightnessTransformedValue = brightnessRawValue ;
  }

  if (brightnessRawValue != brightnessRawValuePrev) {
      Serial.print("brightnessRawValue  ");
      Serial.print(brightnessRawValue);
      Serial.print("\t   brightnessTransformedValue  ");
      Serial.println(brightnessTransformedValue);
      analogWrite(led, brightnessTransformedValue); 
  } 
  
  brightnessRawValuePrev = brightnessRawValue;
}



int enableVerbosity(int* verb) {
  *verb = 1;
  Serial.println("*** Verbose logging enabled ***");  
}


int disableVerbosity(int* verb) {
  *verb = 0;
  Serial.println("*** Verbose logging disabled ***");  
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 

    if (inChar == '\n' || inChar == '\r' ) {
      stringComplete = true;
      return;
    } 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
  }
}

void serialEventRun(void) {
  if (Serial.available()) serialEvent();
}




//**********************************************


int dbg (String msg) {
  if (verbose) {
    Serial.println(msg);
  }

}

void eepromclear( int* ptr) {
  for (int i = 0; i < 512; i++)
    EEPROM.write(i, 0);
    *ptr = 0;
}

void eepromwrite(String str, int* ptr) {
  if (*ptr >= 500) {  //fixme
    *ptr = 0;
  }

  for (int i=0; i<(eepromblock-1); i++) {  // a ptr altal mutatott helyre bemasol X elemet.
    EEPROM.write(i+*ptr, int(str[i]));
  }
  //EEPROM.write(eepromblock+*ptr, int(13));
  *ptr += eepromblock;

}

void    dumpeeprom() {
  Serial.println("Content of EEPROM, RAW: ");
  for (int i =0; i<500; i++)  {
    value = EEPROM.read(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
  }
}

void    dumpeepromblocks() {
  Serial.println("Content of EEPROM, ASCII, blocks: ");

  for (int i =0; i<500; i++)  {
    value = EEPROM.read(i);
    Serial.write(value);  
        if ( (i+1) % eepromblock == 0 ) {    // sortordeles
          Serial.println();
       }  //if
  } //for
}  //function

void    dumpeepromasciiraw() {
  Serial.println("Content of EEPROM, ASCII RAW: ");

  for (int i =0; i<500; i++)  {
    value = EEPROM.read(i);
    Serial.write(value);
                     
  } //for
}  //function



