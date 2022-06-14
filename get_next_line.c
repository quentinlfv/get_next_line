/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlefevre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:18:53 by qlefevre          #+#    #+#             */
/*   Updated: 2022/06/14 20:27:37 by qlefevre         ###   ########.fr       */
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
char	*new_stash(char *stash, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 255));
	if (!tmp)
		return (NULL);
	while (stash[i])
	{
		tmp[j] = stash[i];
		i++;
		j++;
	}
	tmp[j] = 0;
	while (i != 0)
	{
		stash[i] = 0;
		i--;
	}
	stash[i] = 0;
	while (tmp[i])
	{
		stash[i] = tmp[i];
		i++;
	}
	free(tmp);
	return (stash);
}

char	*stricpy(char *src, char *dest, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

int	check_eol(char *s, char *line)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (ft_strlen(s) == i)
		return (-1);
	else
	{
		stricpy(s, line, i + 1);
		new_stash(s, i + 1);
		return (i);
	}
}

char	*strcat(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = 0;
	return (s1);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 255];
	char		*buf;
	char		*line;
	size_t		size;

	printf("stash : %s\n", stash);
	buf = malloc (sizeof(char) * BUFFER_SIZE);
	line = malloc(sizeof(char) * 255);
	/*if (!stash)
		stash = malloc(sizeof(char) * (BUFFER_SIZE + 255));*/
	if (!buf || !line || !stash)
		return (NULL);
	while (check_eol(stash, line) == -1 && size != 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		strcat(stash, buf);

	}
	if (size == 0)
	{
		//free(stash);
		return (NULL);
	}
	free(buf);
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
	for (int i = 0; i < 4; i++)
	{
		line = get_next_line(fd);
		printf("gnl = %s", line);
	}
	free(line);
	if (close(fd) < 0)
		printf("Error while closing doc");
	else
		printf("closed the doc");
	return (0);
}	
