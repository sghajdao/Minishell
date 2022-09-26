#include "minishell.h"

int	envStrLen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	env_sort(char **tab, int env_len)
{
	char	*tmp;
	int		ordered;
	int		i;

	ordered = 0;
	while (ordered == 0 && tab)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	print_env_sorted(t_env *env)
{
	char	**tab;
	char	*str_env;
	int		i;

	str_env = envToString(env);
	tab = ft_split(str_env, '\n');
	ft_memdel(str_env);
	env_sort(tab, envStrLen(tab));
	i = 0;
	while (tab[i])
	{
		ft_putstr("declare -x ");
		ft_putendl(tab[i]);
		i++;
	}
	freeing_tab(tab);
}
