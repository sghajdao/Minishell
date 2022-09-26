#include "minishell.h"

static size_t	env_name_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	delete_node(t_mini *mini, t_env *env)
{
	if (env->next == NULL && mini->env == env)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	ft_unset(char **a, t_mini *mini)
{
	t_env	*tmp;
	t_env	*env;

	env = mini->env;
	if (!(a[1]))
		return (SUCCESS);
	if (ft_strncmp(a[1], env->value, env_name_size(env->value)) == 0)
	{
		if (env->next)
			mini->env = env->next;
		else
			mini->env = mini->env;
		delete_node(mini, env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		if (ft_strncmp(a[1], env->next->value, env_name_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			delete_node(mini, env->next);
			env->next = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}
