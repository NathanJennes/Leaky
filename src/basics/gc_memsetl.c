/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_memsetl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:31:01 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 15:32:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>

void	*gc_memsetl(void *b, int64_t c, size_t len)
{
	size_t	i;
	int64_t	*bcpy;

	bcpy = b;
	i = 0;
	while (i < len)
	{
		bcpy[i] = c;
		i++;
	}
	return (b);
}
