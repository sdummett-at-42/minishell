/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:03:29 by nammari           #+#    #+#             */
/*   Updated: 2021/12/20 15:07:13 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	wait_for_children(t_command_vars *com)
{
	int	i;
	int	status;
	int	last_exit_status;

	i = 0;
	last_exit_status = g_variables->last_exit_status;
	if (com->is_main_process_cmd == true)
		return (last_exit_status);
	while (i < com->nb)
	{
		wait(&status);
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			last_exit_status = WTERMSIG(status) + 128;
			if (last_exit_status == 130)
				printf("\n");
		}
		++i;
	}
	return (last_exit_status);
}
