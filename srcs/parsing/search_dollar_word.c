/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_dollar_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:30:10 by nammari           #+#    #+#             */
/*   Updated: 2021/12/16 10:37:58 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_single_quote(char *word, int *i)
{
	if (word == NULL || *i < 0)
		return ;
	if (word[*i] == '\'')
		++*i;
	while (word[*i] != '\0' && word[*i] != '\'')
		++*i;
}

static char	*get_dollar_word_if_any(char **word, int i, bool *ignore_quote)
{
	int		j;
	char	*dollar_word;

	j = 0;
	while (!is_whitespace(word[0][i + j]) && word[0][i + j] != '\0'
			&& word[0][i + j] != '$' && word[0][i + j] != '\'')
	{
		if (*ignore_quote == true && word[0][i + j] == '"')
		{
			*ignore_quote = false;
			break ;
		}
		++j;
	}
	dollar_word = malloc(sizeof(*dollar_word) * (j + 1));
	if (dollar_word == NULL)
		return (NULL);
	dollar_word[j] = '\0';
	while (j > 0)
	{
		dollar_word[j - 1] = word[0][i + j - 1];
		--j;
	}
	*ignore_quote = false;
	return (dollar_word);
}

char	*get_dollar_word(char **word)
{
	int		i;
	char	*dollar_word;
	bool	ignore_quote;

	i = 0;
	ignore_quote = false;
	while (word[0][i] != '\0')
	{
		if (word[0][i] == '"')
			ignore_quote = !ignore_quote;
		if (word[0][i] == '\'' && ignore_quote == false)
			skip_single_quote(word[0], &i);
		if (word[0][i] == '$' && is_alpha_num(word[0][i + 1])
			&& word[0][i + 1] != '$')
		{
			++i;
			dollar_word = get_dollar_word_if_any(word, i, &ignore_quote);
			word[0] = replace_dollar_word(word[0], dollar_word, i);
			i = -1;
		}
		++i;
	}
	return (word[0]);
}
