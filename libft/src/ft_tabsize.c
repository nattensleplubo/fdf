#include "libft.h"

int	ft_tabsize(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s",tab[i]);
		i++;
	}
	return (i);
}