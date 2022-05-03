/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:43:00 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 14:14:12 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include <stddef.h>

# define SCOPE_START 1
# define SCOPE_END -1

# define LK_MAX_ERRORS 1000

typedef struct s_ptr
{
	void			*address;
	char			temporary;
	size_t			scope;
	struct s_ptr	**childs;
	size_t			child_capacity;
	size_t			child_count;
}					t_ptr;

typedef struct s_gc
{
	void		*new_ptr;
	t_ptr		*current_parent;
	t_ptr		*pointers;
	size_t		ptrs_count;
	size_t		capacity;
	size_t		first_free;
	size_t		malloc_calls;
	size_t		current_scope;
	int			(*callback)(void *);
	void		*param;
	const char	*last_error;
	char		**errors;
	int			clean_on_error;
	int			ignore_warnings;
}			t_gc;

t_gc		*gc_get(void);

int			gc_init(t_gc *gc, int (*callback)(void *),
				void *param);

int			gc_grow(void);
int			gc_must_grow(void);

void		*gc_ialloc(size_t size);
void		*gc_icalloc(size_t count, size_t size);
int			gc_iown(void *ptr);
char		*gc_istrdup(const char *s1);
char		**gc_istrarray_append(char **array, const char *str);
char		**gc_istrarray_init(void);

int			gc_add_child(t_ptr *ptr, t_ptr *child);
int			gc_remove_child(t_ptr *ptr, t_ptr *child);

int			gc_error(const char *msg);
int			gc_add_error(const char *msg);
int			can_change_settings(void);

t_ptr		gc_null_ptr(void);
t_ptr		*gc_get_internal_ptr(void *ptr);
int			gc_contains_ptr(void *ptr);
size_t		gc_get_internal_ptr_index(t_ptr *ptr);

#endif
