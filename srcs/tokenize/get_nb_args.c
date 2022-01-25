/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nb_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:00:13 by sdummett          #+#    #+#             */
/*   Updated: 2021/12/19 22:00:31 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_args(t_token *head)
{
	int		nb_args;

	nb_args = 0;
	while (head && head->type != PIPE)
	{
		if (head->type == CMD_SUFFIX)
			++nb_args;
		head = head->next;
	}
	return (nb_args);
}
