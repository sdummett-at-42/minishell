/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:25:52 by sdummett          #+#    #+#             */
/*   Updated: 2021/12/18 13:01:55 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*next;
}	t_variable;

typedef struct s_vars
{
	t_variable	*env;
	t_variable	*global;
	int			last_exit_status;
	char		*prog_name;
	char		*last_cmd_word;
	char		**environ;
	bool		is_child_to_kill;
	int			my_pid;
}	t_vars;

extern t_vars	*g_variables;

int				shell_init(char **av, char **envp);
t_vars			*init_env(char **av);
int				set_pwd(void);
int				set_lscolors(void);
int				set_underscore(void);
int				set_shlvl(void);

#endif