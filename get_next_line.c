/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:03:20 by hherba            #+#    #+#             */
/*   Updated: 2022/02/28 20:18:18 by hherba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *str)
{
	char	*curr_line;
	int		buff_byte;

	curr_line = malloc(BUFFER_SIZE + 1);
	if (!curr_line)
		return (NULL);
	while (!ft_strchr(str, '\n'))
	{
		buff_byte = read(fd, curr_line, BUFFER_SIZE);
		if (buff_byte == 0)
			break ;
		if (buff_byte == -1)
		{
			free(curr_line);
			free(str);
			return (NULL);
		}
		curr_line[buff_byte] = '\0';
		str = ft_strjoin(str, curr_line);
	}
	free (curr_line);
	return (str);
}

char	*ft_get_line(char	*str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i += 1;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_get_rest_line(char *str)
{
	size_t		i;
	int			j;
	char		*line;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == 0 || (str[i] == '\n' && str[i + 1] == 0))
	{
		free(str);
		return (NULL);
	}
	line = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!line)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (str[i] != '\0')
		line[j++] = str[i++];
	line[j] = '\0';
	free (str);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read (fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_get_rest_line (str);
	return (line);
}
