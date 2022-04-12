/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2022/04/11 14:51:56 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

void	gc_strarray_free(char **array)
{
	size_t	i;
	size_t	size;

	if (!array)
		return ;
	size = gc_strarray_size(array);
	i = 0;
	while (i < size)
	{
		gc_free(array[i]);
		i++;
	}
	gc_free(array[i]);
	gc_free(array);
}
