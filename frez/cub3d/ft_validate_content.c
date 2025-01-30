/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:41:14 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/18 16:35:54 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_check_file(char *av)
{
	size_t	len;

	len = ft_strlen(av) - 1;
	if (av[len] != 'b')
		return (0);
	len--;
	if (av[len] != 'u')
		return (0);
	len--;
	if (av[len] != 'c')
		return (0);
	len--;
	if (av[len] != '.')
		return (0);
	return (1);
}

int	check_empt_line_map(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] && str[i + 1] == '\n')
		{
			free(str);
			return (1);
		}
		i++;
	}
	return (0);
}
int	check_empty_line(char *joined)
{
	char	*str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	str = ft_strtrim(joined, "\n");
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\n' && count < 7)
			i++;
		if (str[i] != '\n' && count < 7)
		{
			while (str[i] && str[i] != '\n')
				i++;
			if (str[i] && str[i] == '\n')
				count++;
		}
		if (count == 7)
			break ;
	}
	if (check_empt_line_map(str, i))
		return (1);
	free(str);
	return (0);
}
char	**ft_fill_content(char **content, char *av)
{
	int		fd;
	char	*line;
	char	*joined;

	joined = NULL;
	line = NULL;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		ft_just_print_error("Error: Failed to open the file\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		joined = ft_strjoin(joined, line);
		line = get_next_line(fd);
	}
	free(line);
	content = ft_split(joined, '\n');
	if (check_empty_line(joined) || !content)
	{
		ft_put_error("Error: emply line.\n", NULL, NULL);
		free(joined);
		free_double(content);
	}
	free(joined);
	return (content);
}

void	ft_validate(char *av, t_start *var)
{
	if (ft_check_file(av))
	{
		var->content = ft_fill_content(var->content, av);
		fill_config(var);
		fill_map(var);
	}
	else
		ft_just_print_error("Error: There is no file with the extension .cub.\n");
}