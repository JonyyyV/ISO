#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "s_header.h"

struct s_Info mDates;

int main(int argc [], char* argv[]){


 if(argc < 3){
  fprintf(stderr,"Numero de argumentos insuficiente");
  exit(1);
 }

 if(argc > 3){
  fprintf(stderr,"Demasiados argumentos");
  exit(2);
 }

 int fich1 = open(argv[1],O_RDONLY,0600);
 if(fich1 == -1){
  fprintf(stderr, " Fichero de salida inexistente");
  exit(3);
 }



 int fich2 = open(argv[2],O_RDONLY|O_WRONLY,0600);
 if(fich2 ==-1){
  fprintf(stderr,"Fichero de datos de entrada inexistente");
  exit(4);
 }

 int id = atoi(argv[3]);
 if(id == 0){
 fprintf(stderr,"Indice invalido");
 exit(5);
 }

 int mInfo;
 mInfo = fstat(fich1, mDates);

 if(mInfo.DatPosition = id){
 fprintf(stderr, "Posicion en uso en uso, utilize otro");
 exit(6);
 }


 char cont[512];
 int size2 = lseek(fich2,SEEK_END,0);
 read(fich2,cont,size2);
 int actPos = unchecked((int)mInfo.DatPostion);

if(id == -1){
  int idA = 0;
  while(actPos >= idA){
   idA++;
  }
  write(fich1,"\n",1);
  write(fich1,cont,size2+1);
  write(fich1,"\n",1);
  close(fich1);
  close(fich2);
  return(idA);
 }else{
  write(fich1,"\n",1);
  write(fich1,cont,size2+1);
  write(fich1, "\n",1);
  mInfo.DatPosition = mInfo.DatPosition + 1;
  close(fich1);
  close(fich2);
  return(id);
 }
}