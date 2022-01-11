#include "../includes/mini_shell.h"

int cd(char *path) 
{
    return chdir(path);
}

int pwd(char *path)
{
    if (getenv("PATH"))
        return (1);
    return (0);
}