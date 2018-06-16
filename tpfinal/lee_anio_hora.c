/*
Este programa lee el anio y la hora del RTC
Programacion UNSAM
Autor: David Lopez
Año: 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

#define P 0x70 /* RTC */

/* Esta funcion lee un byte del registro del RTC cuyo nro se recibe*/ 
unsigned char in (unsigned char reg){
  outb (reg, P);
  return inb(P + 1);
  }
  
int main(){
  unsigned char a, seg, min, hora, an1, an2;

  /* Dar permisos a los ports 70 y 71 */
  if (ioperm(P, 2, 1)) {
    perror("ioperm"); //Mueestra "ioperm" + el mensaje de error 
    exit(1);
  }
  
  /*Leer reg A*/
  a = in (0x0A);
  if ((a & 0x80) != 0) //Verif. bit 7 (UIP). Ojo prioridades operadores
    usleep (1984); //Esperar lo que dura la actualiz. en el peor caso (1984us)

  /*Leer segundos*/
  outb(0x00, P);
  seg = inb(P + 1);

  /*Leer minutos*/
  outb(0x02, P);
  min = inb(P + 1);

  /*Leer hora*/
  outb(0x04, P);
  hora = inb(P + 1);

  /*Leer anio primeros digitos*/
  outb(0x32, P);
  an1 = inb(P + 1);

  /*Leer anio ultimos digitos*/
  outb(0x09, P);
  an2 = inb(P + 1);

  /*Retirar permisos */
  if (ioperm(P, 2, 0)) {
    perror("ioperm");
    exit(1);
  }

  printf ("Anio: %02x%02x Hora: %02x:%02x:%02x\n", an1, an2, hora, min, seg);

  return 0;
}
