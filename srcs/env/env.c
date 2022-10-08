#include "minishell.h"

size_t	envlen(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*envToString(t_env *lst)
{
	int		i;
	int		j;
	char	*env;

	if (!(env = malloc(BUFF_SIZE)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				j++;
				i++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int	init_env(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!(env = malloc(BUFF_SIZE)))
		return (1);
	if (!*env_array)
	{
		env->value = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
		env->next = malloc(sizeof(t_env));
		env->next->value = ft_strdup("SHLVL=1");
		env->next->next = malloc(sizeof(t_env));
		env->next->next->value = ft_strjoin("PWD=", get_pwd());
		env->next->next->next = NULL;
		mini->env = env;
		return (0);
	}
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}

int	init_copy_env(t_mini *mini, char **env_array)
{
	int		i;
	t_env	*env;
	t_env	*new;

	if (!(env = malloc(sizeof(t_env))))
		return (1);
	if (!*env_array)
	{
		env->value = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
		env->next = malloc(sizeof(t_env));
		env->next->value = ft_strdup("SHLVL=1");
		env->next->next = malloc(sizeof(t_env));
		env->next->next->value = ft_strjoin("PWD=", get_pwd());
		env->next->next->next = NULL;
		mini->copy_env = env;
		return (0);
	}
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->copy_env = env;
	i = 1;
	while (env_array && env_array[0] && env_array[i])
	{
		if (!(new = malloc(sizeof(t_env))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
