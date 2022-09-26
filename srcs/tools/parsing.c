#include "minishell.h"

int		ft_isseparator(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|;", line[i]))
		return (0);
	else if (ft_strchr("<>|;", line[i]) && isQuoteOpen(line, i) == 0)
		return (1);
	else
		return (0);
}

int		transcend_separ(char *line, int i)
{
	if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	else if (line[i] && line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
				&& line[i + 2] && line[i + 2] == '>')
		return (1);
	return (0);
}

int		isQuoteOpen(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

int	is_last_arg(t_token *token)
{
	t_token	*previous;

	if (!token || ft_istype(token, CMD) || ft_istype(token, ARG))
	{
		previous = previous_separ(token, NOSKIP);
		if (!previous || ft_istype(previous, END) || ft_istype(previous, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

int	check_syntax(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (hasAtypeOf(token, "TAI")
		&& (!token->next || hasAtypeOf(token->next, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			if (token->next)
				ft_putstr_fd(token->next->str, STDERR);
			else
				ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			mini->ret = 258;
			return (0);
		}
		if (hasAtypeOf(token, "PE")
		&& (!token->prev || !token->next || hasAtypeOf(token->prev, "TAIPE")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
			ft_putstr_fd(token->str, STDERR);
			ft_putendl_fd("'", STDERR);
			mini->ret = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}
