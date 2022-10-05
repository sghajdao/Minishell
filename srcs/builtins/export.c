#include "minishell.h"

static int	print_error(int error, const char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == -3 || error == 0)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while ((arg[i] != '=' || error == -3) && arg[i])
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	add_to_env(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	if (!(new = malloc(sizeof(t_env))))
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

void	get_env_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && (ft_strlen(src) < BUFF_SIZE) && src[i] != '=' && src[i] != '+')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	already_exist_in_env(t_env *env, char *args)
{
	char	env_name[BUFF_SIZE];
	char	var_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (SUCCESS);
}

void	concat(char **env, t_env *e)
{
	char	*to_add;
	char	name[BUFF_SIZE];
	char	*old_value;
	char	*copy;

	to_add = malloc(sizeof(char) * ft_strlen(ft_strchr(*env, '+')));
	to_add = ft_strdup(ft_strchr(*env, '+') + 2);
	get_env_name(name, *env);
	old_value = get_env_value(name, e);
	copy = ft_strjoin(name, "=");
	free(*env);
	*env = ft_strjoin(copy, old_value);
	free(old_value);
	free(copy);
	copy = ft_strjoin(*env, to_add);
	free(to_add);
	free(*env);
	*env = ft_strdup(copy);
	free(copy);
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	int	error_ret;
	int	new_env;
	int	i;

	new_env = 0;
	if (!args[1])
	{
		print_env_sorted(secret);
		return (SUCCESS);
	}
	else
	{
		i = 1;
		while (args[i])
		{
			if (ft_search(args[i], '+'))
				concat(&args[i], env);
			error_ret = is_valid_env_str(args[i]);
			if (args[i][0] == '=')
				error_ret = -3;
			if (error_ret <= 0)
				return (print_error(error_ret, args[i]));
			if (error_ret == 2)
			{
				new_env = already_exist_in_env(secret, args[i]);
				if (new_env == 0)
					add_to_env(args[i], secret);
			}
			else
				new_env = already_exist_in_env(env, args[i]);
			if (new_env == 0)
			{
				if (error_ret == 1)
					add_to_env(args[i], env);
			}
			new_env = already_exist_in_env(secret, args[i]);
			if (new_env == 0)
				add_to_env(args[i], secret);
			i++;
		}
	}
	return (SUCCESS);
}
