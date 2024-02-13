/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 00:15:17 by ngobert           #+#    #+#             */
/*   Updated: 2024/02/13 14:54:37 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	**ft_cpy_int_tab(int **tab, int rows, int cols)
{
	int **ret;
	int i;
	int j;

	ret = (int **)malloc(sizeof(int *) * rows);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		ret[i] = (int *)malloc(sizeof(int) * cols);
		if (!ret[i])
			return (NULL);
		j = 0;
		while (j < cols)
		{
			ret[i][j] = tab[i][j];
			j++;
		}
		i++;
	}
	return (ret);
}