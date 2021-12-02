/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noufel <noufel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:30:44 by sdummett          #+#    #+#             */
/*   Updated: 2021/11/25 08:17:04 by noufel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_2(t_token *head)
{
	char *tab[13];
	int	i;

	i = 0;
	tab[0] = "CMD_NAME";
	tab[1] = "CMD_SUFFIX";
	tab[2] = "PIPE";
	tab[3] = "VAR";
	tab[4] = "REDIR_IN";
	tab[5] = "REDIR_HERE_DOC";
	tab[6] = "REDIR_OUT_TRUNC";
	tab[7] = "REDIR_OUT_APPEND";
	tab[8] = "ASSIGN";
	tab[9] = "";
	while (head)
	{
		i = 0;
		if (head->type == CMD_NAME)
		{
			while (head->cmd[i])
			{
				printf("This is cmd[%d] %s\n", i, head->cmd[i]);
				++i;
			}
		}
		else
			printf("type : %s | value : %s\n", tab[head->type], head->value);
		head = head->next;
	}
}

void	print_token(t_token *head)
{
	char *tab[13];

	tab[0] = "CMD_NAME";
	tab[1] = "CMD_SUFFIX";
	tab[2] = "PIPE";
	tab[3] = "VAR";
	tab[4] = "REDIR_IN";
	tab[5] = "REDIR_HERE_DOC";
	tab[6] = "REDIR_OUT_TRUNC";
	tab[7] = "REDIR_OUT_APPEND";
	tab[8] = "ASSIGN";
	tab[9] = "";
	while (head)
	{
		printf("type : %s | value : %s\n", tab[head->type], head->value);
		head = head->next;
	}
}

char**	copy_cmd_elem(char **src)
{
	int		i;
	char 	**dst;

	i = 0;
	if (!src || !*src)
		return (NULL);
	while (src[i])
		++i;
	dst = malloc(sizeof(*dst) * (i + 1));
	if (dst == NULL)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = ft_strdup(src[i]);
	dst[i] = NULL;
	return (dst);
}

t_token	*dup_elem(t_token *src_elem)
{
	t_token	*dst_elem;
	
	if (src_elem == NULL)
		return (NULL);
	dst_elem = malloc(sizeof(*dst_elem));
	if (dst_elem == NULL)
		return (NULL);
	dst_elem->cmd = copy_cmd_elem(src_elem->cmd);
	dst_elem->value = ft_strdup(src_elem->value);
	dst_elem->type = src_elem->type;
	dst_elem->next = NULL;
	return (dst_elem);
}

t_token	*map_lst_till_pipe_or_eol(t_token **head)
{
	t_token	*new_head;
	t_token	*new_head_ptr;

	if (*head == NULL)
		return (NULL);
	new_head = dup_elem(*head);
	if (new_head == NULL)
		return (NULL);
	new_head_ptr = new_head;
	(*head) = (*head)->next;
	while (*head != NULL && (*head)->type != PIPE)
	{
		new_head_ptr->next = dup_elem(*head);
		new_head_ptr = new_head_ptr->next;
		(*head) = (*head)->next;
	}
	if (*head && (*head)->type == PIPE)
		*head = (*head)->next;
	return (new_head);
}

int	count_nb_cmds(t_token *head)
{
	int	nb_cmd;

	nb_cmd = 0;
	while (head)
	{
		if (head->type == CMD_NAME)
			nb_cmd++;
		head = head->next;
	}
	return (nb_cmd);
}

int	ft_parser(char *cmd)
{
	char	**args;
	t_token *head;
	extern char	**environ;

	head = NULL;
	args = get_prosseced_cmd_line(cmd);
	ft_tokenize(args, &head);
	group_cmd_and_args(&head);
	// print_token(head);
	if (!head)
		return (-1);
	int nb_cmds = count_nb_cmds(head);
	pipex_exec_test(nb_cmds, &head, environ);
	return (0);
}