/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhdeeb <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:59:56 by mhdeeb            #+#    #+#             */
/*   Updated: 2025/08/27 22:01:02 by mhdeeb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_append(int fd, char *stash, char *buf)
{
	ssize_t	bytes;

	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes == -1)
	{
		free(buf);
		free(stash);
		return (NULL);
	}
	buf[bytes] = '\0';
	stash = ft_strjoin(stash, buf);
	if (!stash)
	{
		free(buf);
		return (NULL);
	}
	return (stash);
}

static char	*read_until_newline(int fd, char *stash)
{
	char	*buf;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_strchr(stash, '\n'))
	{
		stash = read_and_append(fd, stash, buf);
		if (!stash)
			return (NULL);
		if (ft_strlen(buf) == 0)
			break ;
	}
	free(buf);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char		*line;
	size_t		i;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (i-- > 0)
		line[i] = stash[i];
	return (line);
}

static char	*trim_stash(char *stash)
{
	char	*new_stash;
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(stash + i + 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_until_newline(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = trim_stash(stash);
	return (line);
}
