#include "minishell.h"

static int	varlcopy(char *new_arg, const char *env_value, int pos)
{
	int	i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

static void		var_inserting(t_expander *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = getEnvVarValue(arg, ex->j, env, ret);
	if (env_value)
		ex->i += varlcopy(ex->new_arg, env_value, ex->i);
	ft_memdel(env_value);
	if (arg[ex->j] == '?')
		ex->j++;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_valid_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
	else
	{
		if (arg[ex->j - 1] != '?')
			ex->j++;
	}
}

char	*expander(char *arg, t_env *env, int ret)
{
	t_expander	ex;
	int			new_arg_len;

	if (!arg)
		return (NULL);
	new_arg_len = cmdsLenForAlloc(arg, env, ret);
	if (!(ex.new_arg = malloc(BUFF_SIZE)))
		return (NULL);
	ex.i = 0;
	ex.j = 0;
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANDER)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0)
			&& arg[ex.j] != '?')
				ex.new_arg[ex.i++] = '$';
			else
				var_inserting(&ex, arg, env, ret);
		}
		ex.new_arg[ex.i++] = arg[ex.j++];
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}
