/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_destroyd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:33:45 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 17:34:41 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/cored.h"
#include "leaky.h"

void	gc_destroy(void **ptr)
{
	if (!ptr)
		return ;
	gc_free(*ptr);
	*ptr = NULL;
}
