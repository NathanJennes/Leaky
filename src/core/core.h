/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:43:00 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 19:25:02 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <stddef.h>

# define SCOPE_START 1
# define SCOPE_END -1

typedef struct s_ptr
{
	void	*address;
	char	temporary;
	size_t	scope;
}			t_ptr;

typedef struct s_gc
{
	void		*new_ptr;
	t_ptr		*pointers;
	size_t		ptrs_count;
	size_t		capacity;
	size_t		first_free;
	size_t		malloc_calls;
	size_t		current_scope;
	int			(*callback)(void *);
	void		*param;
	const char	*error;
	int			clean_on_error;
}			t_gc;

t_gc		*gc_get(void);

int			gc_init(t_gc *gc, int (*callback)(void *),
				void *param);

int			gc_grow(void);
int			gc_must_grow(void);

int			gc_error(const char *msg);

t_ptr		gc_null_ptr(void);
int			gc_contains_ptr(void *ptr);

#endif
