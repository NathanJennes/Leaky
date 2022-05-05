/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_debugd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:37:30 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 12:40:39 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cored.h"

static void	print_ptr_childs(t_ptr ptr);
static void	print_ptr_parents(t_ptr ptr);

void	gc_print_status(void)
{
	int64_t	i;
	t_gc	*allocator;

	allocator = gc_get();
	i = 0;
	printf("[LEAKY DEBUG]:\tallocator status:---------------------\n");
	while (i < allocator->capacity)
	{
		if (!allocator->pointers[i].address || allocator->pointers[i].internal)
		{
			i++;
			continue ;
		}
		printf("\n[PTR %lld]:\t--%p--\n", i, allocator->pointers[i].address);
		if (allocator->pointers[i].address)
		{
			printf("\tTemporary:\t%d\n", (int)allocator->pointers[i].temporary);
			printf("\tScope:\t%lu\n", allocator->pointers[i].scope);
		}
		print_ptr_childs(allocator->pointers[i]);
		print_ptr_parents(allocator->pointers[i]);
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
		if (ptr.childs[i] != -1)
			printf("\t\t[%lu]:\t%p\n", i,
				allocator->pointers[ptr.childs[i]].address);
		i++;
	}
}

static void	print_ptr_parents(t_ptr ptr)
{
	size_t	i;
	t_gc	*allocator;

	allocator = gc_get();
	i = 0;
	printf("\tParents:\n");
	while (i < ptr.parent_capacity)
	{
		if (ptr.parents[i] != -1)
			printf("\t\t[%lu]:\t%p\n", i,
				allocator->pointers[ptr.parents[i]].address);
		i++;
	}
}
