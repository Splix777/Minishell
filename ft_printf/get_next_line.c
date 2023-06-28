/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsalazar <fsalazar@student.42madrid.com:>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:02:07 by fsalazar          #+#    #+#             */
/*   Updated: 2023/03/24 13:03:30 by fsalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_read_and_save(int fd, char *save)
{
	char	*buffer;
	int		bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!gnl_strchr(save, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(save);
			return (NULL);
		}
		buffer[bytes] = '\0';
		save = gnl_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*read_line(char *save)
{
	int		i;
	char	*temp;

	i = 0;
	if (save[i] == '\0' || !save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	temp = malloc((i + 2) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		temp[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		temp[i] = save[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*new_save(char *save)
{
	int		i;
	int		index;
	char	*new;

	index = 0;
	while (save[index] && save[index] != '\n')
		index++;
	if (save[index] == '\0')
	{
		free(save);
		return (NULL);
	}
	new = malloc((gnl_strlen(save) - index + 1) * sizeof(char));
	if (!new)
		return (NULL);
	index++;
	i = 0;
	while (save[index])
		new[i++] = save[index++];
	new[i] = '\0';
	free(save);
	if (new[0] != '\0')
		return (new);
	free(new);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read_and_save(fd, save);
	if (!save)
		return (NULL);
	line = read_line(save);
	save = new_save(save);
	return (line);
}
