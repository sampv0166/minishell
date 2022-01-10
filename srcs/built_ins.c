#include "../includes/mini_shell.h"

int cd(char *path) 
{
    return chdir(path);
}