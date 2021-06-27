

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    pinMode(A0,INPUT); // 빛 센서 핀번호
}


bool flag = 1;


long time;
int threshold = 70;
long getLightTerm(bool mode){
  int light = analogRead(A0); //빛 센서로 받아온 값 저장
  bool isBright = light < threshold ? true : false;

  while(isBright == !mode){
    light = analogRead(A0); //빛 센서로 받아온 값 저장
    isBright = light < threshold ? true : false;
  }
  long brightStartTime = millis();
  while(isBright == mode){
    light = analogRead(A0); //빛 센서로 받아온 값 저장
    isBright = light < threshold ? true : false;
  }
  long brightEndTime = millis();

  return brightEndTime - brightStartTime;
 
}

const bool BRIGHT = false;
const bool DARK = true;

int delay_arr[3] = {10, 20, 30};

int queue[3] = {};
int queue_cnt = 0;

int termToCode(int term){
  int range = 5;

  for(int i = 0; i < 3 ; i ++){
 
    if((delay_arr[i] - range )<= term && (delay_arr[i] + range) >= term){
   
      return i;
    }
  }
  return -1;
  
}


char codeToChar(){

  int code2 = queue[0] * 9 + queue[1] * 3 + queue[2] * 1;
  if(code2 == 0){
    return ' ';
  }else{
    return 'A' + code2 - 1;
  }
  
}

int char_cnt = 0;

void addCodeToQueue(int code){
  queue[queue_cnt] = code;
  queue_cnt++;

  if(queue_cnt == 3){
      char_cnt += 1;
      Serial.print(codeToChar());
      
      memset(queue, 0, sizeof(queue));
      queue_cnt = 0;
    }
}

long timer;


void loop() {
  // put your main code here, to run repeatedly:
  memset(queue, 0, sizeof(queue));
  queue_cnt = 0;
  char_cnt = 0;
  getLightTerm(DARK);
  flag = true;

  timer = millis();
  
  while(1){
    int term = getLightTerm(!flag);

    if(term >= 60){
      if(term >= 70){

        addCodeToQueue(termToCode(term-60));
      }
      Serial.println("");
      Serial.println("END!");
      Serial.print("Time : ");
      Serial.print(millis() - timer);
      Serial.print("ms, Length : ");
      Serial.println(char_cnt);
      return;
    }

    addCodeToQueue(termToCode(term));

    
    

    
    flag = !flag;
  }
 
  
   
   

}
