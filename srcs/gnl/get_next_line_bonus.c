/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:56:00 by ngobert           #+#    #+#             */
/*   Updated: 2021/12/02 12:56:32 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line_bonus.h"

int	check_eol(char *statique)
{
	int	i;

	i = 0;
	if (!statique)
		return (0);
	while (statique[i])
	{
		if (statique[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_returnline(char	*statique)
{
	int		i;
	char	*returnline;

	i = 0;
	if (!statique || !statique[0])
		return (NULL);
	while (statique[i] && statique[i] != '\n')
		i++;
	i += ft_check_nl(&statique[i]);
	returnline = malloc(sizeof(char) * (i + 1));
	if (!returnline)
		return (NULL);
	i = 0;
	while (statique[i] && statique[i] != '\n')
	{
		returnline[i] = statique[i];
		i++;
	}
	if (statique[i] == '\n')
	{
		returnline[i] = statique[i];
		i++;
	}
	returnline[i] = '\0';
	return (returnline);
}

char	*ft_new_static(char *statique)
{
	char	*new_static;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (statique == NULL)
		return (NULL);
	while (statique[i] && statique[i] != '\n')
		i++;
	if (statique[i] == '\0')
		return (ft_free(statique));
	i += ft_check_nl(&statique[i]);
	new_static = malloc(sizeof(char) * (ft_strlen(statique) - i + 1));
	if (!new_static)
		return (NULL);
	while (statique[i])
		new_static[j++] = statique[i++];
	new_static[j] = '\0';
	free(statique);
	statique = NULL;
	return (new_static);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*statique[FOPEN_MAX];
	char		*line;
	int			ret_val;

	ret_val = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!check_eol(statique[fd]) && ret_val != 0)
	{
		ret_val = read(fd, buffer, BUFFER_SIZE);
		if (ret_val == -1)
			return (ft_free(buffer));
		buffer[ret_val] = '\0';
		statique[fd] = ft_strjoin(statique[fd], buffer);
	}
	free(buffer);
	line = ft_returnline(statique[fd]);
	statique[fd] = ft_new_static(statique[fd]);
	return (line);
}
