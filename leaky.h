/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaky.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:19:41 by njennes           #+#    #+#             */
/*   Updated: 2022/04/09 14:38:52 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAKY_H
# define LEAKY_H

# include <stddef.h>

# define BUFFER_SIZE 50

# define GC_GET 1
# define GC_SET_CALLBACK 2
# define GC_SET_CALLBACK_PARAM 3

typedef struct s_gc
{
	void	**pointers;
	size_t	ptrs_count;
	size_t	capacity;
	size_t	first_free;
	int		(*callback)(void *);
	void	*param;
}			t_gc;

//Basic memory interface
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memseti(void *b, int c, size_t len);
void		*ft_memsetf(void *b, float c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

//Memory management
t_gc		*gc(int mode, void *param);
void		gc_init(t_gc *gc, int (*callback)(void *), void *param);
void		*gc_calloc(size_t count, size_t size);
void		gc_clean();
void		gc_destroy(void **ptr);
void		gc_free(void *ptr);

char		*gc_get_next_line(int fd);
char		*gc_itoa(int n);
char		**gc_split(char const *s, char c);
void		gc_split_free(char **tab);
char		*gc_strappend(char *str, char c);
char		*gc_strdup(const char *s1);
char		*gc_strjoin(char *s1, char *s2, int to_free);
char		*gc_substr(char const *s, unsigned int start, size_t len);

char		**gc_strarray_init();
char		**gc_strarray_append(char **array, char *str);
char		*gc_strarray_asstr(char **array);
void		gc_strarray_free(char **array);
char		**gc_strarray_from(char **other, size_t size);
char		**gc_strarray_fromstr(char *str);
size_t		gc_strarray_size(char **array);


int			gc_getfootprint();


size_t		ft_strlen(const char *s);

#endif
