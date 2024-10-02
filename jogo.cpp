#include <LiquidCrystal.h>
#include <time.h>

//aviso que tempo ta acabando
#define RE 294

//avisa que acertou pergunta
#define DO 262

//buzzer vitoria
#define NOTE_F4  349
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_C5  523
#define REST      0

//buzzer perdeu
#define NOTE_E4  330
#define NOTE_D4  294

//buzzer fim
#define NOTE_AS4 466
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_GS5 831
#define NOTE_AS5 932

#define RESET asm ("jmp (0x0000)")
//função que faz o arduino "reseta"
//volta no loop

//Perguntas
//Faceis:
//1.O arduino tem 13 portas? n
//2.O float armazena até 32 bytes? n
//3.Arduino é um microprocessador? n
//4.'É 	um' representa herança? s
//5. ArrayList é capaz de armazenar tipos primitivos? n

//Dificeis:
//1.Frozen lançou em 2012? n
//2. a +(ou) 1 = 1? s
//3. A intrução AJMP tem 2 MC? s 
//4. Saruê é um marsupial? s
//5. Agumon é um pokemon? n

//Permanente: GOSTOU DO QUIZ? S 

//segunda fase
const char* perguntas_Faceis[]{
  "O arduino tem 13 portas?", 
  "O float armazena ate 32 bytes?",
  "Arduino e um microprocessador?", 
  "\"E um\" representa heranca?",
  "ArrayList pode guardar tipos primitivos?"
};
const char* respostas_Faceis[] = {
  "n", "n", "n", "s", "n"
};

const char* perguntas_Dificeis[] = {
  "Frozen lancou em 2012?", 
  "a +(ou) 1 = 1?", 
  "A instrucao AJMP tem 2 MC?",
  "Sarue e um marsupial?", 
  "Agumon e um Pokemon?"
};

const char* respostas_Dificeis[] = {
  "n", "s", "s", "s", "n"
};
//variavel para nao repetir as perguntas, comparar quais perguntas ja foram feitas
int variav = -1; //-1 pq random de 0 a 5
int variav2 = -1;

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

//buzzer perdeu
int melodiaPerdeu[] = {
  NOTE_F4,8, NOTE_E4,8, 
  NOTE_D4,-2,
};

int notesPerdeu = sizeof(melodiaPerdeu) / sizeof(melodiaPerdeu[0]) / 2;
int wholenotePerdeu = (60000 * 4) / 108;

//buzzer final
int melodiaFinal[] = {
  NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//7
  NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
  NOTE_AS5,-2,  NOTE_AS5,8,  NOTE_AS5,8,  NOTE_GS5,8,  NOTE_FS5,16,
  NOTE_GS5,-8,  NOTE_FS5,16,  NOTE_F5,2,  
};
int wholenoteFim = (60000 * 4) / 88;
int notesFinal = sizeof(melodiaFinal) / sizeof(melodiaFinal[0]) / 2;


//segunda fase 
char variavel[30]; //variavel para guardar sprintf

