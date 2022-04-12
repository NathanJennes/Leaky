/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 16:28:31 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

char	*gc_strappend(char *str, char c, int free_old_str)
{
	size_t	len;
	char	*new_str;

	len = gc_strlen(str);
	new_str = gc_calloc(len + 2, sizeof(char));
	gc_memmove(new_str, str, len * sizeof(char));
	new_str[len] = c;
	if (free_old_str)
		gc_free(str);
	return (new_str);
}
