#include "minishell.h"

static	int	how_many_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	ft_echo(char **args)
{
	int	n_option;
	int	i;

	n_option = 0;
	i = 1;
	if (how_many_args(args) > 1)
	{
		while (args[i] && (ft_strcmp(args[i], "-n") == 0 || ft_strcmpall(args[i], 1, 'n') == 0))
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}
