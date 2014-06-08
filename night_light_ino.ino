#include <EEPROM.h>;




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
  Serial.begin(9600);
  delay(1000);
  /*while (!Serial) {
   ; 
   } // wait for serial port to connect. Needed for Leonardo only  */
  inputString.reserve(200);
  
  // make the sensor pin an input:
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT); 

  log("Starting...");

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
  
}


int log (String message) {
  Serial.println ("logging!!!!");
  Serial.print(uptimeseconds); 
  Serial.println (message);
  
  eepromwrite(String(uptimeseconds), &eepromptr);
  eepromwrite("message", &eepromptr); 
}






void loop() {
  // read the sense pin:
  int sensorState = digitalRead(sensor);

  if (stringComplete) {
/*      Serial.print(uptimeseconds); 
      Serial.print("  String Complete: ");
      Serial.println(inputString); 
      eepromwrite(inputString, &eepromptr);*/
      log("Incoming string: ");
      log(inputString);


    if (int(inputString[0]) == 76) {   //L, enable verbose logging
      log("L char detected");  
      enableVerbosity(&verbose);
    } 
    if (int(inputString[0]) == 108) {  // l, disable  verbose logging
      log("l char detected");
      disableVerbosity(&verbose);
    }

    if (int(inputString[0]) == 99) {  // c, clear eeprom
      log("c char detected, clear eeprom");
      eepromclear();
    }



    if (int(inputString[0]) == 100) {  // d, dump eeprom
      log("d char detected, dump eeprom");
      dumpeeprom();
    }

    if (int(inputString[0]) == 68) {  // D, dump eeprom TXT
      log("D char detected, dump eeprom TXT");
      dumpeepromtxt();
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
    Serial.println("Brightness: ");  
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

void eepromclear() {
  for (int i = 0; i < 512; i++)
    EEPROM.write(i, 0);
}

void eepromwrite(String str, int* ptr) {
  if (*ptr >= 512) {
    *ptr = 0;
  }

  for (int i=0; i<19; i++) {  // a ptr altal mutatott helyre bemasol 20 elemet.
    EEPROM.write(i+*ptr, int(str[i]));
  }

  EEPROM.write(20+*ptr, int(13));

  *ptr += 20;

}

void    dumpeeprom() {
  Serial.println("Content of EEPROM: ");
  for (int i =0; i<512; i++)  {
    value = EEPROM.read(i);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
  }
}

void    dumpeepromtxt() {
  Serial.println("Content of EEPROM /TEXT/: ");

  for (int i =0; i<512; i++)  {
    value = EEPROM.read(i);
    Serial.write(value);

    if ( (i+1) % 20 == 0 ) {    // sortordeles
      Serial.println();
    }
  }
}






