void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}


bool flag = true;


int delay_arr[3] = {10, 20, 30};



void loop() {
  // put your main code here, to run repeatedly:

   while(!Serial.available()){
   }
  
   while(Serial.available()) { //시리얼 포트에 데이터가 전송되어 있을때 
      char ch;
      ch = Serial.read(); //데이터를 읽어서 ch변수에 저장한다 
      if(ch=='\n'){

        if(flag == false){ //마지막에 켜짐
          delay(60);
          digitalWrite(9, false);
        }else{ //마지막에 꺼짐
          digitalWrite(9, true);
          delay(60);
          digitalWrite(9, false);
        }
        
        flag = true;
         
        Serial.println("");
        Serial.println("END!");
      }else{
        int code = -1;
        if(ch == ' '){
          code = 0;
        }else if('A' <= ch && ch <= 'Z'){
          code = ch - 'A' + 1;
        }else if('a' <= ch && ch <= 'z'){
          code = ch - 'a' + 1;
        }
        Serial.print(ch);
   
        digitalWrite(9, flag);
        delay(delay_arr[code / 9]);
        flag = !flag;

        digitalWrite(9, flag);
        delay(delay_arr[code / 3 % 3]);
        flag = !flag;

        digitalWrite(9, flag);
        delay(delay_arr[code % 3]);
        flag = !flag;
        
        

        
      } 
      

   }

   

}
