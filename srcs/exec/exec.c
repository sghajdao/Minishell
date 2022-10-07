#include "minishell.h"

char	**cmd_tab(t_token *start)
{
	int		i;
	char	**tab;
	t_token	*token;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * i)))
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	execution_center(t_mini *mini, t_token *token)
{
	int		i;
	char	**cmd;

	if (mini->charge == 0)
		return ;
	i = 0;
	cmd = cmd_tab(token);
	while (cmd && cmd[i])
	{
		if (mini->type_quotes == 0 || mini->type_quotes == 1)
			cmd[i] = expander(cmd[i], mini->env, mini->ret);
		else
			cmd[i] = ft_strdup(cmd[i]);
		i++;
	}
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		ft_exit(mini, cmd);
	else if (cmd && is_builtin_cmd(cmd[0]))
		mini->ret = builtin_executor(cmd, mini);
	else if (cmd)
		mini->ret = executor(cmd, mini->env, mini);
	freeing_tab(cmd);
	close_fd(mini->pipin);
	close_fd(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}
