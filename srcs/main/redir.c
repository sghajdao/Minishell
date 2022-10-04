#include "minishell.h"

void	output(t_mini *mini, t_token *token, int type)
{
	close_fd(mini->fdout);
	if (type == TRUNC)
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fdout = open(token->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (!access(token->str, F_OK) && access(token->str, W_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		ft_putendl_fd(": permission denied", STDERR);
		mini->no_exec = 1;
		mini->ret = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
}

void	input(t_mini *mini, t_token *token)
{
	close_fd(mini->fdin);
	mini->fdin = open(token->str, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(token->str, STDERR);
		if (access(token->str, F_OK) == -1)
			ft_putendl_fd(": No such file or directory", STDERR);
		else if (!access(token->str, F_OK) && access(token->str, R_OK) == -1)
			ft_putendl_fd(": permission denied", STDERR);
		mini->no_exec = 1;
		mini->ret = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}

void	heredoc(t_mini *mini, t_token *token)
{
	char	*line;
	int		fd[2];

	line = NULL;
	//(void)mini;
	dup2(mini->fdin, 0);
	pipe(fd);
	while (1)
	{
		free(line);
		//line = get_next_line(0);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, token->str, ft_strlen(token->str)) == 0 \
				&& line[ft_strlen(token->str)] == '\0')
			break ;
		ft_putendl_fd(line, fd[1]);
		if (ft_strlen(line))
			free(line);
		line = NULL;
	}
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	free(line);
}

int	minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	run_signals(2);
	if (pid == 0)
	{
		close_fd(pipefd[1]);
		dup2(pipefd[0], STDIN);
		mini->pipin = pipefd[0];
		mini->parent = 0;
		mini->pid = -1;
		mini->no_exec = 0;
		return (2);
	}
	else
	{
		close_fd(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		mini->pipout = pipefd[1];
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}
}
