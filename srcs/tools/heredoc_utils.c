/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:37:51 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/19 12:58:17 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	stop_reading(t_mini *mini, t_token *tmp, char *file_name)
{
	mini->heredoc = 1;
	free (tmp->str);
	free (tmp->next->str);
	tmp->str = ft_strdup("<");
	if (!tmp->str)
		return (ERROR);
	tmp->next->str = file_name;
	return (SUCCESS);
}

void	unlinking_heredoc_files(t_mini *mini)
{
	t_list	*copy;

	if (mini->heredoc)
	{
		while (mini->file)
		{
			copy = mini->file;
			unlink(mini->file->content);
			mini->file = mini->file->next;
			free(copy->content);
			free(copy);
		}
	}
}
