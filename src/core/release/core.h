/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:43:00 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 18:21:30 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <stddef.h>
# include <stdint.h>

# define SCOPE_START 1
# define SCOPE_END -1

typedef struct s_ptr
{
	void			*address;
	char			temporary;
	size_t			scope;
	int64_t			*childs;
	size_t			child_capacity;
	size_t			child_count;
	int64_t			*parents;
	size_t			parent_capacity;
	size_t			parent_count;
}					t_ptr;

typedef struct s_gc
{
	void		*new_ptr;
	int64_t		current_parent;
	t_ptr		*pointers;
	int64_t		ptrs_count;
	int64_t		capacity;
	int64_t		first_free;
	size_t		malloc_calls;
	size_t		current_scope;
	int			(*callback)(void *);
	void		*param;
	const char	*last_error;
	char		**errors;
	int			clean_on_error;
}			t_gc;

t_gc		*gc_get(void);
t_ptr		*gc_ptr(int64_t index);

int			gc_init(t_gc *gc, int (*callback)(void *),
				void *param);

int			gc_grow(void);
int			gc_must_grow(void);

void		*gc_ialloc(size_t size);
void		*gc_icalloc(size_t count, size_t size);
int			gc_iown(void *ptr);
char		*gc_istrdup(const char *s1);

int			gc_add_child(int64_t ptr, int64_t child);
int			gc_remove_child(int64_t ptr, int64_t child);

int			gc_error(const char *msg);
int			can_change_settings(void);

t_ptr		gc_null_ptr(void);
int64_t		gc_get_internal_ptr(void *ptr);
int			gc_contains_ptr(void *ptr);
int64_t		gc_get_current_parent(void);
int			gc_has_global_parent(void);
int			gc_is_valid_ptr_index(int64_t index);

t_ptr		gc_create_generic_ptr(void *address);
t_ptr		gc_create_temporary_ptr(void *address);
t_ptr		gc_create_internal_ptr(void *address);

#endif
