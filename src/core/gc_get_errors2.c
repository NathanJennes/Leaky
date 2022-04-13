/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_errors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:10:56 by njennes           #+#    #+#             */
/*   Updated: 2022/04/13 16:16:18 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*gc_error_clean_scope_left(void)
{
	return ("Leaky: A call to gc_clean() was done but "
			"some scopes weren't ended");
}

static char	*gc_error_no_exit_callback(void)
{
	return ("Leaky: A fatal error occurred but "
			"your callback didn't exit the program");
}
