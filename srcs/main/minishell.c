#include "minishell.h"

void	exec_and_redir(t_mini *mini, t_token *token)
{
	t_token	*previous;
	t_token	*next;
	int		pipe;

	previous = previous_separ(token, NOSKIP);
	next = next_separator(token, NOSKIP);
	pipe = 0;
	if (ft_istype(previous, TRUNC))
		output(mini, token, TRUNC);
	else if (ft_istype(previous, APPEND))
		output(mini, token, APPEND);
	else if (ft_istype(previous, HEREDOC))
	{
		heredoc(mini, token);
	}
	else if (ft_istype(previous, INPUT))
		input(mini, token);
	else if (ft_istype(previous, PIPE))
		pipe = minipipe(mini);
	if (next && pipe != 1)
		exec_and_redir(mini, next->next);
	if ((ft_istype(previous, PIPE) || !previous)
		&& pipe != 1 && mini->no_exec == 0)
		execution_center(mini, token);
}

void	minishell(t_mini *mini)
{
	t_token	*token;
	int		status;

	token = last_token(mini->start, NOSKIP);
	if (hasAtypeOf(mini->start, "THAI"))
		token = mini->start->next;
	while (mini->exit == 0 && token)
	{
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
		exec_and_redir(mini, token);
		dup2_IN_OUT(mini);
		close_multi_fds(mini);
		reset_all_fds(mini);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (mini->last == 0)
			mini->ret = status;
		if (mini->parent == 0)
		{
			freeing_token(mini->start);
			exit(mini->ret);
		}
		mini->no_exec = 0;
		token = last_token(token, SKIP);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.exit = 0;
	mini.ret = 0;
	mini.no_exec = 0;
	reset_all_fds(&mini);
	init_env(&mini, env);
	init_copy_env(&mini, env);
	increment_shlvl(mini.env);
	while (mini.exit == 0)
	{
		sig_init();
		parser(&mini);
		if (mini.start != NULL && check_syntax(&mini, mini.start))
			minishell(&mini);
		freeing_token(mini.start);
	}
	freeing_env(mini.env);
	freeing_env(mini.copy_env);
	return (mini.ret);
}
