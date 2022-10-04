#include "minishell.h"

void	close_fd(int fd)
{
	if (fd > 0)
		close(fd);
}

void	dup2_IN_OUT(t_mini *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}

void	close_multi_fds(t_mini *mini)
{
	close_fd(mini->fdin);
	close_fd(mini->fdout);
	close_fd(mini->pipin);
	close_fd(mini->pipout);
}

void	reset_all_fds(t_mini *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->pid = -1;
}
