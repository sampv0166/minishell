int main ()
{
	int i;
	int j;
	i = 3;

	while (i)
	{
		j = fork();
		if(j == 0)
		{
			return (0);
		}
		i--;
	}
}