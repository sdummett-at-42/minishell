/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 21:56:03 by sdummett          #+#    #+#             */
/*   Updated: 2021/12/19 21:57:26 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*cat_path(char *str1, char *str2)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	ft_strlcpy(new, str1, ft_strlen(str1) + 1);
	ft_strlcat(new, str2, ft_strlen(str1) + ft_strlen(str2) + 1);
	return (new);
}

int	exec_cd_with_cdpath(char *str)
{
	int			i;
	t_variable	*var;
	char		**path;
	char		*joined_path;

	var = get_variable(g_variables->env, "CDPATH");
	if (var == NULL)
		return (-1);
	path = ft_split(var->value, ':');
	i = 0;
	while (path[i] != NULL)
	{
		joined_path = cat_path(path[i], str);
		if (chdir(joined_path) > -1)
		{
			free(joined_path);
			free_array(path);
			return (1);
		}
		free(joined_path);
		i++;
	}
	return (-1);
}
