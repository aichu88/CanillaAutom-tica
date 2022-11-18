const int LED = 12;
const int RELAY_MODULE = 8;
const int TIP = 9; //led simulador, relé y tip (para que se adapte a lo q haya)

const int TRIG = 6;
const int ECHO = 4;//variables del sensor

const int POT_DIST = A1;//iniciamos el pot de distancia
const int MINIMO_CM = 0;
const int MAXIMO_CM = 20;//rango de distancia en q se activa la canilla 
int distanciaPOT = 0;//variable final del pot distancia

const int POT_TIEMP = A0;//iniciamos el pot de tiempo
const int MINIMO_T = 0;
const int MAXIMO_T = 10;//rango de tiempo q se activa la canilla
int tiempoPOT = 0;//variable final del pot tiempo

int lenght;
int distance;//variables para medir el ultrtasonico

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO,INPUT);
  Serial.begin(9600);
}


void loop()
{
  
  distanciaPOT = analogRead(POT_DIST);//leemos lo que recibe el pot de distancia
  
  delay(300);
  unsigned int valPOT_DIST = map(distanciaPOT, 0, 1023, MINIMO_CM, MAXIMO_CM);//usamos esta funcion para cambiar de rango lo que lee el pot de distancia

  tiempoPOT = analogRead(POT_TIEMP);//leemos lo que recibe el pot de tiempo
  unsigned int valPOT_TIEMP = map(tiempoPOT, 0, 1023, MINIMO_T, MAXIMO_T);//usamos esta funcion para cambiar de rango lo que lee el pot de tiempo

  digitalWrite(TRIG,HIGH);//Cosas
  delay(1);
  digitalWrite(TRIG,LOW);//del
  
  lenght=pulseIn(ECHO,HIGH);
  distance=lenght/58.2;//Trigger
  
  Serial.print("Distancia: ");//Imprimimos la distancia q toma el sensor
  Serial.print(distance);
  Serial.print(" Distancia max: ");//Imprimimos la distancia q toma el pot
  Serial.print(valPOT_DIST);
  Serial.print(" Tiempo prendido: ");//Imprimimos el tioempo que va a abrirse la canilla
  Serial.print(valPOT_TIEMP);
  Serial.println("");
  
  
  
  if(distance<=valPOT_DIST && distance >=0){//si la distancia del sensor es menor o igual a la del potenciometro y mayor a 0
    prenderElectrovalvula();
    delay(valPOT_TIEMP);//Prende la electrovalvula el tiempo que marca el pot de tiempo
    apagarElectrovalvula();
  }
  else{
    apagarElectrovalvula();
  }
    
}

void prenderElectrovalvula()
{
    digitalWrite(LED,HIGH);
    digitalWrite(RELAY_MODULE,LOW);
}
  
void apagarElectrovalvula()
{
    digitalWrite(LED,LOW);
    digitalWrite(RELAY_MODULE,HIGH);
}
