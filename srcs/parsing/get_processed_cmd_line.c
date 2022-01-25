/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_processed_cmd_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:53:52 by nammari           #+#    #+#             */
/*   Updated: 2021/12/20 17:23:32 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_processed_cmd_line(char *cmd_line)
{
	int		words_nb;
	char	**splited_args;
	int		index;

	words_nb = 0;
	index = 0;
	words_nb = count_words_nb(cmd_line, words_nb);
	if (words_nb == 0)
		return (NULL);
	if (words_nb == ERROR)
		return (NULL);
	splited_args = malloc(sizeof(*splited_args) * (words_nb + 1));
	if (splited_args == NULL)
		return (NULL);
	split_cmd_line(cmd_line, splited_args, index);
	if (words_nb != 0 && splited_args[words_nb - 1] != NULL
		&&splited_args[words_nb - 1][0] == '|')
	{
		ft_error("minishell: parsing error\n");
		ft_free_tab(splited_args, 0);
		return (NULL);
	}
	return (splited_args);
}
