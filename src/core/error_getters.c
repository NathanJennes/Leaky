/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:28:20 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 15:30:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const char	*gc_error_allocation(void)
{
	return ("Leaky: Allocation error!");
}

const char	*gc_error_scope_overflow(void)
{
	return ("Leaky: scope overflow! "
		"(Do you have a gc_scope_start() inside a while() ?)");
}

const char	*gc_error_scope_underflow(void)
{
	return ("Leaky: scope underflow! "
		"(Do you have a gc_scope_end() inside a while() ?)");
}
