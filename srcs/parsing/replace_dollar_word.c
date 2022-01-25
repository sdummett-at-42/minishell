/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:31:19 by nammari           #+#    #+#             */
/*   Updated: 2021/12/20 14:31:15 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_dollar_word_value(char *dollar_word)
{
	t_variable	*env_var;
	t_variable	*global_var;

	env_var = g_variables->env;
	global_var = g_variables->global;
	while (env_var)
	{
		if (ft_strcmp(env_var->name, dollar_word) == 0)
			return (ft_strdup(env_var->value));
		env_var = env_var->next;
	}
	while (global_var)
	{
		if (ft_strcmp(global_var->name, dollar_word) == 0)
			return (ft_strdup(global_var->value));
		global_var = global_var->next;
	}
	return (NULL);
}

static void	copy_string_prefix(char *word, int index, char *new_wrd)
{
	int	i;

	i = 0;
	while (i < index && word != NULL && word[i] != '\0')
	{
		new_wrd[i] = word[i];
		++i;
	}
}

static void	copy_string_suffix(char *word, char *dlr_wrd_value, char *new_wrd)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (dlr_wrd_value && dlr_wrd_value[j] != '\0')
	{
		new_wrd[j] = dlr_wrd_value[j];
		++j;
	}
	while (word && word[i] != '\0')
	{
		new_wrd[j] = word[i];
		++j;
		++i;
	}
}

char	*replace_dollar_word(char *word, char *dollar_word, int index)
{
	long	len;
	char	*new_wrd;
	char	*dlr_wrd_value;

	if (ft_strcmp(dollar_word, "?") == 0)
		dlr_wrd_value = ft_itoa(g_variables->last_exit_status);
	else
		dlr_wrd_value = get_dollar_word_value(dollar_word);
	len = ft_strlen(word) - ft_strlen(dollar_word)
		+ ft_strlen(dlr_wrd_value) - 1;
	new_wrd = malloc(sizeof(*new_wrd) * len + 1);
	if (new_wrd == NULL)
		return (NULL);
	copy_string_prefix(word, index - 1, new_wrd);
	copy_string_suffix(word + index + ft_strlen(dollar_word), dlr_wrd_value,
		new_wrd + index - 1);
	new_wrd[len] = '\0';
	free(dlr_wrd_value);
	free(dollar_word);
	free(word);
	return (new_wrd);
}

/*
export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8
echo "$A'$B"'$C"$D'$E'"$F"'"'$G'$H"
*/