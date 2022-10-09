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

void	add_quotes_to_value(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		ft_putstr("declare -x ");
		j = 0;
		while (tab[i][j] != '=' && tab[i][j])
		{
			write(1, &tab[i][j], 1);
			j++;
		}
		write(1, "=\"", 2);
		while (tab[i][++j])
			write(1, &tab[i][j], 1);
		write(1, "\"\n", 2);
		i++;
	}
}

void	print_env_sorted(t_env *env)
{
	char	**tab;
	char	*str_env;

	str_env = env_to_string(env);
	tab = ft_split(str_env, '\n');
	ft_memdel(str_env);
	env_sort(tab, envStrLen(tab));
	add_quotes_to_value(tab);
	freeing_tab(tab);
}
