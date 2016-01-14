config ()
pinsetup()
btsetup()




loop {

  bluetooth()
  serial()

  handleincomingstring()

  sm()


}


##functions


        int handleincomingstring() {
          if stringcomplete {
            split the arguments based on delimiter
              if atmode {
              /*bridging between the bluetooth module and serial port*/
              /*this requires the module to be set into AT mode also*/
              /*it can be done using the button pressing on the module or the*/
              /*logical value of the control pin also*/
            } /*endif atmode*/
            if out1{
            }
            if out2{
            }
            if adc{
            }
            if in{
            }
            if pwma{
            }
            if pwmb{
            }
            if r{
              /*dum eeprom ascii raw     #FIXME*/
            } 
            if L{ 
              /*enable verbosity*/
            } 
            if l{
              /* disable verbosity*/
            } 
            if c{
              /*clear eeprom*/
            } 
            if d() # dump eeprom ascii raw # FIXME
            if D{
              /* dump eeprom ascii blocks*/
            } 
          }  /*endif stringcomplete*/

        } /* end function*/



sm (int forcestate=9) {  /*state machine*/
if forcestate!=9 {
  s=forcestate;
  /*the s state can be overriden by the optional parameter
}


  /* switch (s)
   0: idle, no action, no light, check trigger
   1: dim up to a medium value
   2. medium light, check new      trigger
   3. medium to maximum light
   4. medium to dark, check new trigger   
   8. no light, no action, no trigger
   */
}







