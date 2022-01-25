/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nammari <nammari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:41:40 by sdummett          #+#    #+#             */
/*   Updated: 2021/12/20 16:03:39 by nammari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_two_chars(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 1)
			return (true);
		i++;
	}
	return (false);
}

static bool	is_echo_option(char *str)
{
	unsigned int	i;

	if (!has_two_chars(str))
		return (false);
	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

static unsigned int	skip_options(char **args, bool *has_option)
{
	unsigned int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (!is_echo_option(args[i]))
		{
			if (i != 0)
				*has_option = true;
			else
				*has_option = false;
			return (i);
		}
		i++;
	}
	return (i);
}

int	ft_echo(char **args)
{
	unsigned int	i;
	bool			has_option;

	i = skip_options(args, &has_option);
	while (args[i] != NULL)
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
		if (args[i] != NULL)
			write(1, " ", 1);
	}
	if (has_option == false)
		write(1, "\n", 1);
	return (0);
}
