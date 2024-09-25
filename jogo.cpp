#include <LiquidCrystal.h>
#include <time.h>
#define NOTE_F4  349
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_C5  523
#define REST      0

//leds
int pinLedVer = 9;
int pinLedAm = 10;

//botoes (re)inicia e jogo
int pinBotIn = 3;
int pinBot1 = 2;
int pinBot2 = 8;

//contador para ver se botao de iniciar foi clicado
int inicia = 0;

//iniciar o display
LiquidCrystal lcd_1(12, 11, 7, 6, 5, 4);

//buzzer
int pinBuz = 13;
int melodiaFase[] = {
  NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
};
int notes = sizeof(melodiaFase) / sizeof(melodiaFase[0]) / 2;
int wholenote = (60000 * 4) / 120;
int divider = 0, noteDuration = 0;

void setup(){
  //aparecer texto no display em linhas diferentes
  lcd_1.begin(16, 2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Seja Bem Vindo!");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Pressione inicia");
  
  //declarar pinos como input ou output
  pinMode(pinLedVer,OUTPUT);
  pinMode(pinLedAm,OUTPUT);
  pinMode(pinBotIn,INPUT_PULLUP);
  pinMode(pinBot1,INPUT_PULLUP);
  pinMode(pinBot2,INPUT_PULLUP);
  pinMode(pinBuz,OUTPUT);
  
  //configura interrupcao externa, chama funcao reinicia sempre que clica no botal
  attachInterrupt(digitalPinToInterrupt(pinBotIn), reinicia, RISING);
  
  //inicializar pra criar numeros aleatorios
  randomSeed(analogRead(0));
  Serial.begin(9600);
  
}

void loop()
{
  //arrays para guardar os numeros aleatorios do led e da resposta da pessoa para compar e aparecer correto ou nao no display
  int leds[10];
  int ledsResp[10];
  if(inicia == 0){
     lcd_1.setCursor(0, 0);
  	 lcd_1.print("Seja Bem Vindo!");
     lcd_1.setCursor(0, 1);
     lcd_1.print("Pressione inicia");
  }
  // se clicar no botao de iniciar (inicia==1)
  if(inicia == 1){  
    lcd_1.clear();
    lcd_1.print("Iniciando o jogo");
    delay(2000);
    lcd_1.clear();
    lcd_1.print("Memorize as");
    lcd_1.setCursor(0, 1);
    lcd_1.print("cores dos LEDs");
    delay(500);
    //cria 10 numeros aleatorioso
    for(int cont = 0; cont<10;cont++){
      int numAle = random(0,2); //num aleatorio entre 0 e 1
      delay(500);
      //Serial.println(numAle);
      //se numero aleatorio for 1 adiciona valor no array e o pino verde pisca (acende e apaga) e pino amarelo apaga 
      if(numAle == 1){
        digitalWrite(pinLedVer,HIGH);
        delay(200);
        leds[cont] = 1;
        //Serial.println(leds[cont]);
        digitalWrite(pinLedVer,LOW);
        digitalWrite(pinLedAm,LOW);
      }else{
        leds[cont] = 0;
        digitalWrite(pinLedAm,HIGH);
        delay(200);
        digitalWrite(pinLedAm,LOW);
        digitalWrite(pinLedVer,LOW);
      }
     }
    //para parar de piscar apos 10x ???
  digitalWrite(pinLedVer,LOW);
  digitalWrite(pinLedAm,LOW);
    
  lcd_1.clear();
  lcd_1.print("Agora repita");
  lcd_1.setCursor(0, 1);
  lcd_1.print("a sequencia");  
  delay(500);
  //ver 10x a tentativa da pessoa de acertar a sequencia  
    for(int i = 0; i<10; i++){
      //se pessoa clicar no botao1(ele fica 0 pq eh pullup) guarda 1 no arrayresp
     unsigned long startTime = millis();
      while (millis() - startTime < 5000) { // 10 segundos no while
        //cria variavel dos outros botoes para guardar no array e comparar com array leds
    	int bot1 = digitalRead(pinBot1);
    	int bot2 = digitalRead(pinBot2);
        //Serial.println("Led: ");
        Serial.println(leds[i]);
          if (bot1 == 0) {
              ledsResp[i] = 1;
              break;
          } else if (bot2 == 0) {
              ledsResp[i] = 0;
              break;
          }
      }
      //Serial.println("Resp: ");
      //Serial.println(ledsResp[i]);
      lcd_1.clear();
  	  lcd_1.print("Sequencia: ");
      lcd_1.setCursor(12, 0);
      //printa sequencia
      lcd_1.print(i+1);
      if(ledsResp[i] == leds[i]){
    	lcd_1.setCursor(0, 1);
        lcd_1.print("Correto");
      }else{
        lcd_1.setCursor(0, 1);
        lcd_1.print("Incorreto");
        delay(1000);
        lcd_1.clear();
        lcd_1.setCursor(0, 0);
        lcd_1.print("Melhore...");
        lcd_1.setCursor(5,1);
        lcd_1.print("( -__-)");
        delay(3000);
		inicia = 0;
        return;//volta pro inicio
      }
      delay(400);
    }
  lcd_1.clear();
  lcd_1.print("Parabens ^-^");
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melodiaFase[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
     
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }
    tone(pinBuz, melodiaFase[thisNote], noteDuration*0.9);
    delay(noteDuration);
    noTone(pinBuz);
  }
  delay(2000);
  }//chaves do if == 1
}

void reinicia(){
  lcd_1.clear();
  if(inicia == 0){
    inicia = 1;
  }else{
    lcd_1.print("Reiniciando...");
    inicia = 0;
  }
}