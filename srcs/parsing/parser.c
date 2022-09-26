#include "minishell.h"

void	parser(t_mini *mini)
{
	char	*line;
	t_token	*token;

	line = lexer(mini);
	if (!line)
		return ;
	mini->start = tokenizer(line);
	ft_memdel(line);
	connect_loops(mini);
	token = mini->start;
	while (token)
	{
		if (ft_istype(token, ARG))
			type_arg_parsing(token, 0);
		token = token->next;
	}
}
