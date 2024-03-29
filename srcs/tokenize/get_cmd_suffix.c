/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_suffix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:53:14 by nammari           #+#    #+#             */
/*   Updated: 2021/12/16 11:28:12 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_suffix(char *str, t_token **head)
{
	char	*cmd_suffix;
	int		i;
	int		ret;

	i = 0;
	while (str[i])
		++i;
	cmd_suffix = malloc((i + 1) * sizeof(char));
	if (cmd_suffix == NULL)
		return (errno);
	cmd_suffix[i] = '\0';
	while (i--)
		cmd_suffix[i] = str[i];
	ret = ft_elem_pushback(head, ft_create_elem(cmd_suffix, CMD_SUFFIX));
	if (ft_catch_error(ret == 2, cmd_suffix, head) == MALLOC_ERROR)
		return (1);
	return (0);
}
