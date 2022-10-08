#include "minishell.h"

void	output(t_mini *mini, t_token *token, int type)
{
	char	*file;

	if (mini->type_quotes == 0 || mini->type_quotes == 1)
		file = expander(token->str, mini);
	else
		file = ft_strdup(token->str);
	close_fd(mini->fdout);
	if (type == TRUNC)
		mini->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (!access(file, F_OK) && access(file, W_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(file, STDERR);
		ft_putendl_fd(": permission denied", STDERR);
		mini->no_exec = 1;
		mini->ret = 1;
		return ;
	}
	dup2(mini->fdout, STDOUT);
	free(file);
}

void	input(t_mini *mini, t_token *token)
{
	char	*file;

	if (mini->type_quotes == 0 || mini->type_quotes == 1)
		file = expander(token->str, mini);
	else
		file = ft_strdup(token->str);
	close_fd(mini->fdin);
	mini->fdin = open(file, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(file, STDERR);
		if (access(file, F_OK) == -1)
			ft_putendl_fd(": No such file or directory", STDERR);
		else if (!access(file, F_OK) && access(file, R_OK) == -1)
			ft_putendl_fd(": permission denied", STDERR);
		mini->no_exec = 1;
		mini->ret = 1;
		return ;
	}
	dup2(mini->fdin, STDIN);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		write(2, "\n", 1);
	}
}

void	heredoc(t_mini *mini, t_token *token)
{
	char	*line;
	int		fd[2];
	int		old;

	line = NULL;
	old = dup(0);
	pipe(fd);
	signal(SIGINT, handler);
	while (1)
	{
		free(line);
		line = readline("> ");
		if (!line)
		{
			mini->ret = 1;
			mini->no_exec = 1;
			break ;
		}
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
	close(old);
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
