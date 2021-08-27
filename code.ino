// C++ code
//
String passwd;
#define led 13
#define timeOut 2777
#define sft 1
#define numbersRange 10
#define numbersStart 48
#define numbersEnd 57
#define lettersRange 26 	
#define lowerCaseStart 65
#define lowerCaseEnd 90
#define upperCaseStart 97
#define upperCaseEnd 122

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(timeOut);
}

void loop()
{
  if(passwd.length()!=0){
    //read the password
    Serial.println("Enter your password...");
    String passEnter = Serial.readString();
    if(passEnter==passwd){
      Serial.println("Sucess Login");
      //update the password for the next time
      caesarCipherEncryption(passwd);
      //turn on for 3 seconds
      digitalWrite(led,HIGH);
      delay(3000);
     }else{
      Serial.println("Wrong Password");
      //blink for 3 seconds      
      unsigned long time = millis();
      while(millis()-time < 3000){//not 3000 cuse there some execuation ime
    	digitalWrite(led,!digitalRead(led));
        delay(250);
      }
    }
    digitalWrite(led,LOW);
    
  }else{
    Serial.println("Make: the password");
    passwd = Serial.readString();
    caesarCipherEncryption(passwd);
    Serial.println("Thanks, save it");
  }

}
void caesarCipherEncryption(String &text) {
  int charDec, transfDec, charDecInRange;
  for(int i = 0; i < text.length(); i++) {
    charDec = (int) text[i];//char decimal 
    //numbers range
    if(numbersStart<=charDec && charDec <= numbersEnd){
      charDecInRange = charDec-numbersStart;
      charDecInRange +=sft;
      transfDec = charDecInRange%numbersRange;
      transfDec +=numbersStart ;
    }else if( lowerCaseStart<=charDec && charDec<=lowerCaseEnd){
      charDecInRange = charDec-lowerCaseStart;
      charDecInRange +=sft;
      transfDec = charDecInRange%lettersRange;
      transfDec +=lowerCaseStart ;
    }else if(lowerCaseStart<=charDec && charDec<=upperCaseEnd){
      charDecInRange = charDec-upperCaseStart;
      charDecInRange +=sft;
      transfDec = charDecInRange%lettersRange;
      transfDec +=upperCaseStart ;
    }else{
      //the rest of ascii code
      transfDec = charDec;
    }
    //replacing it 
    text[i] = transfDec;
  }
}