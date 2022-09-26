#include "minishell.h"

char	*alloc_space(char *line)
{
	char	*new;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (ft_isseparator(line, i))
			count++;
		i++;
	}
	if (!(new = malloc(sizeof(char) * (i + 2 * count + 1))))
		return (NULL);
	return (new);
}

char	*addSpaceBetweenCmds(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = alloc_space(line);
	while (new && line[i])
	{
		if (isQuoteOpen(line, i) != 2 && line[i] == '$' && i && line[i - 1] != '\\')
			new[j++] = (char)(-line[i++]);
		else if (isQuoteOpen(line, i) == 0 && ft_isseparator(line, i))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (isQuoteOpen(line, i) == 0 && (line[i] == '>' || line[i] == '<'))
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

int		check_quote(t_mini *mini, char **line)
{
	if (isQuoteOpen(*line, 2147483647))
	{
		ft_putendl_fd("minishell: syntax error with open quotes", STDERR);
		ft_memdel(*line);
		mini->ret = 2;
		mini->start = NULL;
		return (1);
	}
	return (0);
}

char    *lexer(t_mini *mini)
{
    char    *line;

    run_signals(1);
	line = readline("MINISHELL$ ");
	if (line && *line)
		add_history(line);
	else if (!line)
		run_signals(3);
	if (check_quote(mini, &line))
		return (NULL);
	line = addSpaceBetweenCmds(line);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
    return (line);
}
