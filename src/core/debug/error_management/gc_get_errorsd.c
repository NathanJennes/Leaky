/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_errorsd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:28:20 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:29:44 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const char	*gc_error_allocation(void)
{
	return ("Leaky: Allocation error!");
}

const char	*gc_error_scope_overflow(void)
{
	return ("Leaky: Scope overflow! "
		"(Do you have a gc_scope_start() inside a while() ?)");
}

const char	*gc_error_scope_underflow(void)
{
	return ("Leaky: Scope underflow! "
		"(Do you have a gc_scope_end() inside a while() ?)");
}

const char	*gc_error_errors_overflow(void)
{
	return ("Leaky: Errors overflow! Did you properly set-up your callback ?");
}

const char	*gc_error_clean_empty(void)
{
	return ("Leaky: A call to gc_clean() was done but "
		"no memory has been allocated");
}
