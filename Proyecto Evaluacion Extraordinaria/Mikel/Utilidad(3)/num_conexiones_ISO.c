#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// Declaramos antes las funciones para que no aparezca ningun tipo de warning.
int wait();
int error();
int mkfifo();

void main(int argc, char *argv[])
{
    int pid;
    if (mkfifo("my_fifo", 0644) == -1) //Creamos la tuberia con nombre que vamos a utilizar.
        error("mkfifo");

    switch (pid = fork()) //Creamos el fork que realizará el last.
    {
        case -1:
            error("fork");
        case 0:
            if (close(1) == -1) //Cerramos la salida estandar del fork.
                error("close");
            if (open("my_fifo", O_WRONLY) != 1) //Abrimos la entrada estandar de la tuberia.
                error("open");
            execlp("last", "last", NULL); //Ejecutamos el comando last mediante la funcion execlp, sabiendo que escribirá en la entrada de la tuberia.
            error("execlp");
    }

    switch (pid = fork()) //Creamos el fork que realizará el conteo.
    {
        case -1:
            error("fork");
        case 0:
            if (close(0) == -1) //Cerramos la entrada estandar del fork.
                error("close");
            if (open("my_fifo", O_RDONLY) != 0)
                error("open");
            execlp("grep", "grep", "acaf00", "-c", NULL); //Ejecutamos el comando last mediante la funcion execlp, sabiendo que leerá de la salida de la tuberia.
            error("execlp");
    }

    while ((pid = wait(NULL)) != -1) //Esperamos a que todos los procesos hijos terminen
        unlink("my_fifo"); //Cerramos la tuberia y salimos satisfactoriamente

    exit(0);
}