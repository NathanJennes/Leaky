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

# define LK_FALSE 0
# define LK_TRUE 1

typedef struct s_gc	t_gc;

//----IMPORTANT----
//  Any pointer allocated by gc_*() MUST be freed by
//    gc_free() / gc_destroy() / gc_clean() / gc_scope_end().
//  Otherwise, double free might occur.
//  Best practice is to only use gc_* functions.
//----

//--------//
//--Core--//
//--------//

//----
//  Interface for setting up Leaky's behavior.
//--
//  gc(GC_SET_CALLBACK, your_callback_function)
//    To set allocation error callback.
//    This function must return an int and take a pointer as parameter.
//    It will be called upon any allocation error.
//    It is recommended to save/free all system resources,
//      then call gc_clean() and exit your program in your callback.
//--
//  gc(GC_SET_CALLBACK_PARAM, your param)
//    To set the parameter that will be passed to the callback.
//----
t_gc		*gc(int mode, void *param);

//----
//  Works like malloc().
//--
//  A pointer allocated with gc_alloc() MUST be freed by
//    gc_free() / gc_destroy() / gc_clean() / gc_scope_end().
//---
void		*gc_alloc(size_t size);

//----
//  Same as gc_alloc() but the pointer created is temporary.
//--
//  Temporary pointers can all be freed at any point by a call to gct_free().
//---
void		*gct_alloc(size_t size);

//----
//  Takes a pointer allocated outside Leaky and
//    adds it to the list of managed pointers so that it can be freed by
//    gc_free() / gc_destroy() / gc_clean() / gc_scope_end().
//--
//  If an error occurs during the transfer, the pointer will be freed.
//  If the pointer was allocated by Leaky, nothing will be done
//    and the function returns 0
//----
int			gc_own(void *ptr);

//----
//  Same as gc_own() but the pointer created is temporary.
//--
//  Temporary pointers can all be freed at any point by a call to gct_free().
//----
int			gct_own(void *ptr);

//----
//  Frees a pointer allocating by Leaky.
//--
//  It won't free a pointer that wasn't allocated bt Leaky.
//  Safe from double frees.
//  If freeing was successful, it returns 1, otherwise it returns 0.
//----
int			gc_free(void *ptr);

//----
//  Frees all temporary pointers.
//----
void		gct_free(void);

//----
//  Takes the address of the pointer that you want to free.
//  If freeing is successful, it sets the freed pointer to NULL.
//----
void		gc_destroy(void **ptr);

//----
//  Frees all allocated memory by the garbage collector.
//    since the start of the program.
//----
void		gc_clean(void);

//----
//  Returns 1 if an error has occured in Leaky.
//----
int			gc_failed(void);

//----
//  Returns the last error message. You should not free or modify it.
//----
const char	*gc_get_error(void);

//----
//  Starts a new scope.
//--
//  Scopes can be started and ended anywhere.
//  All allocations that were done during this scope will be freed
//    by a call to gc_scope_end().
//--
//  Example:
//
//  function1()
//  {
//    gc_scope_start();
//    ...
//    function2();
//    ...
//    gc_scope_end(); -> #2
//  }
//
//  function2()
//  {
//  gc_scope_start();
//  ...
//  gc_scope_end(); -> #1
//  }
//
//  #1: This call frees everything that was allocated during function2
//  #2: This call frees everything that was allocated during function1
//    and function2. In this case, everything from function2 was already freed
//    so nothing has to be free that was allocated during function2.
//
//----
void		gc_scope_start(void);

//----
//  Ends the current scope and frees all pointers allocated during it.
//--
//  Scopes can be started and ended anywhere.
//--
//  Example:
//
//  function1()
//  {
//    gc_scope_start();
//    ...
//    function2();
//    ...
//    gc_scope_end(); -> #2
//  }
//
//  function2()
//  {
//  gc_scope_start();
//  ...
//  gc_scope_end(); -> #1
//  }
//
//  #1: This call frees everything that was allocated during function2
//  #2: This call frees everything that was allocated during function1
//    and function2. In this case, everything from function2 was already freed
//    so nothing has to be free that was allocated during function2.
//
//----
void		gc_scope_end(void);

//------------//
//--Standard--//
//------------//
//  Those functions work like the standard libc ones.
//  Returned pointers must be freed by
//    gc_free() / gc_destroy() / gc_clean() / gc_scope_end().

void		*gc_calloc(size_t count, size_t size);
void		*gct_calloc(size_t count, size_t size);
char		*gc_itoa(int n);
char		*gct_itoa(int n);
char		*gc_strdup(const char *s1);
char		*gct_strdup(const char *s1);
char		*gc_substr(char const *s, unsigned int start, size_t len);
char		*gct_substr(char const *s, unsigned int start, size_t len);

