#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char		long_max[] = "9223372036854775808";
	int			i;

	i = 0;
	while (long_max[i])
		i++;
	printf("%d\n", i);
	return (0);
}