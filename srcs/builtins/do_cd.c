/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:05:24 by sdummett          #+#    #+#             */
/*   Updated: 2021/12/19 22:24:01 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_cd(char **args, char *oldpwd, int *ret)
{
	char	*str;

	if (exec_cd_with_cdpath(args[0]) < 0)
	{
		if (chdir(args[0]) < 0)
		{
			str = strerror(errno);
			printf("cd: %s: %s\n", str, args[0]);
			free(oldpwd);
			*ret = 1;
			return ;
		}
		edit_env(oldpwd);
	}
}
