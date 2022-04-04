#include "../../includes/mini_shell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;
	i = 0;
	while (s && s[i] != '\0')
	{
		i++;
	}
	return (i);
}


char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*ptr;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1 && s1[j])
	{
		ptr[i] = s1[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
    free( (void *)s1);
	return (ptr);
}


void allocate(t_parser_info *pa_info)
{
    pa_info->arr1[0] = ft_strdup("ss");
}

int main ()
{   
    t_parser_info pa_info;

    pa_info.arr1 = malloc (sizeof(char) * 1);
    allocate(&pa_info);
    free(pa_info.arr1);
}