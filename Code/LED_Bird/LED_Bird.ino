#include <EEPROM.h>

int i;
char data;
char res[100];

int R;
int G;
int B;

int lastR=0;
int lastG=0;
int lastB=0;

int addR=0;
int addG=1;
int addB=2;

void setup() 
{
pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);

pinMode(12,INPUT);


digitalWrite(9,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);

Serial.begin(9600);
Serial.flush();

if(digitalRead(12)==LOW)
{
    analogWrite(11,EEPROM.read(addR));
    analogWrite(10,EEPROM.read(addG));
    analogWrite(9,EEPROM.read(addB));
}

}

void loop()
{


  while(digitalRead(12)==HIGH)
  {
 int sensorValue=analogRead(A0);

 //Serial.println(sensorValue);
 
  if(sensorValue <= 30)
  {
    analogWrite(11,sensorValue+200);
    analogWrite(10,0);
    analogWrite(9,0);
  }
  else if( (sensorValue > 30) && ( sensorValue <= 60) )
  {
    analogWrite(11,0);
    analogWrite(10,sensorValue+200);
    analogWrite(9,0);
  }
  else if(sensorValue > 60)
  {
    analogWrite(11,0);
    analogWrite(10,0);
    analogWrite(9,sensorValue+200);
  }
  }
  while(!Serial.available() && digitalRead(12)==LOW)
  {
    analogWrite(11,EEPROM.read(addR));
    analogWrite(10,EEPROM.read(addG));
    analogWrite(9,EEPROM.read(addB));
  }
  
    i=0;  
      while(Serial.available())
      {
  while( data!=')')   
        {
          while(Serial.available())
          {
          data=Serial.read();
           res[i]=data;
            i++;
        }
        }
      }
        data=0;
    String r(res);
    String red=r.substring(0,r.indexOf('.'));
    String r2=r.substring(r.indexOf('.')+1, r.indexOf(')'));
    
    String green=r2.substring(0,r2.indexOf('.'));
    String r3=r2.substring(r2.indexOf('.')+1, r2.indexOf(')'));

    String blue=r3.substring(0,r3.indexOf('.'));

    //String color=red + "," + green + "," + blue;
    
    if(red!= NULL && green !=NULL && blue!=NULL)
    {
    R=red.toInt();
    G=green.toInt();
    B=blue.toInt();
   
EEPROM.write(addR, R);
EEPROM.write(addG, G);
EEPROM.write(addB, B);
    }
    analogWrite(11,EEPROM.read(addR));
    analogWrite(10,EEPROM.read(addG));
    analogWrite(9,EEPROM.read(addB));

}
