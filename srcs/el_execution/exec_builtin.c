/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:40:47 by nammari           #+#    #+#             */
/*   Updated: 2021/12/20 16:22:59 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_ressources_builtin(void)
{
	free_environ(g_variables->environ);
	free_t_variable_struct(g_variables->env);
	free_t_variable_struct(g_variables->global);
	free(g_variables->last_cmd_word);
	free(g_variables);
}

void	exit_builtin_exec(int pipe[2], int prev_output,
	t_command_vars *com, t_token **head)
{
	if (pipe[0] != -1)
		close(pipe[0]);
	if (pipe[1] != -1)
		close(pipe[1]);
	if (prev_output != -1)
		close(prev_output);
	if (com->input_fd != -1)
		close(com->input_fd);
	if (com->output_fd != -1)
		close(com->output_fd);
	ft_free_tab(com->name, 0);
	ft_free_tab(com->paths, 0);
	free_token_lst(*head);
	free_ressources_builtin();
	close_fd_chain(com->in_head, com);
	close_fd_chain(com->out_head, com);
	exit(0);
}

int	assign_variables(char **keyvalue)
{
	int	i;

	if (keyvalue == NULL || *keyvalue == NULL)
		return (1);
	i = 0;
	while (keyvalue[i])
	{
		assign_var(keyvalue[i]);
		++i;
	}
	return (0);
}

int	exec_builtin(t_command_vars *commands, t_token **head)
{
	int	exit_status;

	exit_status = -1;
	if (ft_strcmp(commands->name[0], "cd") == 0)
		exit_status = ft_cd(commands->name + 1);
	else if (ft_strcmp(commands->name[0], "echo") == 0)
		exit_status = ft_echo(commands->name + 1);
	else if (ft_strcmp(commands->name[0], "pwd") == 0)
		exit_status = ft_pwd(commands->name + 1);
	else if (ft_strcmp(commands->name[0], "env") == 0)
		exit_status = ft_env(commands->name + 1);
	else if (ft_strcmp(commands->name[0], "exit") == 0)
		exit_status = ft_exit(commands->name + 1, head, commands);
	else if (ft_strcmp(commands->name[0], "export") == 0)
		exit_status = ft_export(commands->name + 1);
	else if (ft_strcmp(commands->name[0], "unset") == 0)
		exit_status = ft_unset(commands->name + 1);
	else if (commands->is_assign == true)
		exit_status = assign_variables(commands->name);
	if (exit_status != -1)
		g_variables->last_exit_status = exit_status;
	return (exit_status);
}
