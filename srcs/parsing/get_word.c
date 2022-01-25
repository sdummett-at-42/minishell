/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:58:22 by nammari           #+#    #+#             */
/*   Updated: 2021/12/16 11:49:31 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_unquoted_lenght(char *word)
{
	int		i;
	int		len;
	int		quote_count;
	char	quote;

	i = 0;
	quote_count = 0;
	quote = '\0';
	while (word[i] != '\0')
	{
		if (is_quote(word[i]) && quote == '\0')
			quote = word[i];
		else if (word[i] == quote)
		{
			quote = '\0';
			quote_count += 2;
		}
		++i;
	}
	len = ft_strlen(word) - quote_count;
	return (len);
}

static char	*get_unquoted_word(char *word)
{
	int		i;
	int		len;
	char	*unquoted_word;
	char	quote;

	len = get_unquoted_lenght(word);
	unquoted_word = malloc(sizeof(char) * (len + 1));
	if (unquoted_word == NULL)
		return (NULL);
	quote = '\0';
	len = 0;
	i = -1;
	while (word[++i])
	{
		if (is_quote(word[i]) && quote == '\0')
			quote = word[i];
		else if (word[i] == quote)
			quote = '\0';
		else
			unquoted_word[len++] = word[i];
	}
	unquoted_word[len] = '\0';
	return (unquoted_word);
}

static char	*get_word_value(char *cmd_line, int word_length)
{
	char	*word;

	word = malloc(sizeof(*word) * (word_length + 1));
	if (word == NULL)
		return (NULL);
	word[word_length] = '\0';
	while (word_length--)
	{
		--cmd_line;
		word[word_length] = *cmd_line;
	}
	return (word);
}

char	*get_word(char *cmd_line, int word_length)
{
	char	*word;
	char	*tmp_word;

	tmp_word = get_word_value(cmd_line, word_length);
	tmp_word = get_dollar_word(&tmp_word);
	word = get_unquoted_word(tmp_word);
	free(tmp_word);
	return (word);
}
