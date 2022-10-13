/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:29:41 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/13 12:29:42 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (SUCCESS);
	}
	else
	{
		pwd = get_env_value("PWD", mini->env);
		printf("%s\n", pwd);
		free(pwd);
		return (ERROR);
	}
}

char	*get_pwd(void)
{
	char	*cwd;

	cwd = malloc(BUFF_SIZE);
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, PATH_MAX))
		return (cwd);
	else
		return (NULL);
}
