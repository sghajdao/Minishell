/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:27:30 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/13 12:27:31 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	print_cd_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static char	*getPathFromEnv(t_env *env, const char *var, size_t len)
{
	int		i;
	int		j;
	int		s_alloc;
	char	*oldpwd;

	while (env->next != NULL && env)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			if (!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->value[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_mini *mini)
{
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	if (already_exist_in_env(mini->env, oldpwd) == 0 && already_exist_in_env(mini->env, "PWD"))
		add_to_env(oldpwd, mini->env);
	else if (already_exist_in_env(mini->env, "PWD") == 0 && already_exist_in_env(mini->env, oldpwd) == 0)
		add_to_env("OLDPWD=", mini->env);
	if (already_exist_in_env(mini->copy_env, oldpwd) == 0 && already_exist_in_env(mini->copy_env, "PWD"))
		add_to_env(oldpwd, mini->copy_env);
	else if (already_exist_in_env(mini->copy_env, "PWD") == 0 && already_exist_in_env(mini->copy_env, oldpwd) == 0)
		add_to_env("OLDPWD=", mini->copy_env);
	ft_memdel(oldpwd);
	return (SUCCESS);
}

static int	change_directory(int option, t_env *env, t_mini *mini)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(mini);
		env_path = getPathFromEnv(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", STDERR);
		if (!env_path)
			return (ERROR);
	}
	else if (option == 1)
	{
		env_path = getPathFromEnv(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
		if (!env_path)
			return (ERROR);
		update_oldpwd(mini);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

void	updat_pwd(t_mini *mini)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return ;
	already_exist_in_env(mini->env, pwd);
	already_exist_in_env(mini->copy_env, pwd);
	ft_memdel(pwd);
}

void ft_print_msg(void)
{
	if (!getcwd(NULL, 0))
		printf("cd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory\n");
}

int	ft_cd(char **args, t_mini *mini)
{
	int	cd_ret;

	if (!args[1])
		return (change_directory(0, mini->env, mini));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = change_directory(1, mini->env, mini);
	if (ft_strcmp(args[1], ".") == 0)
		ft_print_msg();
	else
	{
		update_oldpwd(mini);
		cd_ret = chdir(args[1]);
		updat_pwd(mini);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_cd_error(args);
	}
	return (cd_ret);
}
