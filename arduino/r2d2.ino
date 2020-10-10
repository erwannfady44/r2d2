#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

const int moteurGaucheAvance = 4;
const int moteurGaucheRecule = 5;
const int moteurDroitAvance = 6;
const int moteurDroitRecule = 7;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(moteurGaucheAvance, OUTPUT);
  pinMode(moteurGaucheRecule, OUTPUT);
  pinMode(moteurDroitAvance, OUTPUT);
  pinMode(moteurDroitRecule, OUTPUT);
}

void loop() {
  int commande[50];

  if (Serial.available() > 0) {

    String data = Serial.readStringUntil('\n');
    if (decode(commande, data)) {
        Serial.print("ok");
        mySerial.write("ok\n");
        bouger(commande);
    }
    else {
      Serial.print("erreur");
      mySerial.write("erreur\n");
    }
 }
}

void bouger(int commande[]) {
   switch (commande[0]) {
      //Si on veut reculer
      case 1 :
         analogWrite(moteurGaucheRecule, commande[1]);
         break;

      case 2 :
         analogWrite(moteurGaucheAvance, commande[1]);
         break;

      default :
         analogWrite(moteurGaucheAvance, 0);
         analogWrite(moteurGaucheRecule, 0);
         break;
   }

   switch (commande[2]) {
      //Si on veut reculer
      case 1 :
         analogWrite(moteurDroitRecule, commande[3]);
         break;

      case 2 :
         analogWrite(moteurDroitAvance, commande[3]);
         break;

      default :
         analogWrite(moteurDroitAvance, 0);
         analogWrite(moteurDroitRecule, 0);
         break;
   }
}

bool decode (int commande[], String data) {
    if (data[1] != '.')
        return false;
    int sens1, vitesse1 = 0, sens2, vitesse2 = 0, i = 0, j = 0;

    switch (data[0]) {
        case 48:
           while(data[i] != '.') {
                i++;
            }
            i++;

           sens1 = data[i+= 2] - 48;

           while (data[i + j] != '.') {
               j++;
           }


           while (j > 0) {
               vitesse1 += pow(10, (j - 1) * (data[i++] - 48));
               j--;
           }
           i++;

           sens2 = data[i+=2] - 48;

            while (data[i + j] != '.') {
                j++;
            }

           while (j > 0) {
               vitesse2 += pow(10, (j - 1) * (data[i++] - 48));
               j--;
           }

           commande[0] = sens1;
           commande[1] = vitesse1;
           commande[2] = sens2;
           commande[3] = vitesse2;

            return true;
            break;
    }
}