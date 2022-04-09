/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:13:03 by njennes           #+#    #+#             */
/*   Updated: 2022/04/09 14:22:16 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*new;

	new = malloc(count * size);
	if (!new)
		return (NULL);
	ft_memset(new, 0, count * size);
	return (new);
}
