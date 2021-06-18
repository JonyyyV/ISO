#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

// Declaramos antes las funciones para que no aparezca ningun tipo de warning
int wait();
int error();
int mkfifo();

void main(int argc, char *argv[])
{
    int pid;
    if (mkfifo("my_fifo", 0644) == -1)
        error("mkfifo");
    switch (pid = fork())
    {
    case -1:
        error("fork");
    case 0:
        if (close(1) == -1)
            error("close");
        if (open("my_fifo", O_WRONLY) != 1)
            error("open");
        execlp("last", "last", NULL);
        error("execlp");
    }

    switch (pid = fork())
    {
    case -1:
        error("fork");
    case 0:
        if (close(0) == -1)
            error("close");
        if (open("my_fifo", O_RDONLY) != 0)
            error("open");
        execlp("grep", "grep", "acaf00", "-c", NULL);
        error("execlp");
    }

    while ((pid = wait(NULL)) != -1)
        unlink("my_fifo");
    exit(0);
}