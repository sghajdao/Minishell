#include "minishell.h"

static void	if_no_env(t_env **env, t_mini *mini, int flag)
{
	char	*pwd;
	char	*get;

	get = get_pwd();
	pwd = ft_strjoin("PWD=", get);
	free(get);
	env = malloc(BUFF_SIZE);
	ft_memset(env, 0, BUFF_SIZE);
	ft_lstadd_back_env(env, ft_lstnew_env("PATH=/usr/bin:/bin:/usr/sbin:/sbin"));
	ft_lstadd_back_env(env, ft_lstnew_env("SHLVL=0"));
	ft_lstadd_back_env(env, ft_lstnew_env(pwd));
	free(pwd);
	if (flag == 0)
		mini->env = *env;
	else
		mini->copy_env = *env;
}

int	init_env(t_mini *mini, char **env_array)
{
	t_env	*env;
	int		i;

	i = 1;
	if (!*env_array)
	{
		if_no_env(&env, mini, 0);
		return (0);
	}
	env = ft_lstnew_env(env_array[0]);
	mini->env = env;
	while (env_array[i])
	{
		if (!ft_strncmp(env_array[i], "OLDPWD=", 7))
		{
			i++;
			continue ;
		}
		ft_lstadd_back_env(&env, ft_lstnew_env(env_array[i]));
		i++;
	}
	return (0);
}

int	init_copy_env(t_mini *mini, char **env_array)
{
	t_env	*env;
	int		i;

	i = 1;
	if (!*env_array)
	{
		if_no_env(&env, mini, 1);
		return (0);
	}
	env = ft_lstnew_env(env_array[0]);
	mini->copy_env = env;
	while (env_array[i])
	{
		if (!ft_strncmp(env_array[i], "OLDPWD=", 7))
		{
			i++;
			continue ;
		}
		ft_lstadd_back_env(&env, ft_lstnew_env(env_array[i]));
		i++;
	}
	return (0);
}
