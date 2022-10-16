/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:22:48 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/16 15:37:29 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	type_arg_parsing(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<<") == 0 && separator == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

void	connect_loops(t_mini *mini)
{
	t_token	*token;
	t_token	*previous;

	token = mini->start;
	while (token)
	{
		previous = previous_separ(token, NOSKIP);
		if (ft_istype(token, ARG) && hasAtypeOf(previous, "TAI"))
		{
			while (is_last_arg(previous) == 0)
				previous = previous->prev;
			token->prev->next = token->next;
			if (token->next)
				token->next->prev = token->prev;
			token->prev = previous;
			if (previous)
				token->next = previous->next;
			else
			{
				token->next = mini->start;
				previous = token;
			}
			previous->next->prev = token;
			if (mini->start->prev)
				mini->start = mini->start->prev;
			else
				previous->next = token;
		}
		token = token->next;
	}
}

int		next_length(char *line, int *i)
{
	char	c;
	int		count;
	int		j;

	count = 0;
	j = 0;
	c = ' ';
	while ((line[*i + j] != ' ' || c != ' ') && line[*i + j])
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
	}
	return (j - count + 1);
}

t_token	*get_next_token(char *line, int *i)
{
	t_token	*token;
	char	c;
	int		j;

	c = ' ';
	j = 0;
	if (!(token = malloc(sizeof(t_token)))
	|| !(token->str = malloc(sizeof(char) * next_length(line, i))))
		return (NULL);
	while ((line[*i] != ' ' || c != ' ') && line[*i])
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
	return (token);
}

t_token	*tokenizer(char *line, t_mini *mini)
{
	t_token	*previous;
	t_token	*next;
	int		i;

	next = NULL;
	(void)mini;
	previous = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		next = get_next_token(line, &i);
		next->prev = previous;
		if (previous)
			previous->next = next;
		previous = next;
		type_arg_parsing(next, 0);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
