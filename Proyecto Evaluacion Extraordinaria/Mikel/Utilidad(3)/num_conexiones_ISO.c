#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void main(int argc, char *argv[])
{
    int pid;
    if (mkfifo("my_fifo", 0644) == -1)
        error("mkfifo");
    printf("parent: fifo created\n");
    switch (pid = fork())
    {
    case -1:
        error("fork");
    case 0: /* 1st child process: who */
        printf("1st child process created\n");
        if (close(1) == -1)
            error("close");
        if (open("my_fifo", O_WRONLY) != 1)
            error("open");
        execlp("last", "last", NULL);
        error("execlp");
    }
    printf("parent: who(%d) process launched\n", pid);

    switch (pid = fork())
    {
    case -1:
        error("fork");
    case 0: /* 2nd child process: wc -l */
        printf("2nd child process created\n");
        if (close(0) == -1)
            error("close");
        if (open("my_fifo", O_RDONLY) != 0)
            error("open");
        execlp("grep", "grep", "jony","-c", NULL);
        error("execlp");
    }
    printf("parent: wc(%d) process launched\n", pid);
    while ((pid = wait(NULL)) != -1)
        printf("parent: %d process finished\n", pid);
    unlink("my_fifo");
    printf("parent: fifo removed\n");
    exit(0);
}