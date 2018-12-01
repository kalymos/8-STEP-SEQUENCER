//LOOK MUM NO COMPUTER KEYBOARD SEQUENCER. A SIMPLE DESIGN TO MAKE A 4017 STYLE SEQUENCER WITH MORE ADDED FUNCTIONS.
//MORE INFO CHECK LOOKMUMNOCOMPUTER.COM
//PLEASE EMAIL ME COMPUTER@LOOKMUMNOCOMPUTER.COM OR LOOKMUMNOCOMPUTER@GMAIL.COM IF ANY QUESTIONS
//ANY MODIFICATIONS PLEASE LET ME KNOW AND I CAN FEATURE ON THE WEBSITE
//OPEN SOURCE. DONT USE IN A PRODUCT OR WHATEVER WITHOUT TALKING TO ME
//SAM BATTLE 2017
//BOOM



//ALSO TO ADD! I HAVE MADE THIS CODE IN A WAY ITS EASY TO UNDERSTAND FOR A NONE CODER (LIKE MYSELF)
//I REMEMBER WHEN I STARTED ON ARDUINO BEING LIKE WHAT THE HELL IS GOING ON.
//SO IVE LAYED IT OUT LOGICALLY, SEINSE IT ISNT A COMPLICATED PROGRAM I FIGURED WHY THE HECK NOT!

//SO YES THIS ISNT THE BEST WAY OF GOING ABOUT THIS HOWEVER IT IS THE EASIEST TO UNDERSTAND
//FOR A NONE CODER MIND.



#define STEP1 0
#define STEP2 1
#define STEP3 2
#define STEP4 3
#define STEP5 4
#define STEP6 5
#define STEP7 6
#define STEP8 7

#define STEPBUTTON1  8
#define STEPBUTTON2  9
#define STEPBUTTON3  10
#define STEPBUTTON4  11
#define STEPBUTTON5  12
#define STEPBUTTON6  13
#define STEPBUTTON7  14
#define STEPBUTTON8  15


#define FORWARDS 16
#define BACKWADS 17
#define GATE_CLOCK 18
#define RESETZERO 19
#define PWM 20
#define TIME 21





//ABOVE BASICALLY DEFINES THE NAMES OF THE PINS, PLEASE REMEMBER THE ANALOG PINS A0,A1,A2, BLAH BLAH CAN BE USED AS DIGITAL PINS. THE ARE
//DIGITAL 14 and UP!


bool forwards = 0;
bool forwards_old = 0;

bool backwards = 0;
bool backwards_old = 0;

int zero_reset = 0;

int step_button_in = 0;

byte Step = 9;

float time_in = 0;
int time_pwm = 0;
long time_reference = 0;
long time_T = 0;
long time_p = 0;



void setup (){ 

//SET THE PINS TO IN OR OUT

  pinMode (STEP1, OUTPUT);
  pinMode (STEP2, OUTPUT);
  pinMode (STEP3, OUTPUT);
  pinMode (STEP4, OUTPUT);
  pinMode (STEP5, OUTPUT);
  pinMode (STEP6, OUTPUT);
  pinMode (STEP7, OUTPUT);
  pinMode (STEP8, OUTPUT);
  pinMode (FORWARDS, INPUT);
  pinMode (BACKWADS, INPUT);
  pinMode (GATE_CLOCK, OUTPUT);
  pinMode (STEPBUTTON1, INPUT);
  pinMode (STEPBUTTON2, INPUT);
  pinMode (STEPBUTTON3, INPUT);
  pinMode (STEPBUTTON4, INPUT);
  pinMode (STEPBUTTON5, INPUT);
  pinMode (STEPBUTTON6, INPUT);
  pinMode (STEPBUTTON7, INPUT);
  pinMode (STEPBUTTON8, INPUT);
//Serial.begin(9600);
  
}


