/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anayef <anayef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:03:16 by anayef            #+#    #+#             */
/*   Updated: 2023/02/25 18:38:26 by anayef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_line(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i ++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *store)
{
	char	*buffer;
	int		buffer_l;

	if (!store)
		store = ft_calloc(1, 1);
	buffer = ft_calloc((size_t)BUFFER_SIZE + 1, sizeof(char));
	buffer_l = 1;
	while (buffer_l > 0)
	{
		buffer_l = read(fd, buffer, BUFFER_SIZE);
		if (buffer_l == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[buffer_l] = 0;
		store = join_line(store, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0
		|| BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}

/* #include <stdio.h>
#include <fcntl.h>

 int main()
{
	int fd1;
	fd1 = open("test1.txt", O_RDONLY | O_CREAT);
	//fd2 = open("test2.txt", O_RDONLY | O_CREAT);
	//fd3 = open("test3.txt", O_RDONLY | O_CREAT);
	char *line;
	line = get_next_line(fd1);
	while(line)
	{
		printf("%s", line);
		free (line);
		line = get_next_line(fd1);
	}
}
 */
