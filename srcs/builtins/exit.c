#include "minishell.h"

void	ft_exit(t_mini *mini, char **cmd)
{
	ft_putendl_fd("exit ", STDERR);
	if (cmd[1] && cmd[2] && ft_strisnum(cmd[1]))
	{
		mini->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		return ;
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		mini->ret = 255;
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1])
		mini->ret = ft_atoi(cmd[1]);
	else
		mini->ret = 0;
	mini->exit = 1;
}
