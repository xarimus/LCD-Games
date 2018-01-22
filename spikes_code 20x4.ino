/*     ____   ____  _____  _____
   /  _/  /  _/ / ___/ / ___/
   / /    / /   \__ \  \__ \ 
 _/ / _ _/ / _ ___/ / ___/ / 
/___/(_)___/(_)____(_)____(_)
                             
   ______   ______                          _     
  / ____/  / ____/__  ______________ ______(_)____
 / / __   / /_  / _ \/ ___/ ___/ __ `/ ___/ / ___/
/ /_/ /_ / __/ /  __/ /  / /  / /_/ / /  / (__  ) 
\____/(_)_/    \___/_/  /_/   \__,_/_/  /_/____/  
   ______                __              
  / ____/_______  ____ _/ /_____  ______ 
 / /   / ___/ _ \/ __ `/ __/ __ \/ ___(_)
/ /___/ /  /  __/ /_/ / /_/ /_/ / /  _   
\____/_/   \___/\__,_/\__/\____/_/  (_)  

    ____ _____ ____  _________ __  __
   / __ \__  // __ \/  _/ ___// / / /
  / /_/ //_ </ /_/ // / \__ \/ /_/ / 
 / ____/__/ / _, _// / ___/ / __  /  
/_/   /____/_/ |_/___//____/_/ /_/   

   _____ ____  _ 
  |__  // __ )(_)
   /_ </ __  / / 
 ___/ / /_/ / /  
/____/_____/_/   
                                                               
 */
/*
   _________      .__ __                  
 /   _____/_____ |__|  | __ ____   ______
 \_____  \\____ \|  |  |/ // __ \ /  ___/
 /        \  |_> >  |    <\  ___/ \___ \ 
/_______  /   __/|__|__|_ \\___  >____  >
        \/|__|           \/    \/     \/ 
 */
#include <LiquidCrystal.h>
LiquidCrystal board(12, 11, 5, 4, 3, 2);
const int buttonUp = 7;
const int buttonDown = 9;
int upState = 0;
int downState = 0;
int spyRight = 1;
int spyLeft = 0;
int control;
int fly = 0;
int randomSpikes;
int r;
int l;
int score = 0;
int dead0,dead1,dead2;  
bool dead = false;
byte creeperR [8] = {
  B01000,
  B11110,
  B11011,
  B11110,
  B11111,
  B00100,
  B00100,
  B11011,
};
byte creeperL [8] = {
  B00010,
  B01111,
  B11011,
  B01111,
  B11111,
  B00100,
  B00100,
  B11011,
};
byte spikeR [8] = {
  B00001,
  B00011,
  B00111,
  B01111,
  B11111,
  B00111,
  B00011,
  B00001,
};
byte spikeL [8] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11111,
  B11100,
  B11000,
  B10000,
};
void setup (){
   Serial.begin (9600);
   board.begin (20,4);
   board.createChar (0,creeperR);
   board.createChar (3,creeperL);
   board.createChar (1,spikeR);
   board.createChar (2,spikeL);
   board.setCursor (0,0);
   pinMode (buttonUp,INPUT);
   pinMode (buttonDown,INPUT);
}
void loop (){
  if (spyRight == 1){
    for (int ran=0;ran<=2;ran++){
    randomSpikes = random(0,3);
    board.setCursor (19,randomSpikes);
    board.write (byte(1));
    switch (ran){
      case 0:
      dead0 = randomSpikes;
      continue;
      case 1:
      dead1 = randomSpikes;
      continue;
      case 2:
      dead2 = randomSpikes;
      continue;
    }
  }
    flyRight ();
    board.clear ();
    score++;
  }
  if (spyLeft == 1) {
    for (int ran=0;ran<=2;ran++){ 
    randomSpikes = random(0,3);
    board.setCursor (0,randomSpikes);
    board.write (byte(2));
    switch (ran){
      case 0:
      dead0 = randomSpikes;
      continue;
      case 1:
      dead1 = randomSpikes;
      continue;
      case 2:
      dead2 = randomSpikes;
      continue;
    }
  }
    flyLeft ();
    board.clear ();
    score++;
  }
}
int stateControl (){
  upState = digitalRead(buttonUp);
  downState = digitalRead(buttonDown);
  if (upState == HIGH){
    return 1;
  }
  if (downState == HIGH){
    return 2;
  }
  else
  return 0;
}
void flyRight (){
  for (r=0;r<20;r++){
    if (r==19){
      if (fly==dead0){
        Serial.print ("GAME OVER");
        deadScreen ();
        break;
      }
      if (fly==dead1){
        Serial.print ("GAME OVER");
        deadScreen ();
        break;
      }
      if (fly==dead2){
        Serial.print ("GAME OVER");
        deadScreen ();
        break;
      }
    }
    board.setCursor (r-1,fly);
    board.print (" ");
    control = stateControl ();
    if (control == 1){
      if (fly == 0){
        fly = 1;
      }
      fly --;
    }
    if (control == 2){
      if (fly == 3){
        fly = 2;
      }
      fly ++;
    }
    board.setCursor (r,fly);
    board.write (byte(0));
    delay (150);
    if (r>=19){
      spyRight = 0;
      spyLeft = 1;
    }
  }
}
void flyLeft (){
  for (l=19;l>=0;l--){
    if (l==0){
      if (fly==dead0){
        Serial.print ("GAME OVER");
        deadScreen ();
        break;
      }
      if (fly==dead1){
        Serial.print ("GAME OVER");
        deadScreen ();
        break;
      }
      if (fly==dead2){
        Serial.print ("GAME OVER");
        deadScreen ();
        break;
      }
    }
    board.setCursor ((l+1),fly);
    board.print (" ");
    control = stateControl ();
    if (control == 1){
      if (fly == 0){
        fly = 1;
      }
      fly --;
    }
    if (control == 2){
      if (fly == 3){
        fly = 2;
      }
      fly ++;
    }
    board.setCursor (l,fly);
    board.write (byte(3));
    delay (150);
    if (l==0){
      spyRight = 1;
      spyLeft = 0;
    }
  }
}
void deadScreen (void){
  while (control == 0){
    board.clear ();
    board.setCursor (5,1);
    board.print ("GAME OVER!");
    board.setCursor (5,2);
    board.print ("Punteggio:");
    board.print (score);
    board.setCursor (0,0);
    board.print ("Premere un tasto");
    board.setCursor (0,3);
    board.print ("per riprovare!");
    control = stateControl ();
    delay (100);
  }
  spyRight = 1;
  spyLeft = 0;
  score = 0;
  dead0,dead1,dead2 = 0;
  dead = true;  
}

