/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoussa <mamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:11:48 by mamoussa          #+#    #+#             */
/*   Updated: 2020/12/04 17:28:55 by mamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    ft_exit(char *line, t_cmd *tmp)
{
    if (g_cmd_head && ft_strncmp("exit", g_cmd_head->string, ft_strlen(g_cmd_head->string)))
    {
        ft_error("command not found:");
        write(1, g_cmd_head->string, ft_strlen(g_cmd_head->string));
        write(1, "\n", 1);
        return ;
    }
    if (line)
        simple_pointer_free(line);
    if (tmp)
        ft_lstclearcmd(&tmp);
	ft_lstclearenv(&g_env_head);/* free env var  */
	if (g_tmp_env)
		double_pointer_free(g_tmp_env);
    exit(0);
}