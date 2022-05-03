/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:37:30 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 17:24:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "core.h"

static void	print_ptr_childs(t_ptr ptr);

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
