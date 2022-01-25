/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:33:37 by sdummett          #+#    #+#             */
/*   Updated: 2021/12/16 13:12:41 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenize(char **args, t_token **head)
{
	int	i;
	int	ret;
	int	(*get_redirection[4])(char **arg, int *index, t_token **head);

	i = 0;
	init_function_pointer(get_redirection);
	while (args && args[i])
	{
		if (is_redirection(args[i][0]))
			ret = get_redirection_op(get_redirection, args, &i, head);
		else if (args[i][0] == '|')
			ret = get_pipe_op(args, i, head);
		else if (is_next_word_assignment(args[i]))
			ret = get_assignment(args[i], head);
		else
			ret = get_cmd(args, &i, head);
		if (ret > 0)
			return (ret);
		if (args[i])
			++i;
	}
	return (0);
}
