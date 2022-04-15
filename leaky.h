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
//  Sets the error callback of leaky.
//--
//  If an error occur (allocation error, ...), callback will be called.
//  It is strongly recommended to set one.
//  It is strongly recommended that you save/free all other ressources that
//    you may be using, then call gc_clean() and then exit the program.
//----
void		gc_set_callback(int (*callback)(void *));

//----
//  Sets the parameter that wil be given when calling the error callback.
//--
//  This parameter is optional.
//----
void		gc_set_callback_param(void *param);

//----
//  Toggles on or off automatic cleaning upon error.
//--
//  This parameter is optional.
//--
//  By default, Leaky won't do any king of automatic cleaning
//    if an error occurs. This is to let you handle your resources as you want.
//    For example, you might need to do some things with your data before
//    exiting in the error callback.
//  If you enable this behavior, all allocated resources will be freed
//    right after an error occurs, and before the error callback is called.
//----
void		gc_clean_on_error(int clean_on_error);

//----
//  Sets the base capacity in allocations of Leaky.
//--
//  This parameter is optional.
//--
//  Capacity of allocations is automatically handled by Leaky
//    (it grows as your program requests more allocations).
//  This parameter allows you to more precisely configure Leaky
//    for your use case.
//  If your program allocated a lot of memory, you might set this number to
//    something in the thousands. On the other hand you may want to set it to
//    a lower number.
//  The base capacity is 100. That means that Leaky can hold 100 pointers at a
//    time before needing to do any king of reallocation.
//----
void		gc_set_default_capacity(size_t capacity);

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

//----
//  Makes this the parent of all new allocations.
//--
//  If this pointer is freed, all of its child will be freed too.
//  You can end this object creation by calling gc_object_end().
//----
void	gc_object_start(void *ptr);

//----
//  End the current object creation.
//----
void	gc_object_end();

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
char		**gc_strarray_append(char **array, const char *str);

//----
//  Same as gc_strarray_append() but the array created is temporary.
//--
//  Temporary pointers can all be freed at any point by a call to gct_free().
//----
char		**gct_strarray_append(char **array, const char *str);

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

//---------//
//--Debug--//
//---------//

//----
//  Returns the last error message. You should not free or modify it.
//----
const char	*gc_get_last_error(void);

//----
//  Returns an array of error strings. You should not free or modify it.
//----
const char	**gc_get_errors(void);

//----
//  Get the error message when an allocation crashes.
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_allocation()) ...
//----
const char	*gc_error_allocation(void);

//----
//  Get the error message when too many scopes were created.
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_scope_overflow()) ...
//----
const char	*gc_error_scope_overflow(void);

//----
//  Get the error message when you try to get out of a scope that
//    you didn't start.
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_scope_underflow()) ...
//----
const char	*gc_error_scope_underflow(void);

//----
//  Get the error message when you get too many errors.
//--
//  Non-fatal error can be ignored with gc_ignore_warnings().
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_errors_overflow()) ...
//----
const char	*gc_error_errors_overflow(void);

//----
//  Get the error message when you call gc_clean() without allocating anything.
//--
//  Non-fatal error can be ignored with gc_ignore_warnings().
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_clean_empty()) ...
//----
const char	*gc_error_clean_empty(void);

//----
//  Get the error message when you call gc_clean() without ending all scopes.
//--
//  Non-fatal error can be ignored with gc_ignore_warnings().
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_clean_scope_left()) ...
//----
const char	*gc_error_clean_scope_left(void);

//----
//  Get the error message when a fatal error occurs but your callback
//    doesn't exit the program.
//--
//  Non-fatal error can be ignored with gc_ignore_warnings().
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_no_exit_callback()) ...
//----
const char	*gc_error_no_exit_callback(void);

//----
//  Get the error message when a setting was changed but
//    an allocation already occurred.
//--
//  Non-fatal error can be ignored with gc_ignore_warnings().
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_settings_after_allocation()) ...
//----
const char	*gc_error_settings_after_allocation(void);

//----
//  Get the error message when you are trying to attach a pointer to another
//    but the parent doesn't belong to Leaky.
//--
//  Non-fatal error can be ignored with gc_ignore_warnings().
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_attach_wrong_parent()) ...
//----
const char	*gc_error_attach_wrong_parent(void);

//----
//  Get the error message when you are trying to attach a pointer to another
//    but the pointer doesn't belong to Leaky.
//--
//  Non-fatal error can be ignored with gc_ignore_warnings().
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_attach_wrong_pointer()) ...
//----
const char	*gc_error_attach_wrong_pointer(void);

//----
//  Get the error message when you are trying to detach a pointer
//    from its parent but the pointer doesn't belong to Leaky.
//--
//  Non-fatal error can be ignored with gc_ignore_warnings().
//--
//  Can be used to figure out the type of error that was thrown.
//  Example:
//    if (gc_get_last_error() == gc_error_detach_wrong_pointer()) ...
//----
const char	*gc_error_detach_wrong_pointer(void);

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
