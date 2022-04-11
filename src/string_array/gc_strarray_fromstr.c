/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_fromstr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2022/04/11 14:54:19 by njennes          ###   ########.fr       */
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

char	**gct_strarray_fromstr(char *str)
{
	char	**array;

	array = gct_strarray_init();
	if (!str)
		return (array);
	array = gct_strarray_append(array, str);
	return (array);
}
