// CHINESE RINGS PUZZLE - V1.2
//   Copyright by LAGSILVA
//        29.Mai.2017
//
//  09 Rings / 341 Moves


#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte anelOff[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte anelOn[8] = {
  B00100,
  B01010,
  B10001,
  B11111,
  B10001,
  B01010,
  B00100,
  B00000,
};

byte ponteiro[8] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,
  B00000,
};

String aneis;
int px, p1, movimentos,k;
int botoes = 0;
int estadoBotoes = 0;

#define btDir 1
#define btEsq 2
#define btCima 3
#define btBaixo 4
#define btOk 5
#define btNone 6

// Leitura dos Botoes
int ler_botoes()
{
  estadoBotoes = analogRead(0);
  
  // For V1.1 use this threshold (I applied this configuration)
  if (estadoBotoes < 50)   return btDir;
  if (estadoBotoes < 250)  return btCima;
  if (estadoBotoes < 450)  return btBaixo;
  if (estadoBotoes < 650)  return btEsq;
  if (estadoBotoes < 850)  return btOk;
  
  /* For V1.0 comment the other threshold and use the one below:
  if (estadoBotoes < 50)   return btDir;
  if (estadoBotoes < 195)  return btCima;
  if (estadoBotoes < 380)  return btBaixo;
  if (estadoBotoes < 555)  return btEsq;
  if (estadoBotoes < 790)  return btOk;
  */
  
  return btNone;  // Retorna None qdo todas as opcoes falharem
}

void setup() {

  lcd.createChar(0, anelOff);
  lcd.createChar(1, anelOn);
  lcd.createChar(2, ponteiro);

  lcd.begin(16, 2);

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("CHINESE RINGS");
  lcd.setCursor(2, 1);
  lcd.print("by LAGSILVA");

  delay(3000);

  telaInicial();

}


void loop() {

  do {
    botoes = ler_botoes();
    delay(100);
  } while (botoes == btNone);

  delay(100);

  switch (botoes) {

    case btDir:
      p1 = aneis.indexOf('1', 1);
      if (px <= p1) {
        if (aneis.substring(p1, p1 + 1) == "1") {
          px = px + 1;
        }
      }
      lcd.setCursor(0, 1);
      lcd.print("        ");
      lcd.setCursor(px - 1 , 1);
      lcd.write(byte(2));

      break;

    case btEsq:

      px = 1;
      lcd.setCursor(0, 1);
      lcd.print("         ");
      lcd.setCursor(px - 1 , 1);
      lcd.write(byte(2));

      break;

    case btOk:

      if (aneis.substring(px - 1, px) == "1") {
        if (aneis.substring(px, px + 1) == "1") {
          aneis.setCharAt(px, '0');
          lcd.setCursor(px - 1, 0);
          lcd.write(byte(0));
        }
        else {
          aneis.setCharAt(px, '1');
          lcd.setCursor(px - 1, 0);
          lcd.write(byte(1));
        }
      }
      movimentos = movimentos + 1;
      lcd.setCursor(12, 1);
      lcd.print(movimentos);

      break;

  }

  if (aneis == "1000000000") {
    lcd.clear();
    botoes = ler_botoes();
    lcd.setCursor(0, 0);
    lcd.print("CONGRATULATIONS!");
    lcd.setCursor(0, 1);
    lcd.print("Your Grade: ");
    lcd.print(34100 / movimentos);

    do {
      botoes = ler_botoes();
      delay(100);
    } while (botoes == btNone);
    delay(500);
    telaInicial();
  }

}


void telaInicial() {

  // Imprime Aneis e Estado Inicial
  lcd.clear();
  for (k = 0; k <= 8; k++) {
    lcd.setCursor(k, 0);
    lcd.write(byte(1));
  }
  lcd.setCursor(12, 0);
  lcd.print("Move");

  aneis = "1111111111";
  movimentos = 0;

  px = 1; //Posicao do Ponteiro "^"
  p1 = 1; //Posicao do Primeiro "1"

  lcd.setCursor(p1 - 1, 1);
  lcd.write(byte(2));
  lcd.setCursor(12, 1);
  lcd.print(movimentos);

}


