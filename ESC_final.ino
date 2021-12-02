int A1=3;
int A2=5;
int B1=11;
int B2=10;
int C1=9;
int C2=6;


int emfA=A0;
int emfB=A1;
int emfC=A2;

int phase=1;
int deltaA=0;
int emA=0;
int sum=0;

int IN=A3;
int Delay=4000;

int it=0;
int it2=1;
static int delta_= 0;
static int Lastdelta= -1;

unsigned long previousMillis = 0; 

void setup() {
Serial.begin(250000);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(B1,OUTPUT);
  pinMode(B2,OUTPUT);
  pinMode(C1,OUTPUT);
  pinMode(C2,OUTPUT);

  pinMode(enable,OUTPUT);

  pinMode(IN,INPUT);
  pinMode(emfA,INPUT);
  pinMode(emfB,INPUT);
  pinMode(emfC,INPUT);

  
}

void loop() {
      
      
      int emA = analogRead(emfA);
      int emB = analogRead(emfB);
      int emC = analogRead(emfC);
      int sum = (emA+emB+emC)/3;  

      unsigned long currentMillis = micros();
 
  
  if(currentMillis - previousMillis >= Delay){
  
      previousMillis += Delay;
   
  //Phase1 C-B
  switch(phase){
    case 1:
      digitalWrite(A1,LOW);
      digitalWrite(A2,LOW);
      digitalWrite(B1,LOW);
      digitalWrite(C2,LOW);
      digitalWrite(B2,HIGH);
      digitalWrite(C1,HIGH);
      delta = emA-sum;
      
      break;
      

  //Phase2 A-B
    case 2:
      digitalWrite(A2,LOW);
      digitalWrite(B1,LOW);
      digitalWrite(C1,LOW);
      digitalWrite(C2,LOW);
      digitalWrite(A1,HIGH);
      digitalWrite(B2,HIGH);
      delta = emC-sum;
      break;

  //Phase3 A-C
    case 3: 
      digitalWrite(A2,LOW);
      digitalWrite(B1,LOW);
      digitalWrite(B2,LOW);
      digitalWrite(C1,LOW);
      digitalWrite(C2,HIGH);
      digitalWrite(A1,HIGH);
      delta = emB-sum;
    break;   
  
  //Phase4 B-C
  case 4:
      digitalWrite(A1,LOW);
      digitalWrite(A2,LOW);
      digitalWrite(B2,LOW);
      digitalWrite(C1,LOW);
      digitalWrite(B1,HIGH);
      digitalWrite(C2,HIGH);
      delta = emA-sum;
      break;

  //Phase5 B-A 
  case 5:
      digitalWrite(A1,LOW);
      digitalWrite(B2,LOW);
      digitalWrite(C1,LOW);
      digitalWrite(C2,LOW);
      digitalWrite(A2,HIGH);
      digitalWrite(B1,HIGH);
      delta = emC-sum;
      break;

  //Phase6 C-A
  case 6:
      digitalWrite(A1,LOW);
      digitalWrite(B1,LOW);
      digitalWrite(B2,LOW);
      digitalWrite(C2,LOW);
      digitalWrite(C1,HIGH);
      digitalWrite(A2,HIGH);
      delta = emB-sum;
  break;
  }

  if (Lastdelta < 0){
  if (delta > 0)
      {
        Lastdelta=delta; //save the last delta
        fase= fase + 1;
        if (fase > 6) {
          fase = 1;
          }
      }
  }//Zero cross from - to +  

  if (Lastdelta > 0){
  if (delta < 0)
      {
        Lastdelta=delta;
        fase= fase + 1;
        if (fase > 6) {
          fase = 1;
          }
      }
  }//Zero cross from + to - 
   
  }//Case ends

  

  int t =analogRead(IN); //From the potentiometer
  Delay=map(t,0,1024,1,1000); 

  
 
} 