void loop (){

 Step_B();
 Step_Map();
  
//IT'S GATE_CLOCK

  time_in = analogRead(TIME);
  time_T = time_in * 4  + 50 + time_reference; //THIS IS THE ADJUSTMENT OF THE DURATION OF IMPULSION 

  if(time_T <= millis()){                      //time_in 0->1023    (time_in + 1) * 4 + 200 = 204->4296ms
      digitalWrite(GATE_CLOCK,HIGH);
    time_reference = millis();
  }
  
//PWM FOR THE GATE_CLOCK

  time_pwm = analogRead(PWM);
  time_p = ((time_in / 1000) * time_pwm) * 3.9 + 25 + time_reference;

  if(time_p <= millis()){
    digitalWrite(GATE_CLOCK,LOW);
  }
  
  
 
//THIS IS THE THING THAT MAKES IT GO FORWARDS, IT SAYS +1 YOULL SEE ALL OF THE NUMBERS AND WHAT THEY DO BELOW

  if(step_button_in == LOW){
    
    forwards = digitalRead (FORWARDS);
    if(forwards > forwards_old){
      Step ++; 
      if (Step > 8) {
        Step = 1; } 
    }
    forwards_old = forwards;
  
  //GO BACKWADS
    
    backwards = digitalRead (BACKWADS);
    if(backwards > backwards_old){
      Step -- ; 
      if (Step < 1 ) {
        Step = 8;
       }
    }
    backwards_old = backwards;
  }

//THIS MAKES THE ZERO COMMAND WORK, STEP 9 IS WHEN NO LIGHTS ARE ON. OR REST GO TU STEP 1.



  zero_reset = analogRead (RESETZERO);
 
//  while (zero_reset > 300 && zero_reset <= 600){
//
//    Step = 1;
//    zero_reset = analogRead (RESETZERO);
//    Step_B();
//    Step_Map();
//    
//  }
//
//  while (zero_reset > 600){
//
//    Step = 9;
//    zero_reset = analogRead (RESETZERO);
//    Step_B();
//    Step_Map();
//    
//  }
  

  if(zero_reset > 300){

    if(zero_reset < 900){
     Step = 9;
    }
    else{
      Step = 1;
    }
  }
}
  
void Step_B(){

//BELOW ARE ALL OF THE STEP BUTTONS AND WHAT THEY DO. BASICALLY WHEN THEY ARE HIT THE LED NUMBER GOES TO THE RIGHT NUMBER
  
  step_button_in = digitalRead (STEPBUTTON1);
  if(step_button_in == HIGH){
    //digitalWrite(GATE_CLOCK,HIGH);
    Step = 1;
  }
  
  step_button_in = digitalRead (STEPBUTTON2);
  if(step_button_in == HIGH){
   // digitalWrite(GATE_CLOCK,HIGH);
    Step = 2;
  }
  
  step_button_in = digitalRead (STEPBUTTON3);
  if(step_button_in == HIGH){
   // digitalWrite(GATE_CLOCK,HIGH);
    Step = 3;
  }
  
  step_button_in = digitalRead (STEPBUTTON4);
  if(step_button_in == HIGH){
   // digitalWrite(GATE_CLOCK,HIGH);
    Step = 4;
  }
  
  step_button_in = digitalRead (STEPBUTTON5);
  if(step_button_in == HIGH){
   //digitalWrite(GATE_CLOCK,HIGH);
   Step = 5;
  }
  
  step_button_in = digitalRead (STEPBUTTON6);
  if(step_button_in == HIGH){
    //digitalWrite(GATE_CLOCK,HIGH);
    Step = 6;
  }
  
  step_button_in = analogRead (STEPBUTTON7);
  if(step_button_in == HIGH){
    //digitalWrite(GATE_CLOCK,HIGH);
    Step = 7;
  }
  
  step_button_in = analogRead (STEPBUTTON8);
  if(step_button_in == HIGH){
    //digitalWrite(GATE_CLOCK,HIGH);
    Step = 8;
  }
}

  
 //BELOW ARE ALL OF THE NU<BERS AND WHAT THEY DO!
void Step_Map() {
  if (Step == 1){
    digitalWrite(STEP1, HIGH);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);      
  }
  
  if (Step == 2){
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, HIGH);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
  }
         
  if (Step == 3){
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, HIGH);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
  } 
  
  if (Step == 4){
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, HIGH);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
  } 
  
  if (Step == 5){
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, HIGH);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
  } 
  
  if (Step == 6)
  {
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, HIGH);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
  } 
  
  if (Step == 7){
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, HIGH);
    digitalWrite(STEP8, LOW);
  } 
  
  if (Step == 8){
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, HIGH);
  } 
  
  if (Step == 9){
    digitalWrite(STEP1, LOW);
    digitalWrite(STEP2, LOW);
    digitalWrite(STEP3, LOW);
    digitalWrite(STEP4, LOW);
    digitalWrite(STEP5, LOW);
    digitalWrite(STEP6, LOW);
    digitalWrite(STEP7, LOW);
    digitalWrite(STEP8, LOW);
  } 
}

