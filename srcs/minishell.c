/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 21:30:04 by sdummett          #+#    #+#             */
/*   Updated: 2021/12/20 15:06:48 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*g_variables = NULL;

static char	*get_cmd_line(void)
{
	char	*cmd_line;

	if (g_variables->last_exit_status == 131)
		printf("Quit (core dumped)\n");
	cmd_line = readline(BGRN"pepesh » "RESET);
	return (cmd_line);
}

static void	edit_underscore_var(void)
{
	char	**args;
	char	*var;
	int		len;

	len = ft_strlen(g_variables->last_cmd_word);
	var = malloc(sizeof(char) * (len + 3));
	if (var == NULL)
		return ;
	args = malloc(sizeof(char *) * 2);
	if (args == NULL)
		return ;
	ft_strlcpy(var, "_=", 3);
	ft_strlcat(var, g_variables->last_cmd_word, len + 3);
	args[0] = var;
	args[1] = NULL;
	ft_export(args);
	free(args);
	free(var);
}

int	minishell(void)
{
	char	*cmd;

	while (true)
	{
		signal(SIGINT, &sighandler);
		signal(SIGQUIT, SIG_IGN);
		cmd = get_cmd_line();
		update_history(cmd);
		if (cmd == NULL)
		{
			free_ressources();
			exit(0);
		}
		ft_parser(cmd);
		if (g_variables->last_cmd_word != NULL)
			edit_underscore_var();
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	shell_init(av, envp);
	minishell();
	return (g_variables->last_exit_status);
}
