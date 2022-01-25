/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words_nb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:59:48 by nammari           #+#    #+#             */
/*   Updated: 2021/12/20 15:06:15 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(char *cmd_line, int *index)
{
	char	quote_type;

	if (!is_quote(cmd_line[*index]))
		return (1);
	quote_type = cmd_line[*index];
	while (cmd_line[*index] != '\0')
	{
		++(*index);
		if (cmd_line[*index] == quote_type)
		{
			++(*index);
			if (is_quote(cmd_line[*index]))
				quote_type = cmd_line[*index];
			else
				return (0);
		}
	}
	return (ERROR);
}

bool	count_word(char *cmd_line, int *i, int *word_count)
{
	bool	is_word;

	is_word = false;
	while (cmd_line[*i] != '\0' && !is_whitespace(cmd_line[*i])
		&& !is_alpha_num(cmd_line[*i])
		&& !is_operator(cmd_line[*i])
		&& !is_quote(cmd_line[*i]) && cmd_line[*i] != '$')
	{
		is_word = true;
		++*i;
	}
	if (is_word)
		++*word_count;
	return (is_word);
}

void	count_and_skip_operator(char *cmd_line, int *index, int *word_count)
{
	char	c;

	if (cmd_line[*index] == '\0')
		return ;
	if (is_operator(cmd_line[*index]))
		++*word_count;
	c = cmd_line[*index];
	if (count_word(cmd_line, index, word_count))
		--*index;
	++*index;
	if (is_redirection(c))
	{
		if (cmd_line[*index] == c)
			++*index;
	}
}

bool	is_word(char *cmd_line, int *index)
{
	if (cmd_line[*index] == '\0')
		return (false);
	if ((is_alpha_num(cmd_line[*index]) || is_quote(cmd_line[*index]))
		&& !is_operator(cmd_line[*index]))
	{
		while (is_alpha_num(cmd_line[*index]) && !is_operator(cmd_line[*index]))
		{
			++*index;
		}
		if (is_quote(cmd_line[*index]))
			skip_quotes(cmd_line, index);
		return (true);
	}
	return (false);
}

int	count_words_nb(char *cmd_line, int wrd_count)
{
	int		i;

	i = 0;
	while (cmd_line[i] != '\0')
	{
		while (is_whitespace(cmd_line[i]))
			++i;
		if (is_word(cmd_line, &i))
		{
			while (is_word(cmd_line, &i))
				;
			++wrd_count;
		}
		if (is_quote(cmd_line[i]))
		{
			if (skip_quotes(cmd_line, &i) == ERROR)
				return (ERROR);
			is_word(cmd_line, &i);
			++wrd_count;
		}
		count_and_skip_operator(cmd_line, &i, &wrd_count);
	}
	return (wrd_count);
}
