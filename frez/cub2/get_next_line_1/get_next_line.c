/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:30:16 by rel-mora          #+#    #+#             */
/*   Updated: 2024/11/05 20:59:23 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_hold_line(char *hold_line)
{
	int		i;
	int		j;
	char	*final_line;

	i = 0;
	j = 0;
	if (hold_line == NULL || !(*hold_line))
		return (NULL);
	while (hold_line[i] && hold_line[i] != '\n')
		i++;
	final_line = ft_calloc(i + 2);
	if (!final_line)
		return (free(final_line), NULL);
	i = 0;
	while (hold_line[i] && hold_line[i] != '\n')
		final_line[j++] = hold_line[i++];
	if (hold_line[i] == '\n')
		final_line[j++] = hold_line[i];
	final_line[j] = '\0';
	return (final_line);
}

char	*ft_rest_buf(char *hold_line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (hold_line[i] && hold_line[i] != '\n')
		i++;
	if (!hold_line[i])
		return (free(hold_line), NULL);
	str = ft_calloc((len(hold_line) - i + 1));
	if (!str)
		return (free(str), NULL);
	i++;
	j = 0;
	while (hold_line[i])
		str[j++] = hold_line[i++];
	str[j] = '\0';
	free(hold_line);
	return (str);
}

ssize_t	ft_read(char *buf, int fd, ssize_t *result_read)
{
	*result_read = read(fd, buf, BUFFER_SIZE);
	if (*result_read == -1)
		return (free(buf), buf = NULL, 0);
	buf[*result_read] = '\0';
	return (*result_read);
}

char	*get_next_line(int fd)
{
	static char	*hold_line;
	char		*buf;
	char		*final_line;
	ssize_t		result_read;

	if (fd < 0 || read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
	{
		free(hold_line);
		hold_line = NULL;
		return (NULL);
	}
	result_read = 1;
	buf = ft_calloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (ft_check(hold_line) == 0 && result_read > 0)
	{
		result_read = ft_read(buf, fd, &result_read);
		hold_line = join(hold_line, buf);
	}
	free(buf);
	final_line = ft_hold_line(hold_line);
	hold_line = ft_rest_buf(hold_line);
	return (final_line);
}
