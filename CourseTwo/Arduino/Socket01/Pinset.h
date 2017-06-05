
#include <String.h>
#define _Debug 1

#define RxPin 11
#define TxPin 12
#define RelayPin 8
#define TurnOn HIGH
#define TurnOff LOW

//------------
String BTCommand = "" ;
boolean PowerStatus = false ;
String ReadStr = "      " ;
char  StartToken = 0x40 ;
char  EndToken = 0x23 ;
boolean SetTime = false ;
int StHr=0, StMin= 0 , StSec=0 ;
int EdHr=0, EdMin= 0 , EdSec=0 ;

