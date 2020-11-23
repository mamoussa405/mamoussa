/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoussa <mamoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:43:12 by mamoussa          #+#    #+#             */
/*   Updated: 2020/11/22 17:36:49 by mamoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    path_checker(void)
{
    t_env   *current;

    current = g_env_head;
    while (current)
    {
        if (!ft_strncmp(current->key, "HOME", ft_strlen("HOME")))
        {
            g_tmp = g_cmd_head->string;
            g_cmd_head->string = ft_strjoin(current->value,
            g_cmd_head->string);
            free(g_tmp);
            break;
        }
        current = current->next;
    }
}

void    check_for_tilde(void)
{
    char    *str;
    char    *strtmp;

    strtmp = ft_strdup(g_cmd_head->string);
    str = (char*)malloc(ft_strlen(strtmp));
    str_cpy(&str, &strtmp);
    g_tmp = g_cmd_head->string;
    g_cmd_head->string = ft_strdup(str);
    free(g_tmp);
    path_checker();
    free(str);
    free(strtmp);
}

char    *check_for_home(void)
{
    t_env   *current;

    current = g_env_head;
    while(current)
    {
        if (!ft_strncmp(current->key, "HOME", ft_strlen("HOME")))
        {
            return (current->value);
            break;
        }
        current = current->next;
    }
    return (NULL);
}

void	ft_cd(void)
{
    int     ret;

    if(ft_cd_helper())
        return ;
    if (!ft_strncmp(g_cmd_head->string, "~", ft_strlen("~")))
        check_for_tilde();
    ret = chdir(g_cmd_head->string);
    if (ret < 0)
    {
        ft_error(strerror(errno));
        write(1, ":", 1);
        write(1, g_cmd_head->string, ft_strlen(g_cmd_head->string));
        write(1, "\n", 1);
    }
}
