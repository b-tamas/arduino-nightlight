#include <Boards.h>
#include <SoftwareSerial.h>// import the serial library

#include <EEPROM.h>;

//LED chain
#include <Adafruit_NeoPixel.h>
#define LEDCHAIN 4
#define LED_COUNT 24
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LEDCHAIN, NEO_GRB + NEO_KHZ800);
#define TOP_DOWN 0
#define DOWN_TOP 1

#define BLACK      0x000000
#define NAVY      0x000080
#define DARKBLUE    0x00008B
#define MEDIUMBLUE    0x0000CD
#define BLUE      0x0000FF
#define DARKGREEN   0x006400
#define GREEN     0x008000
#define TEAL      0x008080
#define DARKCYAN    0x008B8B
#define DEEPSKYBLUE   0x00BFFF
#define DARKTURQUOISE   0x00CED1
#define MEDIUMSPRINGGREEN 0x00FA9A
#define LIME      0x00FF00
#define SPRINGGREEN   0x00FF7F
#define AQUA      0x00FFFF
#define CYAN      0x00FFFF
#define MIDNIGHTBLUE    0x191970
#define DODGERBLUE    0x1E90FF
#define LIGHTSEAGREEN   0x20B2AA
#define FORESTGREEN   0x228B22
#define SEAGREEN    0x2E8B57
#define DARKSLATEGRAY   0x2F4F4F
#define LIMEGREEN   0x32CD32
#define MEDIUMSEAGREEN    0x3CB371
#define TURQUOISE   0x40E0D0
#define ROYALBLUE   0x4169E1
#define STEELBLUE   0x4682B4
#define DARKSLATEBLUE   0x483D8B
#define MEDIUMTURQUOISE   0x48D1CC
#define INDIGO      0x4B0082
#define DARKOLIVEGREEN    0x556B2F
#define CADETBLUE   0x5F9EA0
#define CORNFLOWERBLUE    0x6495ED
#define MEDIUMAQUAMARINE  0x66CDAA
#define DIMGRAY     0x696969
#define SLATEBLUE   0x6A5ACD
#define OLIVEDRAB   0x6B8E23
#define SLATEGRAY   0x708090
#define LIGHTSLATEGRAY    0x778899
#define MEDIUMSLATEBLUE   0x7B68EE
#define LAWNGREEN   0x7CFC00
#define CHARTREUSE    0x7FFF00
#define AQUAMARINE    0x7FFFD4
#define MAROON      0x800000
#define PURPLE      0x800080
#define OLIVE     0x808000
#define GRAY      0x808080
#define SKYBLUE     0x87CEEB
#define LIGHTSKYBLUE    0x87CEFA
#define BLUEVIOLET    0x8A2BE2
#define DARKRED     0x8B0000
#define DARKMAGENTA   0x8B008B
#define SADDLEBROWN   0x8B4513
#define DARKSEAGREEN    0x8FBC8F
#define LIGHTGREEN    0x90EE90
#define MEDIUMPURPLE    0x9370DB
#define DARKVIOLET    0x9400D3
#define PALEGREEN   0x98FB98
#define DARKORCHID    0x9932CC
#define YELLOWGREEN   0x9ACD32
#define SIENNA      0xA0522D
#define BROWN     0xA52A2A
#define DARKGRAY    0xA9A9A9
#define LIGHTBLUE   0xADD8E6
#define GREENYELLOW   0xADFF2F
#define PALETURQUOISE         0xAFEEEE
#define LIGHTSTEELBLUE    0xB0C4DE
#define POWDERBLUE    0xB0E0E6
#define FIREBRICK   0xB22222
#define DARKGOLDENROD   0xB8860B
#define MEDIUMORCHID    0xBA55D3
#define ROSYBROWN   0xBC8F8F
#define DARKKHAKI   0xBDB76B
#define SILVER      0xC0C0C0
#define MEDIUMVIOLETRED         0xC71585
#define INDIANRED     0xCD5C5C
#define PERU      0xCD853F
#define CHOCOLATE   0xD2691E
#define TAN     0xD2B48C
#define LIGHTGRAY   0xD3D3D3
#define THISTLE     0xD8BFD8
#define ORCHID      0xDA70D6
#define GOLDENROD   0xDAA520
#define PALEVIOLETRED   0xDB7093
#define CRIMSON     0xDC143C
#define GAINSBORO   0xDCDCDC
#define PLUM      0xDDA0DD
#define BURLYWOOD   0xDEB887
#define LIGHTCYAN   0xE0FFFF
#define LAVENDER    0xE6E6FA
#define DARKSALMON    0xE9967A
#define VIOLET      0xEE82EE
#define PALEGOLDENROD   0xEEE8AA
#define LIGHTCORAL    0xF08080
#define KHAKI     0xF0E68C
#define ALICEBLUE   0xF0F8FF
#define HONEYDEW    0xF0FFF0
#define AZURE     0xF0FFFF
#define SANDYBROWN    0xF4A460
#define WHEAT     0xF5DEB3
#define BEIGE     0xF5F5DC
#define WHITESMOKE    0xF5F5F5
#define MINTCREAM   0xF5FFFA
#define GHOSTWHITE    0xF8F8FF
#define SALMON      0xFA8072
#define ANTIQUEWHITE    0xFAEBD7
#define LINEN     0xFAF0E6
#define LIGHTGOLDENRODYELLOW  0xFAFAD2
#define OLDLACE     0xFDF5E6
#define RED     0xFF0000
#define FUCHSIA     0xFF00FF
#define MAGENTA     0xFF00FF
#define DEEPPINK    0xFF1493
#define ORANGERED   0xFF4500
#define TOMATO      0xFF6347
#define HOTPINK     0xFF69B4
#define CORAL     0xFF7F50
#define DARKORANGE    0xFF8C00
#define LIGHTSALMON   0xFFA07A
#define ORANGE      0xFFA500
#define LIGHTPINK   0xFFB6C1
#define PINK      0xFFC0CB
#define GOLD      0xFFD700
#define PEACHPUFF   0xFFDAB9
#define NAVAJOWHITE   0xFFDEAD
#define MOCCASIN    0xFFE4B5
#define BISQUE      0xFFE4C4
#define MISTYROSE   0xFFE4E1
#define BLANCHEDALMOND    0xFFEBCD
#define PAPAYAWHIP    0xFFEFD5
#define LAVENDERBLUSH   0xFFF0F5
#define SEASHELL    0xFFF5EE
#define CORNSILK    0xFFF8DC
#define LEMONCHIFFON    0xFFFACD
#define FLORALWHITE   0xFFFAF0
#define SNOW      0xFFFAFA
#define YELLOW      0xFFFF00
#define LIGHTYELLOW   0xFFFFE0
#define IVORY     0xFFFFF0
#define WHITE     0xFFFFFF





