/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oibis <oibis@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:14:10 by oibis             #+#    #+#             */
/*   Updated: 2022/03/02 14:36:49 by oibis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*ft_get_line(char *saved_line)
{
	int		i;
	char	*r_line;

	i = 0;
	if (!saved_line[i])
		return (NULL);
	while (saved_line[i] && saved_line[i] != '\n')
		i++;
	r_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!r_line)
		return (NULL);
	i = 0;
	while (saved_line[i] && saved_line[i] != '\n')
	{
		r_line[i] = saved_line[i];
		i++;
	}
	if (saved_line[i] == '\n')
	{
		r_line[i] = saved_line[i];
		i++;
	}
	r_line[i] = '\0';
	return (r_line);
}

char	*ft_save(char *saved_line)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (saved_line[i] && saved_line[i] != '\n')
		i++;
	if (!saved_line[i])
	{
		free(saved_line);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(saved_line) - i + 1));
	if (!s)
		return (NULL);
	i++;
	j = 0;
	while (saved_line[i])
		s[j++] = saved_line[i++];
	s[j] = '\0';
	free(saved_line);
	return (s);
}

char	*read_save_line(int fd, char *saved_line)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(saved_line, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		saved_line = ft_strjoin(saved_line, buff);
	}
	free(buff);
	return (saved_line);
}

char	*get_next_line(int fd)
{
	char		*r_line;
	static char	*saved_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	saved_line = read_save_line(fd, saved_line);
	if (!saved_line)
		return (NULL);
	r_line = ft_get_line(saved_line);
	saved_line = ft_save(saved_line);
	return (r_line);
}
/*  int main()
{
        int fd = open("asd.text", O_RDONLY);
        int fds = open("qwe.text", O_RDONLY);

        char *s, *s2;
        int i = 0;

        while (i++ < 10)
        {
                s = get_next_line(fd);
                printf(".%s\n", s);
        }



        return (0);
} */