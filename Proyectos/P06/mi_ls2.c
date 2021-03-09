// mi_lsl.c
// Similar a ls -l.
//////////////////////////////////////////////////////

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>


int main(int argc, const char * argv[]){
        int n;
	DIR *dir;
        struct dirent *rdir;
        struct stat st;
	char *error1 = "No hay parametros suficientes\n Uso : %s directorio";
        char *error2 = "No existe el directorio.\n";
        char *error3 = "No se ha podido obtener el inode.\n";
        char path[256];
        char linea[256];
        char buf[1024];

        //perror(" ");
        if(argc!=2){
             fprintf(stderr,"%s %s", error1, argv[0]) ;
             _exit(1);
        }

        if((dir=opendir(argv[1]))==NULL){
             fprintf(stderr,"%s", error2) ;
             _exit(2);
        }

        while((rdir=readdir(dir))!=NULL){
            sprintf(path, "%s/%s", argv[1], rdir->d_name);
            //sprintf(path, "%s",  rdir->d_name);
            // stat -> es el inodo de un archivo o directorio
            if(stat(path, &st)==0)
            {

                printf("%15s Mode(%d) NLink(%d) Size(%d) TCTime(%d)\n",path,st.st_mode, st.st_nlink, st.st_size, st.st_ctime);

            } else {
                fprintf(stderr,"%s", error3) ;
                _exit(3);

            }

        }
       _exit(0); // Todo OK
}




