/*
  MBPzem004TV3 - Libreria Arduino para multiples modulos Pzem004TV3.0.
  Sebastian Ferraro  Copyright (c) 2020
  sebastian.ferraro.cerrutti@gmail.com
  https://github.com/SebaFerraro/MBPzem004TV3
  Bajo Licencia GPLV3
*/

#include <MBPzem004TV3.h>
#include <SoftwareSerial.h>

SoftwareSerial pzemSerial(D5, D6);
MBPzem004TV3 pzem1; 
MBPzem004TV3 pzem2;

void setup() {
  Serial.begin(115200);
  pzemSerial.begin(9600);
  pzem1.begin(1, pzemSerial);
  pzem2.begin(2, pzemSerial);

}

void loop() {
  uint8_t resl=0;
  Serial.println("################## PZEM 1 #####################");
  double v = pzem1.readvoltage();
  double i = pzem1.readcurrent();
  double p = pzem1.readpower();
  double e = pzem1.readenergy();
  double f = pzem1.readfrequency();
  double pf = pzem1.readpowerfactor();
  double pa = pzem1.readpoweralarm();
  double pat = pzem1.readpoweralarmthreshold();
  uint8_t ad = pzem1.readaddress();
  Serial.print("Voltaje: ");Serial.print(v);Serial.print(" Corriente: ");Serial.print(i);Serial.print(" Potencia: ");Serial.print(p);Serial.print(" Energia: ");Serial.println(e);
  Serial.print("Frecuenci: ");Serial.print(f);Serial.print(" Fi: ");Serial.print(pf);Serial.print(" Alarma Potencia: ");Serial.print(pa);Serial.print(" Umbral Alarma Potencia: ");Serial.println(pat);
  Serial.print("Address: ");Serial.println(ad);
 
  delay(1000);
  /*
  resl=pzem1.setaddress(0x03);
  Serial.print("Address: ");Serial.println(ad);
  delay(1000);
  
  resl=pzem1.setaddress(0x01);
  Serial.print("Address: ");Serial.println(ad);
  delay(1000);
  */
  
  //resl=pzem1.setpoweralarmthreshold(25000);
  //pzem1.resetenergy();
  //pat = pzem1.readpoweralarmthreshold();
  //Serial.print(pa);Serial.print(" Umbral Alarma Potencia: ");Serial.println(pat);
  
  Serial.println("##### PZEM 1 #####");
  delay(5000);
  Serial.println("################## PZEM 2 #####################");
  v = pzem2.readvoltage();
  i = pzem2.readcurrent();
  p = pzem2.readpower();
  e = pzem2.readenergy();
  f = pzem2.readfrequency();
  pf = pzem2.readpowerfactor();
  pa = pzem2.readpoweralarm();
  pat = pzem2.readpoweralarmthreshold();
  ad = pzem2.readaddress();
  Serial.println("################## PZEM 2 #####################");
  Serial.print("Voltaje: ");Serial.print(v);Serial.print(" Corriente: ");Serial.print(i);Serial.print(" Potencia: ");Serial.print(p);Serial.print(" Energia: ");Serial.println(e);
  Serial.print("Frecuenci: ");Serial.print(f);Serial.print(" Fi: ");Serial.print(pf);Serial.print(" Alarma Potencia: ");Serial.print(pa);Serial.print(" Umbral Alarma Potencia: ");Serial.println(pat);
  Serial.print("Address: ");Serial.println(ad);
  Serial.println("##### PZEM 2 #####");
  
}
