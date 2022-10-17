/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:22:17 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/17 09:30:42 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*alloc_space(char *line, t_mini *mini)
{
	char	*new;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (ft_isseparator(line, i, mini))
			count++;
		i++;
	}
	new = malloc(sizeof(char) * (i + 2 * count + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	*add_space_between_cmds(char *line, t_mini *mini)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = alloc_space(line, mini);
	while (new && line[i])
	{
		if (isQuoteOpen(line, i, mini) == 0 && ft_isseparator(line, i, mini))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (isQuoteOpen(line, i, mini) == 0 && \
			(line[i] == '>' || line[i] == '<'))
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

int	check_quote(t_mini *mini, char **line)
{
	if (isQuoteOpen(*line, 2147483647, mini))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		mini->ret = 2;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

char	*lexer(t_mini *mini)
{
	char	*line;

	run_signals(1);
	line = readline("MINISHELL$ ");
	if (line && *line)
		add_history(line);
	else if (!line)
		run_signals(3);
	if (g_sig.sigint == 1)
		mini->ret = g_sig.exit_status;
	if (check_quote(mini, &line))
		return (NULL);
	line = addSpaceBetweenCmds(line, mini);
	return (line);
}
