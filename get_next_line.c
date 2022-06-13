/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:18:53 by qlefevre          #+#    #+#             */
/*   Updated: 2022/06/13 17:15:36 by qlefevre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*stricpy(char *src, char *dest, int i)
{
	int	j;

	j = 0;
	printf("i vaut %d\n", i);
	while (src[i])
	{
		dest[j] = src[i];
		src[i] = 0;
		j++;
		i++;
	}
	dest[j] = 0;
	printf("dest : %s\n", dest);
	return (dest);
}

int	check_eol(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (ft_strlen(s) == i)
		return (-1);
	else
		return (i);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buf;
	char		*line;
	size_t		size;

	buf = malloc (sizeof(char) * BUFFER_SIZE);
	line = malloc(sizeof(char) * 25);
	stash = malloc(sizeof(char) * 40);
	while (check_eol(line) == -1 && size != 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		printf("line : %s\n", line);
	}
	if (check_eol(line) != -1)
		stricpy(line, stash, check_eol(line));
	return (line);
}

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error while oppening doc");
		return (0);
	}
	printf("the file descp is %d\n", fd);
	line = get_next_line(fd);
	printf("gnl = %s\n", line);
	line = get_next_line(fd);
	printf("gnl = %s\n", line);
	if (close(fd) < 0)
		printf("Error while closing doc");
	else
		printf("closed the doc");
	return (0);
}	
