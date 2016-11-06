
//Programa preparado p/ controle via PC

//#include <Servo.h>
#include <SoftwareSerial.h>


                              //Entradas
//int const sLuz = 0;         //sensor de luminosidade(pino analogico)
int const botao = 0;          //botao de "panico"

                              //Saidas
//int const frente = 2;       //pino para andar para frente
//int const re = 3;           //pino para andar atras
//int const servo = 4;        //pino para servo motor
//int const luzes = 5;        //pino para leds de iluminaÃ§ao
//int const lRe = 6;          //pino para luz de re
//int const buzzer = 7;       //pino para buzzer
//int const esq = 9;          //pino para virar a esquerda
//int const dirt = 10;        //pino para virar a direita
int const alarme = 2;         //pino para acionamento de alarme (led, buzzers ...)

int const atraso = 100;       //tempo definido para delay
                              
Servo s;                      //Variavel p/ servo motor

int pos=90;                     //Posicao do servo motor (pos = posicao)
int pwm = 0;                    //variavel para realizar pwm (acelerar ou diminuir velocidade do motor)
//SoftwareSerial mBT (0,1);     //Inicializa a serial do mod Bluetooh nas portas 0 e 1 (RX, TX)

char op;                        //Armazena a operaÃ§es (EX: ir p/ frente)

//tema do MARIO - cada valor representa uma frequencia que corresponde a uma determinada nota musical
int musica[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,
                660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,
                430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,
                620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,
                1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,
                585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,
                500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,
                760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,
                500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,
                580,660,870,760,500,500,500,500,580,660,500,430,380,660,
                660,660,510,660,770,380};

//tempo de cada nota musical (musical[nota])
int dNotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,
                50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,
                100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,
                100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,
                150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,
                100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,
                100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,
                100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,
                80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,
                100,100,100,100,100,100};

void setup(){

  //Declaracao de pinos de saida
                              
  pinMode(frente, OUTPUT);
  pinMode(re, OUTPUT);
  pinMode(luzes, OUTPUT);
  pinMode(lRe,OUTPUT);
  pinMode(esq,OUTPUT);
  pinMode(dirt,OUTPUT);
  s.attach(servo);                       //Declaracao de var p/ servo motor
  
  s.write(90);                           //Definindo servo na posiÃ§ao 0

  Serial.begin(9600);
}

void andar(char run){                    // funcao p/ andar p/ frente ou p/ re
  if(run == 'f'){
    pwm += 5;
    digitalWrite(frente,pwm);
    digitalWrite(re,LOW);

  }
  else if(run == 'r'){
    pwm += 5;
    digitalWrite(re,pwm);
    digitalWrite(frente,LOW);
    luzRe(run);    // ligara luz de re quando run = 'r'

  }
  else{
    digitalWrite(frente,LOW);              // Desligara motor traseiro se se run <> 'f' ou 'r'
    digitalWrite(re,LOW);
  }
  
  if(pwm == 255)
    pwm = 255;
}

void virar(char lado){                      // funcao p/ direçao (virar a esquerda ou direita) - dir = direcao
  //COD P/ MOTOR CC
  
  /*
  COD P/ MOTOR CC
  if(dir == 'e'){
    digitalWrite(esq,64);                  //  64 de 255, ou seja, esq trabalhando com sada a 25% - controle PWM
    digitalWrite(dirt,LOW);
    delay(atraso);
    digitalWrite(esq,LOW);
  }
  else if(dir == 'd'){
    digitalWrite(dirt,64);                  //  64 de 255, ou seja, esq trabalhando com sada a 25% - controle PWM
    digitalWrite(re,LOW);
    delay(atraso);
    digitalWrite(dirt,LOW);;
  }
  else{
    digitalWrite(esq,LOW);                 // Desligara motor diantero se se dir <> 'e' ou 'd' 
    digitalWrite(dirt,LOW);
  }
  */
  

  //COD P/ SERVO MOTOR
  if(lado == 'e'){
    pos -= 5;
    s.write(pos);

    if(pos < 0)
      pos = 0;
  }
  else if(lado == 'd'){
    pos += 5;
    s.write(pos);
    
    if(pos > 180)
      pos = 180;
  }
  delay(15);
 
  //se der errado colocar um return na funcao p/ alterar o valor de pos
  //  na funcao void loop(){...}
}

