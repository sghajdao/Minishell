#include "minishell.h"

//void	sig_int(int code)
//{
//	(void)code;
//	if (g_sig.pid == 0)
//	{
//		ft_putstr_fd("\b\b  ", STDERR);
//		ft_putstr_fd("\n", STDERR);
//		g_sig.exit_status = 1;
//	}
//	else
//	{
//		ft_putstr_fd("\n", STDERR);
//		g_sig.exit_status = 130;
//	}
//	g_sig.sigint = 1;
//}
//
//void	sig_quit(int code)
//{
//	char	*nbr;
//
//	nbr = ft_itoa(code);
//	if (g_sig.pid != 0)
//	{
//		ft_putstr_fd("Quit: ", STDERR);
//		ft_putendl_fd(nbr, STDERR);
//		g_sig.exit_status = 131;
//		g_sig.sigquit = 1;
//	}
//	else
//		ft_putstr_fd("\b\b  \b\b", STDERR);
//	ft_memdel(nbr);
//}
//
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
		ft_putendl_fd("exit", STDOUT);
		exit(0);
	}
}

void	restore_prompt(int sig)
{
	g_sig.sigint = 1;
	g_sig.exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_sig.exit_status = 1;
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	back_slash(int sig)
{
	g_sig.exit_status = 0;
	(void)sig;
}