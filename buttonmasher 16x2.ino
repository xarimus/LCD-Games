#include <LiquidCrystal.h>

// Controls the game button inputs
const int btn1 = 10;
const int btn2 = 11;
const int btn3 = 12;
const int btn4 = 13;
// variable for reading the pushbutton status
int bs1 = 0;
int bs2 = 0;
int bs3 = 0;
int bs4 = 0;

// Sound
const int buzz = 3;

// Values to detect combination
int combo[] = {0, 0, 0, 0};
int input[] = {0, 0, 0, 0};
int index = 0;//which index of 'input'

// Controls LCD Values
const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Game Variables
int score = 0;
float timer = 60.0;
bool isGame = true;



void setup() 
{   
  isGame = true;
  
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);

  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Let's make it more random
  // Uses an empty analog pin to get a floating number
  randomSeed(analogRead(A0));
  // Generate a random 4-digit sequence
  MakeCombo();
}



void loop() 
{
  if(isGame) 
  {
      // Prints at the beginning of the screen
      ClearScreen();
      PrintInfo();
    
      // Read the input values from the buttons
      bs1 = digitalRead(btn1);
      bs2 = digitalRead(btn2);
      bs3 = digitalRead(btn3);
      bs4 = digitalRead(btn4);
    
      if(index >= 4)
        ResetInput();
    
      // Check if the buttons states are HIGH and print the output on the display
      if(bs1 == HIGH) {
        tone(buzz, 3000);
        input[index++] = 1;
        delay(100); // feel free to adjust this for button length
        
      } else if(bs2 == HIGH) {
        input[index++] = 2;
        tone(buzz, 3000);
        delay(100); // feel free to adjust this for button length
        
      } else if(bs3 == HIGH) {
        input[index++] = 3;
        tone(buzz, 3000);
        delay(100); // feel free to adjust this for button length
        
      } else if(bs4 == HIGH) {
        input[index++] = 4;
        tone(buzz, 3000);
        delay(100); // feel free to adjust this for button length
        
      } else
        noTone(buzz);
    
        // Check if the combo was a match
        if(CheckCombo())
        {
            score++;
            MakeCombo();
            ResetInput();
        
            //tone(buzz, 5000, 250);
            delay(100);
        }
        
      //Checks if the game is over (when time runs out)
      if(timer > 0)
        timer -= 0.1f;
      else
        GameOver();
  }
    
  delay(100); // Make sure to adjust accordingly with the 'timer'
}



void PrintInfo()
{
  // This prints on the first line of the 16x2 display
  lcd.print("S: ");
  lcd.print(score);
  if(score < 10)
    lcd.print("       ");
   else
    lcd.print("      ");
  lcd.print("T: ");
  lcd.print(static_cast<int>(timer));
  
  lcd.setCursor(0, 1);
  for(int i = 0; i < 4; i++)
    lcd.print(combo[i]);
    lcd.print("        ");
  for(int i = 0; i < 4; i++)
    lcd.print(input[i]);
}



void ClearScreen() 
{
    //Iterates through each row and prints a blank
    lcd.setCursor(0, 0);
    for(int col = 0; col < 16; col++)
        lcd.print(" ");
        
    lcd.setCursor(0, 1);
    for(int col = 0; col < 16; col++)
    lcd.print(" ");

    lcd.setCursor(0, 0);
}



void MakeCombo()
{
    // Fill array with random values assigned to button numbers
    for(int i = 0; i < 4; i++)
        combo[i] = random(1, 5);
}



bool CheckCombo()
{
    // Check if the input == combo
    for(int i = 0; i < 4; i++)
    {
        if(combo[i] != input[i])
            return false;
    }
    return true;
}



void ResetInput()
{
    for(int i = 0; i < 4; i++)
        input[i] = 0;
    index = 0;
}



void GameOver()
{
    ClearScreen();
    
    lcd.print("GameOver");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
    
    isGame = false;
}
