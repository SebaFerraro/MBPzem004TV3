  MBPzem004TV3 - Libreria Arduino para multiples modulos Pzem004TV3.0.
  Sebastian Ferraro  Copyright (c) 2020
  sebastian.ferraro.cerrutti@gmail.com
  https://github.com/SebaFerraro/MBPzem004TV3
  Bajo Licencia GPLV3


Libreria Arduino para manejar multiples PZEM-004Tv3.0.

Se comunica con los modulos PZEM-004Tv3.0 por Modbus sobre RS232/485 (via protocolo RTU ). Configurando una direccion diferente a cada modulo se pueden conectar todos al mismo puerto.


 SoftwareSerial pzemSerial(D5, D6);
 MBPzem004TV3 pzem1; 

  pzemSerial.begin(9600);
  pzem1.begin(1, pzemSerial);

  v = pzem1.readvoltage();
  i = pzem1.readcurrent();
  p = pzem1.readpower();
  e = pzem1.readenergy();
  f = pzem1.readfrequency();
  pf = pzem1.readpowerfactor();
  pa = pzem1.readpoweralarm();
  pat = pzem1.readpoweralarmthreshold();
  ad = pzem1.readaddress();