void setup(){
  //aparecer texto no display em linhas diferentes
  lcd_1.begin(16, 2);
  
  //declarar pinos como input ou output
  pinMode(pinLedVer,OUTPUT);
  pinMode(pinLedAm,OUTPUT);
  pinMode(pinBotIn,INPUT_PULLUP); //botao de iniciar e reiniciar
  pinMode(pinBot1,INPUT_PULLUP);
  pinMode(pinBot2,INPUT_PULLUP);
  pinMode(pinBuz,OUTPUT);
  
  //configura interrupcao externa, chama funcao reinicia sempre que clica no botal
  attachInterrupt(digitalPinToInterrupt(pinBotIn), reinicia, RISING);
  
  //inicializar pra criar numeros aleatorios
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop(){
  //arrays para guardar os numeros aleatorios do led e da resposta da pessoa para compar e aparecer correto ou nao no display
 // inicia=2; //Para comecar na segunda fase
  int leds[10];
  int ledsResp[10];//guarda resposta da fase de memoria para compára com o que usuario pressionou
 
  //segunda fase
  int contQuestao = 0;
  int pularQuestao = 0; //se tempo chegar no 0 faço valer 1 e se passar de 1 reinicia jogo
  int tempoRestante = 10; //segundos para jogador escolher a resposta
  char* resp = " ";
  if(inicia == 0){
     lcd_1.setCursor(0, 0);
  	 lcd_1.print("Seja Bem Vindo!");
     lcd_1.setCursor(0, 1);
     lcd_1.print("Pressione inicia");
  }
  // se clicar no botao de iniciar (inicia==1) e começa jogo
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
      int numAle = random(0,2); //num aleatorio entre 0 e 1 para leds
      delay(500);
      //Serial.println(numAle);
      //se numero aleatorio for 1 adiciona valor no array e o pino verde pisca (acende e apaga) e pino amarelo apaga 
      if(numAle == 1){
        digitalWrite(pinLedVer,HIGH);
        delay(200);
        leds[cont] = 1;
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
     //mantem o while em 5seg para pessoa conseguir responder
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
      if(ledsResp[i] == leds[i]){//se numero arrmaazenado no array leds for = a respostas do botao ta certo
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
        lcd_1.print("( --)");
        
      //buzzer perdeu
      for (int thisNote = 0; thisNote < notesPerdeu * 2; thisNote = thisNote + 2) {
    	divider = melodiaPerdeu[thisNote + 1];
    	if (divider > 0) {
      		noteDuration = (wholenotePerdeu) / divider;
    	} else if (divider < 0) {
      		noteDuration = (wholenotePerdeu) / abs(divider);
      		noteDuration *= 1.5;
    	}
    	tone(pinBuz, melodiaPerdeu[thisNote], noteDuration*0.9);
    	delay(noteDuration);
    	noTone(pinBuz);
  	  }
        delay(2000);
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
  inicia = 2; //se acertou todas as sequencias vai para a segunda fase
  }//chaves do if == 1
  
  else if(inicia == 2){//2 parte
    lcd_1.clear();
    lcd_1.print("Bem Vindo");
    lcd_1.setCursor(0, 1);
    lcd_1.print("a Segunda Fase!");
    delay(2000);
    lcd_1.clear();
    lcd_1.print("Perguntas e");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Respostas");
    delay(2000);
    lcd_1.clear();
    lcd_1.print("Responda Sim");
    lcd_1.setCursor(0, 1);
    lcd_1.print("ou Nao");
    delay(2000);
    //perguntas randomizadas facil
    int contQ = 0;  //contador perguntas
    while(contQ < 5){//para ter 3 perguntas faceis e 2 dificieis
      int pergAle = random(0,5); //num aleatorio entre 0 e 5
       if(variav != pergAle && variav2 != pergAle){//nao repetir pergunta
          contQ = contQ + 1;
    	  lcd_1.clear();
          sprintf(variavel,"Questao %d de 5", contQ);
          lcd_1.print(variavel);
          delay(2000);
          lcd_1.clear();
         if(variav == -1){
           variav = pergAle;//indice da pergunta
         }else{//se variav tem algo esse go passa para variav2
           variav2 = variav;
           variav = pergAle;
         }
         //perguntas randomizadas dificeis
         String perg_display = "";
         if(contQ<4){//3 perg faceis
         	perg_display = perguntas_Faceis[pergAle];
         }else{//2 dificeis (pq contQ<5, 5-3 = 2
           	perg_display = perguntas_Dificeis[pergAle];
         }
          //pergunta scroll na tela
          lcd_1.print(perg_display);
          delay(1000); // aguarda para ler a pergunta
          // Exibe a pergunta completamente, se couber no display
      	  if (perg_display.length() > 16) {
      		// Scroll da pergunta (-16 para caber no display)
        	for (int i = 0; i < perg_display.length() - 16; i++) {
        		lcd_1.scrollDisplayLeft();
        		delay(200); // ajusta a velocidade do scroll
      		}
         }
         delay(2000);
         lcd_1.clear();//para aparecer a pergunta so uma vez no display
         //Serial.println(perg_display);
         //verificar se algum botao 
        int aperta = 0;
        for(int tempoRestante = 10;tempoRestante>=0;tempoRestante--){
         //tempochega na metadfe começa a apitar
          if(tempoRestante < 5){
             tone(pinBuz, RE);
          }
          // Atualiza o display com os segundos restantes
           lcd_1.clear();
           lcd_1.print("Tempo:");
           lcd_1.setCursor(8, 0); // Move esquerda o texto
           //lcd_1.print(secondsRemaining); 
           lcd_1.print(tempoRestante);
           lcd_1.setCursor(0, 1); 
           lcd_1.print("   Sim    Nao    ");
           delay(1000);
           int bot1 = digitalRead(pinBot1);
           int bot2 = digitalRead(pinBot2);
           if(contQ<4){//Pergunta Facil
             if (bot1 == 0) { //botao 1 é sim (0 quando pressionado pq eh input pull up)
                 resp = "s";
                 aperta = 1; //botao pressionado
                 if(respostas_Faceis[variav] == resp){
                   tone(pinBuz, DO, 1000);
                   lcd_1.clear();
                   lcd_1.print("Correto");
                   lcd_1.setCursor(0, 1); 
                   lcd_1.print("  *Sim    Nao    ");
                   delay(2000);
                   break;     		 
                 }else{//se respostas nao forem iguais, errou
                   lcd_1.clear();
                   lcd_1.print(" Errou :(  ");
                   lcd_1.setCursor(0, 1); 
                   lcd_1.print("   Sim   *Nao    ");
                   delay(2000);
                  //buzzer perdeu
                  for (int thisNote = 0; thisNote < notesPerdeu * 2; thisNote = thisNote + 2) {
                    divider = melodiaPerdeu[thisNote + 1];
                    if (divider > 0) {
                        noteDuration = (wholenotePerdeu) / divider;
                    } else if (divider < 0) {
                        noteDuration = (wholenotePerdeu) / abs(divider);
                        noteDuration *= 1.5;
                    }
                    tone(pinBuz, melodiaPerdeu[thisNote], noteDuration*0.9);
                    delay(noteDuration);
                    noTone(pinBuz);
                  }
                   RESET;
                 }
             }else if (bot2 == 0) {//nao
                resp = "n";
                aperta = 1;
                if(respostas_Faceis[variav] == resp){
                  tone(pinBuz, DO, 1000);
                  lcd_1.clear();
                  lcd_1.print("Correto");
                  lcd_1.setCursor(0, 1); 
                  lcd_1.print("   Sim   *Nao    ");
                  delay(2000);
                  break;
                 }else{
                   lcd_1.clear();
                   lcd_1.print(" Errou :(  ");
                   lcd_1.setCursor(0, 1); 
                   lcd_1.print("  *Sim    Nao    ");
                   delay(2000);
                   //buzzer perdeu
                   for (int thisNote = 0; thisNote < notesPerdeu * 2; thisNote = thisNote + 2) {
                      divider = melodiaPerdeu[thisNote + 1];
                      if (divider > 0) {
                          noteDuration = (wholenotePerdeu) / divider;
                      } else if (divider < 0) {
                          noteDuration = (wholenotePerdeu) / abs(divider);
                          noteDuration *= 1.5;
                      }
                      tone(pinBuz, melodiaPerdeu[thisNote], noteDuration*0.9);
                      delay(noteDuration);
                      noTone(pinBuz);
                    }
                   RESET;
                 }
            }//chaves do else if
           }else{//Perguntas dificeis
             if (bot1 == 0) { //botao 1 é sim (0 quando pressionado pq eh input pull up)
                 resp = "s";
                 aperta = 1; //botao pressionado
                 if(respostas_Dificeis[variav] == resp){
                   tone(pinBuz, DO, 1000);
                   lcd_1.clear();
                   lcd_1.print("Correto");
                   lcd_1.setCursor(0, 1); 
                   lcd_1.print("  *Sim    Nao    ");
                   delay(2000);
                   break;     		 
                 }else{//se respostas nao forem iguais, errou
                   lcd_1.clear();
                   lcd_1.print(" Errou :(  ");
                   lcd_1.setCursor(0, 1); 
                   lcd_1.print("   Sim   *Nao    ");
                   delay(2000);
                    //buzzer perdeu
                    for (int thisNote = 0; thisNote < notesPerdeu * 2; thisNote = thisNote + 2) {
                      divider = melodiaPerdeu[thisNote + 1];
                      if (divider > 0) {
                          noteDuration = (wholenotePerdeu) / divider;
                      } else if (divider < 0) {
                          noteDuration = (wholenotePerdeu) / abs(divider);
                          noteDuration *= 1.5;
                      }
                      tone(pinBuz, melodiaPerdeu[thisNote], noteDuration*0.9);
                      delay(noteDuration);
                      noTone(pinBuz);
                    }
                   RESET;
                 }
             }else if (bot2 == 0) {//nao
                resp = "n";
                aperta = 1;
                if(respostas_Dificeis[variav] == resp){
                  tone(pinBuz, DO, 1000);
                  lcd_1.clear();
                  lcd_1.print("Correto");
                  lcd_1.setCursor(0, 1); 
                  lcd_1.print("   Sim   *Nao    ");
                  delay(2000);
                  break;
                 }else{
                   lcd_1.clear();
                   lcd_1.print(" Errou :(  ");
                   lcd_1.setCursor(0, 1); 
                   lcd_1.print("  *Sim    Nao    ");
                   delay(2000);
                   //buzzer perdeu
                    for (int thisNote = 0; thisNote < notesPerdeu * 2; thisNote = thisNote + 2) {
                      divider = melodiaPerdeu[thisNote + 1];
                      if (divider > 0) {
                          noteDuration = (wholenotePerdeu) / divider;
                      } else if (divider < 0) {
                          noteDuration = (wholenotePerdeu) / abs(divider);
                          noteDuration *= 1.5;
                      }
                      tone(pinBuz, melodiaPerdeu[thisNote], noteDuration*0.9);
                      delay(noteDuration);
                      noTone(pinBuz);
                    }
                   RESET;
                 }
            }
           }
        }//chaves do for_pergunta 
         noTone(pinBuz); //para de apitar o aviso que tempo ta acabando
        //saiu do for,tempo ja chego no 0 e botoes nao foram clicados (aperta == 0), = pular questao
        if(aperta == 0){
          pularQuestao = pularQuestao + 1; //para permitir que o jogador nao responda uma pergunta
          lcd_1.clear();
          lcd_1.print("Tempo esgotado!");
          delay(1000);
          if(pularQuestao > 1){ //jogador nao responder mais dem 1 pergunta
            lcd_1.clear();
            lcd_1.print("Perdeu a chance");
            delay(2000);
             //buzzer perdeu
            for (int thisNote = 0; thisNote < notesPerdeu * 2; thisNote = thisNote + 2) {
              divider = melodiaPerdeu[thisNote + 1];
              if (divider > 0) {
                  noteDuration = (wholenotePerdeu) / divider;
              } else if (divider < 0) {
                  noteDuration = (wholenotePerdeu) / abs(divider);
                  noteDuration *= 1.5;
              }
              tone(pinBuz, melodiaPerdeu[thisNote], noteDuration*0.9);
              delay(noteDuration);
              noTone(pinBuz);
            }
            RESET;
          }//chaves do if
        }//chaves do if
          delay(2000);
         }//chaves do if
       }//chaves do if
      delay(400); //nao clicar duplo no botao
    inicia = 3;//quando acaba as peguntas ir pra fase 3
  }//if == 2
  else if(inicia == 3){
    lcd_1.clear();
    lcd_1.print("Pergunta Final!");
    delay(2000);
    lcd_1.clear();
    lcd_1.print("Gostou do quiz?");
    delay(1000);
    int aperta = 0;
        for(int tempoRestante = 10;tempoRestante>=0;tempoRestante--){
          if(tempoRestante < 5){
             tone(pinBuz, RE);
          }
          // Atualiza o display com os segundos restantes
           lcd_1.clear();
           lcd_1.print("Tempo:");
           lcd_1.setCursor(8, 0); // Move esquerda o texto
           lcd_1.print(tempoRestante);
           lcd_1.setCursor(0, 1); 
           lcd_1.print("   Sim    Nao    ");
           delay(1000);
           int bot1 = digitalRead(pinBot1);
           int bot2 = digitalRead(pinBot2);
             if (bot1 == 0) { //botao 1 é sim (0 quando pressionado pq eh input pull up)
                aperta = 1; //botao pressionado
                lcd_1.clear();
                lcd_1.print("Correto");
                lcd_1.setCursor(0, 1); 
                lcd_1.print("  *Sim    Nao    ");
                delay(2000);
                break;     		
             }else if (bot2 == 0) {//nao
                aperta = 1;
                lcd_1.clear();
                lcd_1.print("Poxa ;-;");
                lcd_1.setCursor(0, 1); 
                lcd_1.print("  *Sim    Nao    ");
                delay(2000);
                //buzzer perdeu
                for (int thisNote = 0; thisNote < notesPerdeu * 2; thisNote = thisNote + 2) {
                  divider = melodiaPerdeu[thisNote + 1];
                  if (divider > 0) {
                      noteDuration = (wholenotePerdeu) / divider;
                  } else if (divider < 0) {
                      noteDuration = (wholenotePerdeu) / abs(divider);
                      noteDuration *= 1.5;
                  }
                  tone(pinBuz, melodiaPerdeu[thisNote], noteDuration*0.9);
                  delay(noteDuration);
                  noTone(pinBuz);
                }
                RESET;
            }//chaves do else if
        }//chaves do for_pergunta 
        noTone(pinBuz);
        //saiu do for,tempo ja chego no 0 e botoes nao foram clicados = pular questao
        if(aperta == 0){
          lcd_1.clear();
          lcd_1.print("Tempo esgotado!");
          delay(1000);
          lcd_1.clear();
          lcd_1.print("Perdeu a chance");
          delay(2000);
           //buzzer perdeu
          for (int thisNote = 0; thisNote < notesPerdeu * 2; thisNote = thisNote + 2) {
            divider = melodiaPerdeu[thisNote + 1];
            if (divider > 0) {
                noteDuration = (wholenotePerdeu) / divider;
            } else if (divider < 0) {
                noteDuration = (wholenotePerdeu) / abs(divider);
                noteDuration *= 1.5;
            }
            tone(pinBuz, melodiaPerdeu[thisNote], noteDuration*0.9);
            delay(noteDuration);
            noTone(pinBuz);
          }
          RESET;
        }
    lcd_1.clear();
    lcd_1.print("  Parabens! <3  ");
    
    //buzzer fim
     for (int thisNote = 0; thisNote < notesFinal * 2; thisNote = thisNote + 2) {
      divider = melodiaFinal[thisNote + 1];
      if (divider > 0) {
        noteDuration = (wholenoteFim) / divider;
      } else if (divider < 0) {
        noteDuration = (wholenoteFim) / abs(divider);
        noteDuration *= 1.5; 
      }
      //tocar musica
      tone(pinBuz, melodiaFinal[thisNote], noteDuration*0.9);
      delay(noteDuration);
      noTone(pinBuz);
    }
    RESET;
  }//chave do if inicia == 3
}

void reinicia(){
  if(inicia == 0){//se botao foi clicado
    inicia = 1;
  }else{
    tone(pinBuz, DO);
    noTone(pinBuz);
    lcd_1.clear();
    lcd_1.print("Reiniciando...");
    delay(100000);
    RESET;
  }
}
 