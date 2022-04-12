/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaky.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:19:41 by njennes           #+#    #+#             */
/*   Updated: 2022/04/09 20:55:08 by njennes          ###   ########.fr       */
/*   Updated: 2022/04/11 14:58:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAKY_H
# define LEAKY_H

# include <stddef.h>

# define BUFFER_SIZE 50

# define GC_GET 1
# define GC_SET_CALLBACK 2
# define GC_SET_CALLBACK_PARAM 3

# define FREE_NONE 0
# define FREE_FIRST 1
# define FREE_SECOND 2
# define FREE_BOTH 3

# define LEAKY_ERROR_ALLOCATION "Leaky: Allocation error!"
# define LEAKY_ERROR_SCOPE_OVERFLOW \
"Leaky: scope overflow! (Do you have a gc_scope_start() inside a while() ?)"
# define LEAKY_ERROR_SCOPE_UNDERFLOW \
"Leaky: scope underflow! (Do you have a gc_scope_end() inside a while() ?)"

typedef struct s_gc t_gc;

//----IMPORTANT----
//  Any pointer allocated by gc_*() MUST be freed by gc_free()/gc_destroy()/gc_clean().
//  Otherwise, double free might occur.
//  Best practice is to only use gc_* functions.
//----

//--Core--

//----
//  Interface for setting up the garbage collector.
//--
//  gc(GC_SET_CALLBACK, your_callback_function) to set allocation error callback.
//    This function must return an int and take a pointer as parameter.
//    It will be called upon any allocation error.
//    It is recommended to save/free all system resources, call gc_clean() and exit your program in your callback.
//--
//  gc(GC_SET_CALLBACK_PARAM, your param) to set the parameter that will be passed to the callback.
//----
t_gc		*gc(int mode, void *param);

//----
//  Works like malloc().
//--
//  A pointer allocated with gc_alloc() MUST be freed by gc_free()/gc_destroy()/gc_clean().
//---
void		*gc_alloc(size_t size);

//----
//  Takes a pointer allocated outside the garbage collector and adds it to the list of managed pointers
//  so that it can be freed by gc_free()/gc_destroy()/gc_clean().
//  If an error occurs during the transfer, the pointer will be freed.
//----
int			gc_own(void *ptr);

//----
//  Same as gc_own() but it adds it as a temporary pointer.
//----
int			gct_own(void *ptr);

//----
//  Frees a pointer allocating by the garbage collector.
//  It won't free a pointer that wasn't allocated from the garbage collector.
//  Safe from double free.
//----
int			gc_free(void *ptr);

//----
//  Same as gc_free() but it takes the address of the pointer that you want to free.
//  If freeing is successful, it sets the freed pointer to NULL.
//----
void		gc_destroy(void **ptr);

//----
//  Frees all allocated pointer by the garbage collector since the start of the program.
//----
void		gc_clean();

//----
//  Returns 1 if an error has occured in the garbage collector.
//----
int			gc_failed(void);

//----
//  Returns the last error message. You should not free or modify it.
//----
const char	*gc_get_error(void);

//--Standard--


void		*gc_calloc(size_t count, size_t size);
char		*gc_itoa(int n);
char		**gc_split(char const *s, char c);
char		*gc_strdup(const char *s1);
char		*gc_strjoin(char *s1, char *s2, int to_free);
char		*gc_substr(char const *s, unsigned int start, size_t len);

//extras
char		*gc_get_next_line(int fd);
void		gc_split_free(char **tab);
char		*gc_strappend(char *str, char c);

//String array
char		**gc_strarray_init();
char		**gc_strarray_append(char **array, char *str);
char		*gc_strarray_asstr(char **array);
void		gc_strarray_free(char **array);
char		**gc_strarray_from(char **other, size_t size);
char		**gc_strarray_fromstr(char *str);
size_t		gc_strarray_size(char **array);

size_t		gc_getfootprint();
size_t		gc_get_malloc_calls();

void		*gct_alloc(size_t size);
void		gct_free(void);
void		*gct_calloc(size_t count, size_t size);
char		*gct_itoa(int n);
char		*gct_strdup(const char *s1);
char		*gct_strjoin(char *s1, char *s2, int to_free);
char		*gct_substr(char const *s, unsigned int start, size_t len);
char		**gct_strarray_append(char **array, char *str);
char		*gct_strarray_asstr(char **array);
char		**gct_strarray_from(char **other, size_t size);
char		**gct_strarray_fromstr(char *str);
char		**gct_strarray_init();

void		gc_scope_start(void);
void		gc_scope_end(void);

//Basics

void		*ft_memset(void *b, int c, size_t len);
void		*ft_memseti(void *b, int c, size_t len);
void		*ft_memsetf(void *b, float c, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
