#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
//# include <linux/limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define HEREDOC 5
# define INPUT 6
# define PIPE 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANDER -36
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	t_token	*start;
	t_env	*env;
	t_env	*copy_env;
	int		in;
	int		out;
	int		fdin;
	int		fdout;
	int		pipin;
	int		pipout;
	int		pid;
	int		charge;
	int		parent;
	int		last;
	int		ret;
	int		exit;
	int		no_exec;
}	t_mini;

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
	int		exit_status;
	pid_t	pid;
}	t_sig;

typedef struct s_expander
{
	char	*new_arg;
	int		i;
	int		j;
}	t_expander;

/*
** MINISHELL
*/
void	output(t_mini *mini, t_token *token, int type);
void	input(t_mini *mini, t_token *token);
void	heredoc(t_mini *mini, t_token *token);
int		minipipe(t_mini *mini);
char	*expander(char *arg, t_env *env, int ret);

/*
** EXEC
*/
void	execution_center(t_mini *mini, t_token *token);
int		executor(char **args, t_env *env, t_mini *mini);
int		builtin_executor(char **args, t_mini *mini);
int		is_builtin_cmd(char	*command);

/*
** BUILTINS
*/
int		ft_echo(char **args);
int		ft_cd(char **args, t_env *env);
int		ft_pwd(void);
char	*get_pwd(void);
int		ft_export(char **args, t_env *env, t_env *secret);
int		ft_env(t_env *env);
int		add_to_env(const char *value, t_env *env);
void	get_env_name(char *dest, const char *src);
int		already_exist_in_env(t_env *env, char *args);
int		ft_unset(char **args, t_mini *mini);
void	ft_exit(t_mini *mini, char **cmd);

/*
** PARSING
*/
void	parser(t_mini *mini);
t_token	*tokenizer(char *line);
void	connect_loops(t_mini *mini);
int		is_last_arg(t_token *token);
int		isQuoteOpen(char *line, int index);
void	type_arg_parsing(t_token *token, int separator);
int		ft_isseparator(char *line, int i);
int		transcend_separ(char *line, int i);
char    *lexer(t_mini *mini);

/*
** ENV
*/
int		check_syntax(t_mini *mini, t_token *token);
char	*envToString(t_env *lst);
int		init_env(t_mini *mini, char **env_array);
int		init_copy_env(t_mini *mini, char **env_array);
char	*get_env_value(char *arg, t_env *env);
char	*env_value(char *env);
int		env_val_length(const char *env);
int		is_valid_env_char(int c);
int		is_valid_env_str(const char *env);
void	print_env_sorted(t_env *env);
void	increment_shlvl(t_env *env);
size_t	envlen(t_env *lst);

/*
** FD TOOLS
*/
void	dup2_IN_OUT(t_mini *mini);
void	close_multi_fds(t_mini *mini);
void	close_fd(int fd);
void	reset_all_fds(t_mini *mini);

/*
** FREE TOOLS
*/
void	freeing_token(t_token *start);
void	freeing_env(t_env *env);
void	freeing_tab(char **tab);

/*
** TOKEN TOOLS
*/
t_token	*next_separator(t_token *token, int skip);
t_token	*previous_separ(t_token *token, int skip);
t_token	*last_token(t_token *token, int skip);

/*
** TYPE TOOLS
*/
int		ft_istype(t_token *token, int type);
int		hasAtypeOf(t_token *token, char *types);
int		has_type(t_token *token, int type);
int		has_pipe(t_token *token);
t_token	*next_type(t_token *token, int type, int skip);

/*
** EXPANDER
*/
int		rtn_size(int ret);
int		getExpandedValueLen(const char *arg, int pos, t_env *env, int ret);
int		cmdsLenForAlloc(const char *arg, t_env *env, int ret);
char	*getEnvVarValue(const char *arg, int pos, t_env *env, int ret);

/*
** SIGNAL
*/
void	sig_int(int code);
void	sig_quit(int code);
void	sig_init(void);
void	run_signals(int sig);
void	restore_prompt(int sig);
void	ctrl_c(int sig);
void	back_slash(int sig);

t_sig g_sig;

#endif
