/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 02:12:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/10 17:22:37 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_calloc(size_t size)
{
	size_t	i;
	char	*src;

	i = 0;
	src = malloc(size);
	if (src == NULL)
		return (free(src), src = NULL, NULL);
	while (i < size)
	{
		src[i] = '\0';
		i++;
	}
	return (src);
}
