#include "minishell.h"

t_token	*next_separator(t_token *token, int skip)
{
	if (skip && token)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*previous_separ(t_token *token, int skip)
{
	if (skip && token)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*last_token(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD)
			token = token->next;
	}
	return (token);
}
