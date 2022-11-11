/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 21:18:27 by kkohki            #+#    #+#             */
/*   Updated: 2021/12/13 20:22:16 by kkohki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_getline(int fd, char *save)
{
	char	*buff;
	ssize_t	read_fd;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_fd = 1;
	while (!ft_strchr(save, '\n') && read_fd != 0)
	{
		read_fd = read(fd, buff, BUFFER_SIZE);
		if (read_fd == READ_ERROR)
		{
			free(buff);
			return (NULL);
		}
		buff[read_fd] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}

static char	*ft_line(char *save)
{
	size_t	i;

	i = 0;
	if (!save[0])
		return (NULL);
	while (save[i] != '\n' && save[i])
		i++;
	return (ft_substr(save, 0, i + 1));
}

static char	*ft_save(char *save)
{
	size_t	i;
	char	*str;

	if (!save)
		return (NULL);
	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
		{
			str = ft_substr(save, i + 1, ft_strlen(save));
			free(save);
			return (str);
		}
		i++;
	}
	free (save);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || INT_MAX <= BUFFER_SIZE
		|| OPEN_MAX <= fd)
		return (NULL);
	save[fd] = ft_getline(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_line(save[fd]);
	save[fd] = ft_save(save[fd]);
	return (line);
}
