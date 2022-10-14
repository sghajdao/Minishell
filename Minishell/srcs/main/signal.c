#include "minishell.h"

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{	
		write (1, "\033[1A\033[11Cexit\n", 14);
		//ft_putendl_fd("exit", STDOUT);
		exit(0);
	}
}

void	restore_prompt(int sig)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_sig.exit_status = 1;
	g_sig.sigint = 1;
	(void)sig;
}

void	ctrl_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig.exit_status = 1;
	g_sig.sigint = 1;
}

void	back_slash(int sig)
{
	g_sig.exit_status = 1;
	g_sig.sigint = 1;
	(void)sig;
}
