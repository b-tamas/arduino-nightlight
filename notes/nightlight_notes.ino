config {
}




loop{
  bluetooth()  #as bluetooth is not event based yet
 
    if stringcomplete {
     split the arguments based on delimiter
       if atmode {
         bridging between the bluetooth module and serial port
         this requires the module to be set into AT mode also
         it can be done using the button pressing on the module or the
         logical value of the control pin also
       }
      if out1{}
      if out2{}
      if adc{}
      if in{}
      if pwma{}
      if pwmb{}
      if r{} #dum eeprom ascii raw     #FIXME
      if L{} #enable verbosity
      if l{} # disable verbosity
      if c{} # clear eeprom
      if d() # dump eeprom ascii raw # FIXME
      if D{} # dump eeprom ascii blocks
        
  }
 
 
 switch (s)
   0: idle, no action, no light, check trigger
   1: dim up to a medium value
   2. medium light, check new      trigger
   3. medium to maximum light
   4. medium to dark, check new trigger   
}

int pwm(int ledpin, int raw) {
  maipulate raw value to match light feeling and write into analog (pwm)

int dbg (string)
  if verbose
  simply print a message

int print (string)
  send to serial and BT also
  returns nothing
  
int log (string)
  can write to eeprom with uptime-stamp
  needs re-work
  returns nothing
 
void serialEvent()
  build inputString
  set stringComplete when newline arrived
  
void bluetooth ()
{
  build inputString
  set stringComplete when newline arrived
} 
