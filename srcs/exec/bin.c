#include "minishell.h"

int	print_error(char *path)
{
	int	fd;
	int	ret;
	DIR	*folder;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (folder == NULL && fd == -1))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	close_fd(fd);
	return (ret);
}

int	fork_proces(char *path, char **args, t_env *env, t_mini *mini)
{
	int		ret;
	char	**env_array;
	char	*ptr;

	ret = SUCCESS;
	g_sig.pid = fork();
	run_signals(2);
	if (g_sig.pid == 0)
	{
		ptr = env_to_string(env);
		env_array = ft_split(ptr, '\n');
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = print_error(path);
		freeing_tab(env_array);
		freeing_token(mini->start);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	if (ret == 32512 || ret == 32256)
		ret = ret / 256;
	else
		ret = !!ret;
	return (ret);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char	*check_directory(char *bin, char *command)
{
	char			*path;
	DIR				*folder;
	struct dirent	*item;

	folder = opendir(bin);
	path = NULL;
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(folder);
	return (path);
}

int	executor(char **args, t_env *env, t_mini *mini)
{
	char	**bin;
	char	*path;
	int		i;
	int		ret;

	i = 0;
	ret = UNKNOWN_COMMAND;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (fork_proces(args[0], args, env, mini));
	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = check_directory(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_directory(bin[i++], args[0]);
	if (path != NULL)
		ret = fork_proces(path, args, env, mini);
	else
		ret = fork_proces(args[0], args, env, mini);
	freeing_tab(bin);
	ft_memdel(path);
	return (ret);
}