//----
//  PARAM:
//    to_free: can be set to FREE_NONE / FREE_FIRST / FREE_SECOND / FREE_BOTH
//--
//  Works like strjoin().
//--
//  You can specify if you want to free the given strings.
//    This only works if the string specified was allocated by Leaky.
//----
char		*gc_strjoin(char *s1, char *s2, int to_free);

//----
//  Same as gc_strjoin() but the pointers created are temporary.
//--
//  Temporary pointers can all be freed at any point by a call to gct_free().
//----
char		*gct_strjoin(char *s1, char *s2, int to_free);

//----------//
//--Extras--//
//----------//

//----
//  PARAM:
//    fd: the file descriptor of the file to read.
//--
//  Reads the file given and returns the current line.
//  With each call to gc_get_next_line(), you get the next line.
//  When reaching EOF, the functions returns NULL.
//--
//  The line returned must be freed by
//    gc_free() / gc_destroy() / gc_clean() / gc_scope_end().
//----
char		*gc_get_next_line(int fd);

//----
//  Create a new string by concatenating str and c.
//--
//  If free_old_str is set to LK_TRUE and str is managed by Leaky,
//    str will be freed
//----
char		*gc_strappend(char *str, char c, int free_old_str);

//----
//  Splits the string s into multiple strings delimited by c.
//--
//  It is fully compatible with gc_strarray*().
//  The array ends with a NULL.
//  s will not be freed.
//----
char		**gc_split(char const *s, char c);

//----------------//
//--String array--//
//----------------//

//----
//  Initializes a string array.
//--
//  It must be freed by gc_strarray_free().
//----
char		**gc_strarray_init(void);

//----
//  Same as gc_strarray_init() but the array created is temporary.
//--
//  Temporary pointers can all be freed at any point by a call to gct_free().
//----
char		**gct_strarray_init(void);

//----
//  Appends a string at the back of the array.
//--
//  str will be duplicated and wont be freed.
//--
//  IMPORTANT:
//    It returns a new array.
//    If the old one (pointed to by the parameter array)
//    was allocated by Leaky, it will be freed and should not be used
//----
char		**gc_strarray_append(char **array, char *str);

//----
//  Same as gc_strarray_append() but the array created is temporary.
//--
//  Temporary pointers can all be freed at any point by a call to gct_free().
//----
char		**gct_strarray_append(char **array, char *str);

//----
//  Creates a string from the concatenation of all strings in array.
//----
char		*gc_strarray_asstr(char **array);

//----
//  Same as gc_strarray_asstr() but the string created is temporary.
//--
//  Temporary pointers can all be freed at any point by a call to gct_free().
//----
char		*gct_strarray_asstr(char **array);

//----
//  Frees a string array allocated by Leaky.
//----
void		gc_strarray_free(char **array);

//----
//  Duplicates a string array of size size.
//----
char		**gc_strarray_from(char **other, size_t size);

//----
//  Same as gc_strarray_from() but the array created is temporary.
//--
//  Temporary pointers can all be freed at any point by a call to gct_free().
//----
char		**gct_strarray_from(char **other, size_t size);

//----
//  Creates a string array with str as its first element.
//----
char		**gc_strarray_fromstr(char *str);

//----
//  Same as gc_strarray_fromstr() but the array created is temporary.
//--
//  Temporary pointers can all be freed at any point by a call to gct_free().
//----
char		**gct_strarray_fromstr(char *str);

//----
//  Get the number of strings in the array.
//----
size_t		gc_strarray_size(char **array);

//--Debug--

//----
//  Get the error message when an allocation crashes.
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_error() == gc_error_allocation()) ...
//----
const char	*gc_error_allocation(void);

//----
//  Get the error message when too many scopes were created.
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_error() == gc_error_scope_overflow()) ...
//----
const char	*gc_error_scope_overflow(void);

//----
//  Get the error message when you try to get out of a scope that
//    you didn't start.
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_error() == gc_error_scope_underflow()) ...
//----
const char	*gc_error_scope_underflow(void);

//----
//  Returns the current number of allocated pointers.
//----
size_t		gc_getfootprint(void);

//----
//  Returns the number of calls to malloc() since the start of the program.
//----
size_t		gc_get_malloc_calls(void);

//----------//
//--Basics--//
//----------//

void		*gc_memset(void *b, int c, size_t len);
void		*gc_memseti(void *b, int c, size_t len);
void		*gc_memsetf(void *b, float c, size_t len);
void		*gc_memcpy(void *dst, const void *src, size_t n);
void		*gc_memmove(void *dst, const void *src, size_t len);
void		*ft_calloc(size_t count, size_t size);
size_t		gc_strlen(const char *s);
size_t		gc_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
