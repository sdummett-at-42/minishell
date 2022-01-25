/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:41:27 by sdummett          #+#    #+#             */
/*   Updated: 2021/12/19 22:36:48 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** chdir seems to handle ".." without to expand it 
** (test with all environment variable unset)
*/

static int	exec_cd_with_home_var(void)
{
	t_variable	*var;

	var = get_variable(g_variables->env, "HOME");
	if (var == NULL)
	{
		write(2, g_variables->prog_name, ft_strlen(g_variables->prog_name));
		write(2, ": cd: HOME not set\n", ft_strlen(": cd: HOME not set\n"));
		return (1);
	}
	chdir(var->value);
	return (0);
}

void	edit_env(char *olddirectory)
{
	char		*cwd;
	t_variable	*env_oldpwd;
	t_variable	*env_pwd;

	cwd = call_getcwd();
	env_oldpwd = get_variable(g_variables->env, "OLDPWD");
	env_pwd = get_variable(g_variables->env, "PWD");
	if (env_oldpwd != NULL)
	{
		free(env_oldpwd->value);
		env_oldpwd->value = olddirectory;
	}
	else
		free(olddirectory);
	if (env_pwd != NULL)
	{
		free(env_pwd->value);
		env_pwd->value = cwd;
	}
	else
		free(cwd);
}

static bool	has_too_many_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (i == 1)
			return (true);
		i++;
	}
	return (false);
}

static int	too_many_args_error(void)
{
	write(2, g_variables->prog_name, ft_strlen(g_variables->prog_name));
	write(2, ": cd: too many arguments\n",
		ft_strlen(": cd: too many arguments\n"));
	return (1);
}

int	ft_cd(char **args)
{
	char	*oldpwd;
	int		ret;

	ret = 0;
	if (has_too_many_args(args))
		return (too_many_args_error());
	oldpwd = call_getcwd();
	if (args == NULL || *args == NULL)
	{
		if (exec_cd_with_home_var() == 1)
		{
			return (1);
			free(oldpwd);
		}
		edit_env(oldpwd);
	}
	else
		do_cd(args, oldpwd, &ret);
	return (ret);
}
