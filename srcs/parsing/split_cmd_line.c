/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:55:21 by nammari           #+#    #+#             */
/*   Updated: 2021/12/20 16:14:00 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_i_and_j(int *i, int *j)
{
	++*i;
	++*j;
}

bool	skip_operator_and_increment(char *cmd_line, int *i, int *j)
{
	char	operator;

	if (cmd_line[*i] == '$')
	{
		increment_i_and_j(i, j);
		while (cmd_line[*i] != '\0' && !is_whitespace(cmd_line[*i]))
			increment_i_and_j(i, j);
		return (true);
	}
	else if (is_operator(cmd_line[*i]))
	{
		operator = cmd_line[*i];
		increment_i_and_j(i, j);
		if (cmd_line[*i] == operator && operator != '|')
			increment_i_and_j(i, j);
		return (true);
	}
	return (false);
}

static void	jump_to_next_quote(char *cmd, int *i, int *j, char q)
{
	++*i;
	++*j;
	while (cmd[*i] != '\0')
	{
		increment_i_and_j(i, j);
		if (cmd[*i] == q)
		{
			increment_i_and_j(i, j);
			if (is_quote(cmd[*i]))
				jump_to_next_quote(cmd, i, j, cmd[*i]);
			else
				while (!is_whitespace(cmd[*i]) && !is_operator(cmd[*i])
					&& cmd[*i] != '\0')
					increment_i_and_j(i, j);
			return ;
		}
	}
}

void	gaining_lines(char *cmd_line, int *i, int *j)
{
	while (is_whitespace(cmd_line[*i]))
		++*i;
	if (is_quote(cmd_line[*i]))
		jump_to_next_quote(cmd_line, i, j, cmd_line[*i]);
	else
		while ((is_alpha_num(cmd_line[*i]) || is_quote(cmd_line[*i]))
			&& !is_operator(cmd_line[*i]))
			increment_i_and_j(i, j);
}

void	split_cmd_line(char *cmd_line, char **args, int j)
{
	int		i;

	i = 0;
	while (cmd_line[i])
	{
		j = 0;
		gaining_lines(cmd_line, &i, &j);
		if (j > 0)
			*args++ = get_word(cmd_line + i, j);
		else
		{
			if (skip_operator_and_increment(cmd_line, &i, &j))
				*args++ = get_word(cmd_line + i, j);
			else if (cmd_line[i] != '\0' && !is_whitespace(cmd_line[i]))
				*args++ = capture_word(cmd_line, &i, &j);
		}
	}
	*args = NULL;
}