void farol(char ch){                     //funcao para farois 
  if(ch == 'o'){
    digitalWrite(luzes,LOW);
  }
  else if(ch == 'l'){
    digitalWrite(luzes,HIGH);
  }
}

void luzRe(char cd){                      //cd = comando
  if(cd != 'r')
    digitalWrite(lRe,LOW);
  else
    digitalWrite(lRe,HIGH);
}

void frei(){                            //funcao para desligar saidas (O = output)
  pwm -= pwm;
  digitalWrite(re,pwm);
  digitalWrite(frente,pwm);
}

void buzina(){
  // for que caminhar pelas 156 notas da msica tema
  for (int nota = 0; nota < 156; nota++) {
    int dNota = dNotas[nota];
    tone(buzzer, musica[nota],dNota);
    //pausa depois de cada nota tocada (intervalo entre as notas)
    int pausadepoisdasnotas[] = {150,300,300,100,300,550,575,450,400,500,300,
                                 330,150,300,200,200,150,300,150,350,300,150,
                                 150,500,450,400,500,300,330,150,300,200,200,
                                 150,300,150,350,300,150,150,500,300,100,150,
                                 150,300,300,150,150,300,150,100,220,300,100,
                                 150,150,300,300,300,150,300,300,300,100,150,
                                 150,300,300,150,150,300,150,100,420,450,420,
                                 360,300,300,150,300,300,100,150,150,300,300,
                                 150,150,300,150,100,220,300,100,150,150,300,
                                 300,300,150,300,300,300,100,150,150,300,300,
                                 150,150,300,150,100,420,450,420,360,300,300,
                                 150,300,150,300,350,150,350,150,300,150,600,
                                 150,300,350,150,150,550,325,600,150,300,350,
                                 150,350,150,300,150,600,150,300,300,100,300,
                                 550,575};
    
    delay(pausadepoisdasnotas[nota]);
    
  }

    noTone(buzzer);
}

//String str;

void loop(){
  
  if(Serial.available()){                //obs.: caso tenha problemas troque o if por while
    op = Serial.read();
  
  /*
  str = op;
  
  if(str.indexOf("fr") > 0) andar(op); 
  
  if(str.indexOf("ed") > 0) virar(op); 
  
  if(str.indexOf("lo") > 0) farol(op);
 
  if(op == 'b') buzina(); 
  */
    andar(op);                          // f = frente                r= re
    virar(op);                          // e = virar a esquerda      d = virar a direita
    farol(op);                          // l = ligar leds (farois)   o = off - desliga farois
    
    /*aproveitando estrutura do cod antigo
    switch(op){                         //aproveitando estrutura do cod antigo
      case 'b':                         //b = buzina - liga a buzina (ou o tema do mario!!!)
        buzina();
        break;
      
    //default: mBT.print("OperaÃ§o invalida \n Comando: \n\t'e' = virar a esquerda\n\t 'd' = direita\n\t\n 'f' = frente\n\t 'r' = re ...");
    //default necessario apenas se na aplicacao nao tiver botoes ( necessidade de digitar)
    
    }
   */
    
    if(op == 'b')
      buzina();
    
    
    if(op != 'r')
      digitalWrite(lRe,LOW);
    

    
 /*   
    int luminosidade = analogRead(sLuz);   //Leitura do valor do sensor
    
    if(luminosidade < 750)
      digitalWrite(luzes, HIGH);
    else
      digitalWrite(luzes, LOW);
 */    
  }
  
  delay(atraso);
  
}

//transistor 547
//resistor 330
//coletor no motor
//base + resist + porta
//emissor no GND
//ponte H (difinir sentido de rotacao do motor)
//posicao servo motor (0 - totalmente esquerda, 180 - totalmente direita)
// sensor interno de temp: http://www.embarcados.com.br/arduino-uno-sensor-de-temperatura/
