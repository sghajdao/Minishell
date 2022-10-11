#include "minishell.h"

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*p;

	if (!*alst)
		*alst = new;
	else
	{
		p = *alst;
		while (p -> next)
			p = p -> next;
		p -> next = new;
	}
}

t_env	*ft_lstnew_env(void *content)
{
	t_env	*c;

	c = (t_env *)malloc(BUFF_SIZE);
	if (!c)
		return (NULL);
	c -> value = ft_strdup(content);
	c -> next = NULL;
	return (c);
}

static void	if_no_env(t_env **env, t_mini *mini, int flag)
{
	char	*pwd;

	pwd = ft_strjoin("PWD=", get_pwd());
	env = malloc(BUFF_SIZE);
	ft_memset(env, 0, BUFF_SIZE);
	ft_lstadd_back_env(env, ft_lstnew_env("PATH=/usr/bin:/bin:/usr/sbin:/sbin"));
	ft_lstadd_back_env(env, ft_lstnew_env("SHLVL=1"));
	ft_lstadd_back_env(env, ft_lstnew_env(pwd));
	if (flag == 0)
		mini->env = *env;
	else
		mini->copy_env = *env;
}

int	init_env(t_mini *mini, char **env_array)
{
	t_env	*env;
	int		i;

	i = 0;
	if (!*env_array)
	{
		if_no_env(&env, mini, 0);
		return (0);
	}
	env = malloc(BUFF_SIZE);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
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

	i = 0;
	if (!*env_array)
	{
		if_no_env(&env, mini, 1);
		return (0);
	}
	env = malloc(BUFF_SIZE);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
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
