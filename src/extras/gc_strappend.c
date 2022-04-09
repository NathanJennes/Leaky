/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:46:20 by njennes           #+#    #+#             */
/*   Updated: 2022/02/16 22:17:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

char	*gc_strappend(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = gc_calloc(len + 2, sizeof(char));
	ft_memmove(new_str, str, len * sizeof (char));
	new_str[len] = c;
	gc_free(str);
	return (new_str);
}
