/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:01:23 by njennes           #+#    #+#             */
/*   Updated: 2022/04/09 20:02:19 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASICS_H
# define BASICS_H

# include <stdio.h>

void		*ft_memset(void *b, int c, size_t len);
void		*ft_memseti(void *b, int c, size_t len);
void		*ft_memsetf(void *b, float c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t		ft_strlen(const char *s);;

#endif
