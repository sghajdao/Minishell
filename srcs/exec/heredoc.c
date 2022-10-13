/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:09:05 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/13 12:09:06 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		write(2, "\n", 1);
	}
}

static void	add_t_at_end(char **file)
{
	char	*copy;

	while (!access(*file, F_OK))
    {
        copy = ft_strdup(*file);
        free(*file);
        *file = ft_strjoin(copy, "t");
        free(copy);
    }
}

static void    read_until_delimiter(t_mini *mini, t_token *tmp, char *file_name, int fd)
{
    char	*line;

    while (1)
	{
		line = readline("> ");
		if (!line)
		{
			mini->ret = 1;
			mini->no_exec = 1;
			break ;
		}
		if (!ft_strcmp(line, tmp->next->str))
		{
			mini->heredoc = 1;
            free(tmp->str);
            free(line);
			tmp->str = ft_strdup("<");
			tmp->next->str = file_name;
			break;
		}
        ft_putendl_fd(line, fd);
        free(line);
	}
}

void	ft_heredoc(t_mini *mini, t_token **lst)
{
	char *file_name;
	t_token	*tmp;
	int fd;
	tmp = *lst;

	while (tmp)
	{
		if (tmp && tmp->type == 5)
		{
			if (!check_syntax(mini, tmp))
				return ;
            file_name = ft_strdup("/tmp/.txt");
			add_t_at_end(&file_name);
			fd = open(file_name , O_CREAT | O_TRUNC | O_WRONLY, 0644);
			ft_lstadd_back(&mini->file, ft_lstnew(file_name));
			mini->heredoc = 1;
			signal(SIGINT, handler);
            read_until_delimiter(mini, tmp, file_name, fd);
		}
		tmp = tmp->next;
	}
}
