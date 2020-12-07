/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoussa <mamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:54:49 by mamoussa          #+#    #+#             */
/*   Updated: 2020/12/05 12:38:32 by mamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	glob_var_init(void)
{
	g_fd_in = 0;
	g_fd_out = 0;
	g_is_in = 0;
	g_is_out = 0;
}

void	ft_exec_helper(void)
{
	t_cmd	*current;
	t_pipe	*new_node;
	size_t	index;

	g_pipe_head = NULL;
	current = g_cmd_head;
	index = 0;
	while (current)
	{
		if (current->type == cmd)
		{
			new_node = new_node_index(index);
			add_back(new_node);
			index++;
		}
		else if (current->type == semicolumn)
			index = 0;
		current = current->next;
	}
}

void 	close_all(t_pipe *cur)
{
	if (cur->index == 0 && (cur->fd0 > 2) && (cur->fd1 > 2))
		close(cur->fd1);
	else if (cur->index > 0 && (cur->fd0 > 2) && (cur->fd1 > 2))
	{
		close(cur->prev->fd0);
		close(cur->fd1);
	}
	else if (cur->prev->fd0 > 2)
		close(cur->prev->fd0);
}

void	free_pipe(void)
{
	t_pipe *tmp;

	while (g_pipe_head)
	{
		tmp = g_pipe_head->next;
		free(g_pipe_head);
		g_pipe_head = 	NULL;
		g_pipe_head = tmp;
	}
}

void	ft_execution(char *line, t_cmd *tmp)
{
	t_pipe *cur;

	ft_exec_helper();
	cur = g_pipe_head;
	while (g_cmd_head)
	{
		glob_var_init();
		if (check_for_red())
			return ;
		if (g_cmd_head->type == cmd)
		{
			g_is_cmd = 1;
			ft_pipes(g_cmd_head, cur);
			if (ft_strlen(g_cmd_head->string) == ft_strlen("sort") && 
			!ft_strncmp(g_cmd_head->string, "sort", ft_strlen("sort")))
				g_is_sort = 1;
			else
				g_is_sort = 0;
			ft_exec2(cur, line, tmp);
		cur = cur->next;
		}
		g_cmd_head = (g_cmd_head) ? g_cmd_head->next : g_cmd_head;
	}
	ft_exec3();
}
