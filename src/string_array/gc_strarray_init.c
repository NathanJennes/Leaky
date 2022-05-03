/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2022/04/18 15:24:33 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"
#include "src/core/release/core.h"

char	**gc_strarray_init(void)
{
	char	**array;

	array = gc_calloc(1, sizeof (char *));
	return (array);
}

char	**gct_strarray_init(void)
{
	char	**array;

	array = gct_calloc(1, sizeof(char *));
	return (array);
}

char	**gc_istrarray_init(void)
{
	char	**array;

	array = gc_icalloc(1, sizeof(char *));
	return (array);
}
