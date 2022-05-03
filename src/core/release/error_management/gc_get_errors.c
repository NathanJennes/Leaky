/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:28:20 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 15:45:49 by njennes          ###   ########.fr       */
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

const char	*gc_error_too_much_parents(void)
{
	return ("Leaky: Trying to attach a pointer to a parent but "
		"it already has the maximum amount of parents");
}
