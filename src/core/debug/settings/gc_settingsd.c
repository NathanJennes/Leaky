/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_settingsd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 19:07:26 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:29:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "src/core/debug/cored.h"
#include "leaky.h"

void	gc_set_callback(int (*callback)(void *))
{
	t_gc	*allocator;

	if (!can_change_settings())
		return ;
	allocator = gc_get();
	allocator->callback = callback;
}

void	gc_set_callback_param(void *param)
{
	t_gc	*allocator;

	allocator = gc_get();
	allocator->param = param;
}

void	gc_clean_on_error(int clean_on_error)
{
	t_gc	*allocator;

	if (!can_change_settings())
		return ;
	allocator = gc_get();
	allocator->clean_on_error = clean_on_error;
}

void	gc_set_default_capacity(size_t capacity)
{
	t_gc	*allocator;

	if (!can_change_settings())
		return ;
	allocator = gc_get();
	if (allocator->ptrs_count)
		return ;
	if (capacity == 0)
		allocator->capacity = 1;
	else
		allocator->capacity = capacity;
	free(allocator->pointers);
	allocator->pointers = ft_calloc(allocator->capacity, sizeof(t_ptr));
	if (!allocator->pointers)
		gc_error(gc_error_allocation());
}

void	gc_ignore_warnings(int ignore_warnings)
{
	t_gc	*allocator;

	if (!can_change_settings())
		return ;
	allocator = gc_get();
	allocator->ignore_warnings = ignore_warnings;
}
