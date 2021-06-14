#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Declaramos antes las funciones para que no aparezca ningun tipo de warning
int wait();
int error();

void main(int argc, char *argv[])
{
    int childid;
    int t;

    if(argc < 3){ //Controlamos que se haya introducido al menos un comando.
        printf("\nIntroduce los comandos a continuacion del modo\n");
        exit(2);
    }

    if (strcmp(argv[1], "C") == 0) // En caso de introducir C como primer parametro, entraremos al modo concurrente.
    {
        t = time(NULL); //Comenzamos a contar el tiempo.

        for (int i = 2; i < argc; i++) // Repeticiones dependiendo del numero de comandos introducidos.
        { 
            if ((fork()) == 0) // Creamos el fork que va a controlar que su hijo, el cual ejecuta el comando termina.
            {
                if ((childid = fork()) == 0) // Creamos el fork que realizara el proceso.
                {
                    execlp(argv[i], argv[i], NULL);
                    error("exec");
                }
                if (wait(NULL) == childid) // Nos aseguramos que el hijo creado anteriormente finaliza como es debido.
                {
                    exit(0);
                }
            }
        }
    }
    else if (strcmp(argv[1], "S") == 0) // En caso de introducir S como primer parametro, accederemos al modo secuencial.
    {
        t = time(NULL); //Comenzamos a contar el tiempo.

        for (int i = 2; i < argc; i++) // Realizamos los bucles necesarios.
        {
            if ((childid = fork()) == 0) // Creamos el fork que realizara el proceso.
            {
                execlp(argv[i], argv[i], NULL);
                error("exec");
            }
            while (wait(NULL) != childid) // En este caso, al necesitar asegurarnos de que ha acabado el primer comando antes de continuar,
            {                             // el padre del mismo, el programa lanzador_cs, es el encargado de hacerlo.
            }
        }
    }
    else
    {
        printf("\nIntroduce un primer caracter valido, S para secuencial o C para concurrente\n"); // Se notifica al usuario en caso de no seleccionar un modo.
        exit(2);
    }

    while (wait(NULL) != -1); // El programa principal, lanzador_cs, esperara a que terminen todos los procesos antes de contabilizar el tiempo,
    t = time(NULL) - t;       //  asegurandonos que todos los procesos han terminado.
    printf("\nEl experimento ha tomado %d segundos\n\n", t);

    exit(0);
}
