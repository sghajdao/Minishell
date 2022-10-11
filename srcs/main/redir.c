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

	line = NULL;
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
	free(line);
}

void	ft_heredoc(t_token **lst)
{
	static int i;
	char *file_name;
	t_token	*tmp;
	char *line;
	int fd;
	tmp = *lst;

	while (tmp)
	{
		if (tmp && tmp->type == 5)
		{
			file_name = ft_strjoin("/tmp/text", ft_itoa(i));
			fd = open(file_name , O_APPEND | O_WRONLY | O_CREAT, 0644);
			while (1)
			{
				line = readline("> ");
				if (!ft_strcmp(line, tmp->next->str))
				{
						// leaks here
						tmp->type = INPUT;
						tmp->str = ft_strdup("<");
						tmp->next->str = file_name;
						i++;
						break;
				}
				write(fd, ft_strjoin(line, ft_strdup("\n")), ft_strlen(line) + 1);
			}
		}
		tmp = tmp->next;
	}
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
