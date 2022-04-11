/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:39:01 by njennes           #+#    #+#             */
/*   Updated: 2022/04/11 14:39:57 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

t_ptr	gc_null_ptr(void)
{
	t_ptr	new;

	ft_memset(&new, 0, sizeof (t_ptr));
	return (new);
}
