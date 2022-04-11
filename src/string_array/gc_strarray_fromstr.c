/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_fromstr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2022/04/04 15:52:57 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

char	**gc_strarray_fromstr(char *str)
{
	char	**array;

	array = gc_strarray_init();
	if (!str)
		return (array);
	array = gc_strarray_append(array, str);
	return (array);
}

char	**gc_strarray_fromstrt(char *str)
{
	char	**array;

	array = gc_strarray_initt();
	if (!str)
		return (array);
	array = gc_strarray_appendt(array, str);
	return (array);
}
