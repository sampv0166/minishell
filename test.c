#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int increment_i(int *i)
{
    *i = *i + 1;
    return (*i);
}

int main(void)
{
    int fd[2];
    char buf[3];
    pipe(fd);
    
    pid_t pid;

    pid = fork();
    char *ar[] = {"ls", "-la"};
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO); 
        printf("ok");
        close(fd[1]); 
    }
    else
    {
        close(fd[1]);
        read(fd[0],buf,2);
    }
     //close(fd[1]);
    close(fd[0]);
    printf("%s",buf);
    return 0;
}