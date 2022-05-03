/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:43:34 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 14:29:29 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "src/core/core.h"

#ifdef DEBUG
static void	print_ptr_childs(t_ptr ptr);
#endif

int	gc_failed(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->last_error)
		return (1);
	return (0);
}

#ifdef DEBUG
void	gc_print_status(void)
{
	size_t	i;
	t_gc	*allocator;

	allocator = gc_get();
	i = 0;
	printf("[LEAKY DEBUG]:\tallocator status:---------------------\n");
	while (i < allocator->capacity)
	{
		if (!allocator->pointers[i].address)
		{
			i++;
			continue ;
		}
		printf("\n[PTR %lu]:\t--%p--\n", i, allocator->pointers[i].address);
		if (allocator->pointers[i].address)
		{
			printf("\tTemporary:\t%d\n", (int)allocator->pointers[i].temporary);
			printf("\tScope:\t%lu\n", allocator->pointers[i].scope);
		}
		if (allocator->pointers[i].child_capacity)
			print_ptr_childs(allocator->pointers[i]);
		i++;
	}
	printf("-------------------------------------------------------\n");
}

static void	print_ptr_childs(t_ptr ptr)
{
	size_t	i;
	t_gc	*allocator;

	allocator = gc_get();
	i = 0;
	printf("\tChilds:\n");
	while (i < ptr.child_capacity)
	{
		if (ptr.childs[i])
			printf("\t\t[%lu]:\t%p\n", i, ptr.childs[i]->address);
		i++;
	}
}
#endif

const char	*gc_get_last_error(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	return (allocator->last_error);
}

const char	**gc_get_errors(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	return ((const char **)(allocator->errors));
}
