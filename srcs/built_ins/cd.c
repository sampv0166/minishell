#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{

	char	s[1000];
	
	printf("%s\n", getcwd(s, 100));
	printf("%d\n", chdir("..s"));
	// if (!chdir("..s"))
	// 	printf("%s\n", getcwd(s, 100));
	return (0);
}