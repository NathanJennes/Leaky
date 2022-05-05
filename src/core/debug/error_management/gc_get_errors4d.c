/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_errors4d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:41:18 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 12:41:29 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const char	*gc_error_wrong_object(void)
{
	return ("Leaky: Trying to start an object with a pointer that doesn't"
		"belong to Leaky");
}
