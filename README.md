# Projeto_Comp_embarcada
Projeto de jogo de memória no arduino
Esse é um projeto do quarto semestre de Ciência da Computação da FEI, programado no Thinkercad, nele, @beatrizmanauia26 e @luaBortko2004 realizaram um jogo no arduino uno, de três fases. A primeira fase é um jogo da memória onde o jogador deve pressionar o botão e, após os 2 leds piscarem em uma sequência randômica, o jogador deve pressionar os botões para acertar a sequência.<br>

<br>
### Materiais:<br>
-2 protobord (por estilo).<br>
-1 arduino UNO<br>
-1 display LCD<br>
-3 botões<br>
-2 leds (1 verde e 1 amarelo)<br>
-3 resistores de 300 ohms<br>
-1 buzzer<br>
-1 potenciometro <br>
-varios fios <br>
<br>
### Funcionamento: <br>
O primeiro botão, da esquerda para a direita, é o botão de iniciar e reiniciar o jogo.<br>
<br>
<img src="https://github.com/user-attachments/assets/d296c479-9e7a-4f16-a2d6-aa19f0b6a471" alt="image" width="300"/><br>
<br>
### Primeira fase: Jogo da memória. <br>
  -Após iniciar o jogo pressionando o botão (imagem 2), os leds piscam 10 vezes de maneiras aleatória(imagem 3) e, após terminar, o jogador deve acertar a sequência pressionando os outros 2 botões(imagem 4) (o da esquerda representa o led verde e o da direita, o amarelo)(imagem 5). Caso o jogador erre, o jogo toca uma música de derrota (imagem 6 e 7) e é reiniciado, caso ele acerte toda a sequência, toca uma música de vitória (imagem 8) e passa para a segunda fase. (imagem 9)<br>
 <img src="https://github.com/user-attachments/assets/ba5d3602-e90f-4cb9-8663-2b0d1f2e934f" alt="image 2" width="300"/><br>
Imagem 2<br>

<img src="https://github.com/user-attachments/assets/ed3033db-9d74-459e-a6aa-0b6d459ac69d" alt="image 3" width="300"/><br>
Imagem 3<br>

<img src="https://github.com/user-attachments/assets/47e74f4b-d521-4430-93da-14f418d2c1a0" alt="image 4" width="300"/><br>
Imagem 4<br>

<img src="https://github.com/user-attachments/assets/75a04f2f-48c9-4231-9bc7-85158c8675ad" alt="image 5" width="300"/><br>
Imagem 5<br>

<img src="https://github.com/user-attachments/assets/e81d7348-1679-428e-8da5-768339949052" alt="image 6" width="300"/><br>
Imagem 6<br>

<img src="https://github.com/user-attachments/assets/e319d3aa-c1a3-433b-a675-bd6cb59d1280" alt="image 7" width="300"/><br>
Imagem 7<br>

<img src="https://github.com/user-attachments/assets/f377b04e-4045-41ff-86d9-3f33fbd7059c" alt="image 8" width="300"/><br>
Imagem 8
<br>
<br>
### Segunda fase: perguntas faceis e dificeis:<br>
   -Há uma ordem para a dificuldade das perguntas, as três primeiras perguntas são faceis e as duas últimas são dificeis. Criamos 5 opções de perguntas faceis e dificeis para que, na hora de aparecer para o jogador, elas sejam aleatoriezadas. Para responbder a pergunta, o segundo botão é de "sim" e o terceiro (botão mais a direita) é o de "não". 
   -O jogador pode pular uma questão, isso ocorre se ele não responder a pergunta nos 10 segundos que aparecem no display, porém ele só pode pular uma pergunta, caso tente pular outra, o jogo reinicia. Além disso, se o jogador errar a resposta o jogo também reinicia e aparece uma música de derrota. Caso ele acerte, aparece um som de acerto e continua a sequência de perguntas.<br>
   <br>
   ### Terceira fase: pergunta final:<br>
   -Após acertar todas as 5 perguntas aleatórias, aparece uma pergunta final que é fixa, se o jogador acertá-la, aparece uma música de vitória e o jogo é finalizado, caso contrário, o jogo reinicia.<br>
<br>
  ### Conclusão: <br>
  Realizar o projeto foi uma experiência muito enriquecedora, aprendemos muito. Todavia, o maior desafio encontrado foi achar uma maneira boa para resetar o arduino após apertar o botão. <br>

  ### Representação no tinkercad:
  <img src="https://github.com/user-attachments/assets/a7602c42-dfd1-4258-8792-2ec4743c8514" alt="image tinkercad" width="300"/><br>

  ### Representação na vida real:
  <img src="https://github.com/user-attachments/assets/70167849-d347-4e45-9cd6-40df4b2b1fba" alt="image real" width="300"/><br>

   

   
   
