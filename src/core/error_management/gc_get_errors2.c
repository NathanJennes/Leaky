/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_errors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:10:56 by njennes           #+#    #+#             */
/*   Updated: 2022/04/15 13:39:30 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const char	*gc_error_clean_scope_left(void)
{
	return ("Leaky: A call to gc_clean() was done but "
		"some scopes weren't ended");
}

const char	*gc_error_no_exit_callback(void)
{
	return ("Leaky: A fatal error occurred but "
		"your callback didn't exit the program");
}

const char	*gc_error_settings_after_allocation(void)
{
	return ("Leaky: A setting was changed but an allocation already occurred");
}

const char	*gc_error_attach_wrong_parent(void)
{
	return ("Leaky: Trying to attach a pointer to a parent "
		"that doesn't belong to Leaky");
}

const char	*gc_error_attach_wrong_pointer(void)
{
	return ("Leaky: Trying to set the parent of a pointer "
		"that doesn't belong to Leaky");
}
