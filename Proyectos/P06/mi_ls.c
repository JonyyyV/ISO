// mi_ls.c
//
//////////////////////////////////////////////////////

#include <stdio.h>
#include <dirent.h>
#include <string.h>

main(int argc, const char * argv[]){
        
	DIR *dir;
        struct dirent *rdir;
        char *error1 = "No hay parametros suficientes. Si quiere el actual ponga un punto\n";
        char *error2 = "No existe el directorio.\n";
        char *error3 = "No se ha podido leer.\n";
        char linea[80];

        //perror(" ");

        if(argc!=1){


                if(argc != 2){
                        write(2, error1, strlen(error1));
                        return 2;
                }

                if((dir=opendir(argv[1]))==NULL){
                        write(2, error2, strlen(error2));
                        return 3;
                }

                while((rdir=readdir(dir))!=NULL){
                        sprintf(linea, "%9d - %s\n", rdir->d_ino, rdir->d_name);
                        write(1, linea, strlen(linea));
                }

                return 0;
        }else{
              	 if((dir=opendir("."))==NULL){
                        write(2, error2, strlen(error2));
                        return 3;
                }

                while((rdir=readdir(dir))!=NULL){
                        sprintf(linea, "%d - %s\n", rdir->d_ino, rdir->d_name);
                        write(1, linea, strlen(linea));
                }
        }

}

