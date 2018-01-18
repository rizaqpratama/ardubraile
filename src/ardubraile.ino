// https://github.com/rizaqpratama/ardubraile.git

/*
*Ardubraile
*author : rizaqpratama
*
*/

//inisiasi pin awal
int swa = 12;
int swb = 11;
int swc = 10;
int space = 9;
int swd = 8;
int swe = 7;
int swf = 5;
uint8_t buf[8] = { 0 };   /* Keyboard report buffer */
char toSend;
word state=0;
bool isNumber=false;
void setup(){

//led
pinMode(led,OUTPUT);

  //swicth 1
  pinMode(swa,INPUT); 
  digitalWrite(swa,HIGH);

  //swicth 2
  pinMode(swb,INPUT); 
  digitalWrite(swb,HIGH);

  //switch 3
  pinMode(swc,INPUT); 
  digitalWrite(swc,HIGH);

  //switch space
  pinMode(space,INPUT); 
  digitalWrite(space,HIGH);

  //switch 4
  pinMode(swd,INPUT); 
  digitalWrite(swd,HIGH);

  //switch 5
  pinMode(swe,INPUT); 
  digitalWrite(swe,HIGH);

  //switch 6
  pinMode(swf,INPUT); 
  digitalWrite(swf,HIGH);


  Serial.begin(9600);
}

void loop(){
  state=0;
toSend='  ';
  int a = !digitalRead(swa);

  bitWrite(state,0,a);

  int b= !digitalRead(swb);
  bitWrite(state,1,b);

  int c= !digitalRead(swc);
  bitWrite(state,2,c);

  int d= !digitalRead(swd);
  bitWrite(state,3,d);

  int e= !digitalRead(swe);
  bitWrite(state,4,e);

  int f= !digitalRead(swf);
  bitWrite(state,5,f);

  if(!digitalRead(space)){
    state= 64;
  }



  switch(state){
  case 64:

    toSend=' ';
    isNumber=false; 
    break;
    //a
  case 1:
    if(!isNumber){
      toSend='a'; 
    }
    else{
      toSend='1';
    }
    break; 
    //b
  case 3:
    if(!isNumber){
      toSend='b';
    }
    else{
      toSend='2';
    }
    break;

    //c
  case 9:
    if(!isNumber){
      toSend='c';
    }
    else{
      toSend='3';
    }
    break;
    //d
  case 25:
    if(!isNumber){
      toSend='d'; 
    }
    else{
      toSend='4'; 
    }
    break;
  case 17:
    if(!isNumber){
      toSend='e';
    }
    else{
      toSend='5'; 
    }

    break; 

    //f
  case 11:
    if(!isNumber){
      toSend='f';
    }
    else{
      toSend='6';
    }
    break;
  case 27:
    if(!isNumber){
      toSend='g'; 
    }
    else{
      toSend='7'; 
    }
    break;
  case 19:
    if(!isNumber){
      toSend='h'; 
    }
    else{
      toSend='8';  
    }
    break;

  case 10:
    if(!isNumber){
      toSend='i'; 
    }
    else{
      toSend='9'; 
    }
    break;

  case 26:
    if(!isNumber){
      toSend='j';  
    }
    else{
      toSend='0';  
    }
    break;
  case 5:
    toSend='k';
    break;

  case 7:
    toSend='l';
    break;
  case 13:
    toSend='m';
    break;

  case 29:
    toSend='n';
    break;

  case 21:
    toSend='o';
    break;

  case 15:
    toSend='p';
    break;

  case 31:
    toSend='q';
    break;

  case 23:
    toSend='r';
    break;

  case 14:
    toSend='s';
    break;
  case 30:
    toSend='t';
    break;
  case 37:
    toSend='u';
    break;
  case 39:
    toSend='v';
    break;
  case 58:
    toSend='w';
    break;
  case 45:
    toSend='x';
    break;
  case 61:
    toSend='y';
    break;


  case 53:
    toSend='z';
    break;

  case 2:
    toSend=',';
    break;

  case 6:
    toSend=';';
    break;

  case 60:
    isNumber=true;
    break;
  }




  delay(200);

  if ((toSend >= 'a') && (toSend <= 'z')) {
    buf[2] = toSend - 'a' + 4;

  } 
  else if ((toSend >= '0') && (toSend <= '9')) {
    buf[2] = toSend;


  }
  else {
    switch (toSend) {
    case ' ':
      buf[2] = 0x2c;  // Space
      break;
    case '+':
      buf[2] = 128; // Volume up
      break;
    case '-':
      buf[2] = 129; // Volume down
      break;
    default:
      /* Character not handled. To do: add rest of chars from HUT1_11.pdf */
      buf[2] = 0x37;  // Period
      break;
    }
  }
if(a || b || c || d || f || e){
 
  Serial.write(buf, 8); // Send keypress
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key

}
delay(250);
}

