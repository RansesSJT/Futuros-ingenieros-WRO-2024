const int s0 = 10;
const int s1 = 11;
const int s2 = 12;
const int s3 = 13;
const int out = 7;


void setup()   
{  
  Serial.begin(9600);
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
 }  

void loop() { 
int R = getRojo();
delay(200);
int V = getVerde();
delay(200);
int A = getAzul();
delay(200);

Serial.print("Int R "+ String(R));
Serial.print("  --  Int V "+ String(V));
Serial.print("  --  Int Z "+ String(A));

  if ( R < A && V > A && R < 35 ) {
    Serial.print("  EL COLOR ROJO");
  }
  else if (A < R  && A < V && V < R ) {
    Serial.print("  EL COLOR ES AZUL");
  }
  else if (R > V  && A > V) {
    Serial.print("  EL COLOR VERDE");
  }
  
  else
  {
    Serial.print("  EL COLOR NO HA SIDO REGISTRADO");
  }
  Serial.println(" ");
  }

int getRojo(){
  //leer color rojo
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  int ROJO = pulseIn(out, LOW);
  return ROJO;
}

int getAzul(){
  //leer color azul
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  int AZUL = pulseIn(out, LOW);
  return AZUL;
}

int getVerde(){
  //leer color verde
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int VERDE = pulseIn(out, LOW);
  return VERDE;
}