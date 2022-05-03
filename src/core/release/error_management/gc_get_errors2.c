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

const char	*gc_error_no_exit_callback(void)
{
	return ("Leaky: A fatal error occurred but "
		"your callback didn't exit the program");
}
