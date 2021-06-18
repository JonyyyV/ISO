#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
    int org_f, dst_f, err, dig;
    char buf[1];
    struct stat st;

    if (argc != 4) //Comprobamos que el numero de argumentos introducido es el correcto
    {
        printf("Error: Introduce un número adecuado de argumentos\n");
        exit(2);
    }
    
    if (isdigit(*argv[3])) //Comprobamos que el argumento correspondiente a pos es adecuado.
    {
        dig = atoi(argv[3]);
        if((org_f = open(argv[1], O_RDONLY)) == -1){ //Abrimos el archivo del que queremos leer los datos
            printf("Error al abrir el fichero de origen\n");
            exit(2);
        }
        
        stat(argv[1], &st);
        int size = st.st_size;  


        if((dst_f = open(argv[2], O_WRONLY | O_APPEND | O_CREAT, 0644)) == -1){ //Abrimos o en su defecto creamos el archivo en el que queremos escribir los datos
            printf("Error al cerrar el fichero de origen\n");
            exit(2);
        }
        if (lseek(org_f, dig, SEEK_SET) == dig - 1) //Posicionamos el puntero en la posicion indicada por parametros, en caso de que no tenga tal posicion, se sale del if.
        {
            for (int i = dig; i < size; i++) //Realizamos un ciclo por cada byte que tengamos que reescribir.
            {
                err = read(org_f, buf, 1); //Leemos el byte desde el archivo de origen.
                if (err == -1)
                {
                    printf("Error al leer el fichero de origen.\n");
                    exit(2);
                }
                if (err = 0)
                    break;

                err = write(dst_f, buf, 1); //Escribimos el byte en el archivo de destino.
                if (err == -1)
                {
                    printf("Error al escribir el fichero de destino.\n");
                    exit(2);
                }
            }
        }
        chmod(argv[2], 0555); //Modificamos los permisos de forma que se ajusten a los requisitos de la expecificación.
    }
    else // En caso de introducir un valor no númerico, se notificará al usuario y se terminará la ejecución.
    {
        printf("Error: Introduce un valor númerico para la posición\n");
        exit(2);
    }
}