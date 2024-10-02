# Projeto_Comp_embarcada
Projeto de jogo de memória no arduino
Esse é um projeto do quarto semestre de Ciência da Computação da FEI, programado no Thinkercad, nele, @beatrizmanauia26 e @luaBortko2004 realizaram um jogo no arduino uno, de três fases. A primeira fase é um jogo da memória onde o jogador deve pressionar o botão e, após os 2 leds piscarem em uma sequência randômica, o jogador deve pressionar os botões para acertar a sequência.

Materiais:
-2 protobord (por estilo).
1 arduino UNO
1 display LCD
3 botões
2 leds (1 verde e 1 amarelo)
3 resistores de 300 ohms
1 buzzer
1 potenciometro 
varios fios 

Funcionamento: 
O primeiro botão, da esquerda para a direita, é o botão de iniciar e reiniciar o jogo.

Primeira fase: Jogo da memória. 
  -Após iniciar o jogo pressionando o botão, os leds piscam 10 vezes de maneiras aleatória e, após terminar, o jogador deve acertar a sequência pressionando os outros 2 botões (o da esquerda representa o led verde e o da direita, o amarelo). Caso o jogador erre, o jogo é reiniciado e toca uma música de derrota, caso ele acerte toda a sequência, toca uma música de vitória e passa para a segunda fase.

Segunda fase: perguntas faceis e dificeis:
   -Há uma ordem para a dificuldade das perguntas, as três primeiras perguntas são faceis e as duas últimas são dificeis. Criamos 5 opções de perguntas faceis e dificeis para que, na hora de aparecer para o jogador, elas sejam aleatoriezadas. Para responbder a pergunta, o segundo botão é de "sim" e o terceiro (botão mais a direita) é o de "não". 
   -O jogador pode pular uma questão, isso ocorre se ele não responder a pergunta nos 10 segundos que aparecem no display, porém ele só pode pular uma pergunta, caso tente pular outra, o jogo reinicia. Além disso, se o jogador errar a resposta o jogo também reinicia e aparece uma música de derrota. Caso ele acerte, aparece um som de acerto e continua a sequência de perguntas.
   
   Terceira fase: pergunta final:
   -Após acertar todas as 5 perguntas aleatórias, aparece uma pergunta final que é fixa, se o jogador acertá-la, aparece uma música de vitória e o jogo é finalizado, caso contrário, o jogo reinicia.

   Representação no tinkercad:
   ![image](https://github.com/user-attachments/assets/a7602c42-dfd1-4258-8792-2ec4743c8514)

   