//BLUETOOTH
SoftwareSerial BTSerial(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

//BTH bridge
char c = ' ';
boolean NL = true;
String bluetoothrx;


//eeprom block size for logging
int eepromblock=10;  //valid values 5,10,15,20,25,50,100


//**********************pin configuration
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

// night-light specific values
int sensor = 2;
int led = 13;
float brightness = 0;    // how bright the LED is
float fadingValue = 0.5;    // how many points to fade the LED by

int prolongTreshold = 128;
int prolongPreset = 30;
int cycleDelay = 100;
int state1Level = 12;

int brightnessRawValuePrev = 0;
int lampminimum=4;


//******************generic defines
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


void clearLEDs()
{
  for (int i=0; i<LED_COUNT; i++)
  {
    leds.setPixelColor(i, 0);
  }
}






// Cascades a single direction. One time.
void cascade(unsigned long color, byte direction, byte wait)
{
  if (direction == TOP_DOWN)
  {
    for (int i=0; i<LED_COUNT; i++)
    {
      clearLEDs();  // Turn off all LEDs
      leds.setPixelColor(i, color);  // Set just this one
      leds.show();
      delay(wait);
    }
  }
  else
  {
    for (int i=LED_COUNT-1; i>=0; i--)
    {
      clearLEDs();
      leds.setPixelColor(i, color);
      leds.show();
      delay(wait);
    }
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


  //led chain setup
  leds.begin();  // Call this to start up the LED strip.
  clearLEDs();   // This function, defined below, turns all LEDs off...
  leds.show();   // ...but the LEDs don't actually update until you call this.




/*
      for (int i=0; i<LED_COUNT; i++)
      {
        leds.setPixelColor(i, 0x0f0f0f);
      }
    leds.show();
*/


/*
      // Ride the Rainbow Road
  for (int i=0; i<LED_COUNT*10; i++)
  {
    rainbow(i);
    delay(100);  // Delay between rainbow slides
  }
 */



 /*
  // Indigo cylon
  // Do a cylon (larson scanner) cycle 10 times
  for (int i=0; i<10; i++)
  {
    // cylon function: first param is color, second is time (in ms) between cycles
    cylon(INDIGO, 100);  // Indigo cylon eye!
  }
*/



    // A light shower of spring green rain
  // This will run the cascade from top->bottom 20 times
  for (int i=0; i<20; i++)
  {
    // First parameter is the color, second is direction, third is ms between falls
    cascade(MEDIUMSPRINGGREEN, TOP_DOWN, 50); 
  }



  
 
   
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




// Implements a little larson "cylon" sanner.
// This'll run one full cycle, down one way and back the other
void cylon(unsigned long color, byte wait)
{
  // weight determines how much lighter the outer "eye" colors are
  const byte weight = 4;  
  // It'll be easier to decrement each of these colors individually
  // so we'll split them out of the 24-bit color value
  byte red = (color & 0xFF0000) >> 16;
  byte green = (color & 0x00FF00) >> 8;
  byte blue = (color & 0x0000FF);
  
  // Start at closest LED, and move to the outside
  for (int i=0; i<=LED_COUNT-1; i++)
  {
    clearLEDs();
    leds.setPixelColor(i, red, green, blue);  // Set the bright middle eye
    // Now set two eyes to each side to get progressively dimmer
    for (int j=1; j<3; j++)
    {
      if (i-j >= 0)
        leds.setPixelColor(i-j, red/(weight*j), green/(weight*j), blue/(weight*j));
      if (i-j <= LED_COUNT)
        leds.setPixelColor(i+j, red/(weight*j), green/(weight*j), blue/(weight*j));
    }
    leds.show();  // Turn the LEDs on
    delay(wait);  // Delay for visibility
  }
  
  // Now we go back to where we came. Do the same thing.
  for (int i=LED_COUNT-2; i>=1; i--)
  {
    clearLEDs();
    leds.setPixelColor(i, red, green, blue);
    for (int j=1; j<3; j++)
    {
      if (i-j >= 0)
        leds.setPixelColor(i-j, red/(weight*j), green/(weight*j), blue/(weight*j));
      if (i-j <= LED_COUNT)
        leds.setPixelColor(i+j, red/(weight*j), green/(weight*j), blue/(weight*j));
      }
    
    leds.show();
    delay(wait);
  }
}


// Prints a rainbow on the ENTIRE LED strip.
//  The rainbow begins at a specified position. 
void rainbow(byte startPosition) 
{
  // Need to scale our rainbow. We want a variety of colors, even if there
  // are just 10 or so pixels.
  int rainbowScale = 192 / LED_COUNT;
  
  // Next we setup each pixel with the right color
  for (int i=0; i<LED_COUNT; i++)
  {
    // There are 192 total colors we can get out of the rainbowOrder function.
    // It'll return a color between red->orange->green->...->violet for 0-191.
    leds.setPixelColor(i, rainbowOrder((rainbowScale * (i + startPosition)) % 192));
  }
  // Finally, actually turn the LEDs on:
  leds.show();
}

// Input a value 0 to 191 to get a color value.
// The colors are a transition red->yellow->green->aqua->blue->fuchsia->red...
//  Adapted from Wheel function in the Adafruit_NeoPixel library example sketch
uint32_t rainbowOrder(byte position) 
{
  // 6 total zones of color change:
  if (position < 31)  // Red -> Yellow (Red = FF, blue = 0, green goes 00-FF)
  {
    return leds.Color(0xFF, position * 8, 0);
  }
  else if (position < 63)  // Yellow -> Green (Green = FF, blue = 0, red goes FF->00)
  {
    position -= 31;
    return leds.Color(0xFF - position * 8, 0xFF, 0);
  }
  else if (position < 95)  // Green->Aqua (Green = FF, red = 0, blue goes 00->FF)
  {
    position -= 63;
    return leds.Color(0, 0xFF, position * 8);
  }
  else if (position < 127)  // Aqua->Blue (Blue = FF, red = 0, green goes FF->00)
  {
    position -= 95;
    return leds.Color(0, 0xFF - position * 8, 0xFF);
  }
  else if (position < 159)  // Blue->Fuchsia (Blue = FF, green = 0, red goes 00->FF)
  {
    position -= 127;
    return leds.Color(position * 8, 0, 0xFF);
  }
  else  //160 <position< 191   Fuchsia->Red (Red = FF, green = 0, blue goes FF->00)
  {
    position -= 159;
    return leds.Color(0xFF, 0x00, 0xFF - position * 8);
  }
}

int print (String message) {
  //printing to both interface
  Serial.println(message);  
  BTSerial.println(message); 
  }




int log (String message) {
  String S = "";
  S = "Log: " + uptimeseconds;   S = S + " ";    S = S + message;   
  Serial.println(S);

  //not written to eeprom currently
  //eepromwrite(String(uptimeseconds), &eepromptr);
  //eepromwrite("message", &eepromptr); 
}


int logcmd (String message) {
  Serial.print("Cmd: ");
  Serial.print(" ");
  Serial.println (message);
  
  //eepromwrite(String(uptimeseconds), &eepromptr);
  //eepromwrite("message", &eepromptr); 
}

void bluetooth() {

     if (BTSerial.available()){
            char inChar = BTSerial.read(); 
            Serial.print(inChar);
        
            if (inChar == '\n' || inChar == '\r' ) {
                // if the incoming character is a newline, set a flag
                // so the main loop can do something about it:
                stringComplete = true;
                return;
            } 
            
            inputString += inChar;

            /*            
            if(BluetoothData=='1'){   // if number 1 pressed ....
               digitalWrite(ledpin,1);
               BTSerial.println("LED  On D13 ON ! ");
            }
            if (BluetoothData=='0'){// if number 0 pressed ....
                digitalWrite(ledpin,0);
                BTSerial.println("LED  On D13 Off ! ");
            }
            */
    }//if available
}


void loop() {
  int sensorState = digitalRead(sensor);      // read the sense pin:

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


   if (command.equals("ATMODE")) {  //note: it is not possible to escape from this yet!
      print("ATMODE DETECTED");
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

      print(String(analogRead(adcpin0)));     
      print(String(analogRead(adcpin1)));     
      print(String(analogRead(adcpin2)));           
      print(String(analogRead(adcpin3)));     
   
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
  print("*** Verbose logging enabled ***");  
}


int disableVerbosity(int* verb) {
  *verb = 0;
  print("*** Verbose logging disabled ***");  
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
    print(msg);
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



