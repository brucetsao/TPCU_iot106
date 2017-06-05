#include "Pinset.h"
#include <SoftwareSerial.h>

SoftwareSerial BT(RxPin, TxPin); // RX, TX


void setup() {
  // put your setup code here, to run once:
    initAll() ;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BT.available()>0)
  {
         ReadStr = BT.readStringUntil(EndToken) ;    // read char @
             if (DecodeString(ReadStr,&StHr,&StMin,&StSec,&EdHr,&EdMin,&EdSec) )
               {

                      if (BTCommand == "A")
                        {
                          TurnOnPower() ;
                          PowerStatus = true ;
                        }
                          
                      if (BTCommand == "B")
                        {
                          TurnOffPower() ;
                          PowerStatus = false ;
                        }
                                            
                      if (BTCommand == "C")
                        {
                            SetTime = false ; 
                            StHr = 0 ;
                            StMin = 0 ;
                            StSec = 0 ;
                            EdHr = 0 ;
                            EdMin = 0 ;
                            EdSec = 0 ; 
                        }              
             
                 }
     }
  }

void initAll()
{
      pinMode(RelayPin,OUTPUT) ;
      digitalWrite(RelayPin,TurnOff) ;
      BT.begin(9600) ;
      Serial.begin(9600) ;
      Serial.println("Program Start Here") ;
}
void TurnOnPower()
{
  if (!PowerStatus)
    {
        digitalWrite(RelayPin,TurnOn) ;
    }
}
void TurnOffPower()
{
    if (PowerStatus)
    {
        digitalWrite(RelayPin,TurnOff) ;
    }
   

}

boolean DecodeString(String INPStr, int *H1, int *M1 , int *S1, int *H2, int *M2 , int *S2) 
{
      int i = 0 ;
      int strsize = INPStr.length();
      for(i = 0 ; i <strsize ;i++)
          {
                    DebugMsg(String(i,DEC)) ;
                    DebugMsg(":(") ;
                         DebugMsg(INPStr.substring(i,i+1)) ;
                    DebugMsg(")\n") ;

              if (INPStr.substring(i,i+1) == String(StartToken) )
                  {
                    DebugMsg("find @ at :(") ;
                     DebugMsg(String(i,DEC)) ;
                         DebugMsg("/") ;
                              DebugMsg(String(strsize-i-1,DEC)) ;
                         DebugMsg("/") ;
                              DebugMsg(INPStr.substring(i+1,strsize)) ;
                    DebugMsg(")\n") ;
                      BTCommand = INPStr.substring(i+1,i+2) ;
                        if (BTCommand == "S" )
                            {
                                *H1 = INPStr.substring(i+2,i+4).toInt() ;
                                *M1 = INPStr.substring(i+4,i+6).toInt()  ;
                                *S1 = INPStr.substring(i+6,i+8).toInt()  ;
                                *H2 = INPStr.substring(i+8,i+10).toInt() ;
                                *M2 = INPStr.substring(i+10,i+12).toInt()  ;
                                *S2 = INPStr.substring(i+12,i+14).toInt()  ;
                                 SetTime = true ;
                            }
                            if (BTCommand == "C" )
                            {
                                                            *H1 = INPStr.substring(i+2,i+4).toInt() ;
                                *M1 = 0  ;
                                *S1 = 0 ;
                                *H2 = 0;
                                *M2 = 0 ;
                                *S2 = 0 ;
                                 SetTime = false ; 
                            }
                      return true ;
                  }
          }
    return false ;

}


void DebugMsg(String msg)
{
    if (_Debug != 0)
        {
          Serial.print(msg) ;
        }
   
}
void DebugMsgln(String msg)
{
    if (_Debug != 0)
        {
          Serial.println(msg) ;
        }
   
}
