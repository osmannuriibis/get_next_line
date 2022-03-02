/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oibis <oibis@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:15:21 by oibis             #+#    #+#             */
/*   Updated: 2022/03/02 14:26:00 by oibis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *save_line)
{
	int		i;
	char	*s;

	i = 0;
	if (!save_line[i])
		return (NULL);
	while (save_line[i] && save_line[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (save_line[i] && save_line[i] != '\n')
	{
		s[i] = save_line[i];
		i++;
	}
	if (save_line[i] == '\n')
	{
		s[i] = save_line[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_save(char *save_line)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (save_line[i] && save_line[i] != '\n')
		i++;
	if (!save_line[i])
	{
		free(save_line);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(save_line) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (save_line[i])
		s[j++] = save_line[i++];
	s[j] = '\0';
	free(save_line);
	return (s);
}

char	*read_save_line(int fd, char *save_line)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(save_line, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		save_line = ft_strjoin(save_line, buff);
	}
	free(buff);
	return (save_line);
}

char	*get_next_line(int fd)
{
	char		*r_line;
	static char	*save_line[257];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (0);
	save_line[fd] = read_save_line(fd, save_line[fd]);
	if (!save_line[fd])
		return (NULL);
	r_line = ft_get_line(save_line[fd]);
	save_line[fd] = ft_save(save_line[fd]);
	return (r_line);
}
