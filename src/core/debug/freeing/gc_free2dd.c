/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free2dd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:04:34 by njennes           #+#    #+#             */
/*   Updated: 2022/05/16 15:05:15 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

void	gc_free2d(void **ptr, size_t size)
{
	if (!ptr)
		return ;
	while (size)
	{
		gc_free(ptr[size - 1]);
		size--;
	}
	gc_free(ptr);
}
