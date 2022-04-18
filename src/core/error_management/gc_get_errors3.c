/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_errors3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:41:37 by njennes           #+#    #+#             */
/*   Updated: 2022/04/18 13:34:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const char	*gc_error_detach_wrong_pointer(void)
{
	return ("Leaky: Trying to detach a pointer from it's parent "
			"that doesn't belong to Leaky");
}

const char	*gc_error_too_much_parents(void)
{
	return ("Leaky: Trying to attach a pointer to a parent but "
			"it already has the maximum amount of parents");
}

const char	*gc_error_attach_same_parent(void)
{
	return ("Leaky: Trying to attach a pointer to a parent but "
			"it already has that parent");
}

const char	*gc_error_detach_not_parent(void)
{
	return ("Leaky: Trying to detach a pointer from it's parent but "
			"it didn't had that parent");
}
