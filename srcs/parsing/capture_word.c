/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:50:57 by nammari           #+#    #+#             */
/*   Updated: 2021/12/20 15:52:53 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*capture_word(char *cmd_line, int *i, int *j)
{
	while (cmd_line[*i] != '\0' && !is_whitespace(cmd_line[*i]))
	{
		++*i;
		++*j;
	}
	return (get_word(cmd_line + *i, *j));
}
