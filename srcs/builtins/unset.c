/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 08:22:53 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/18 08:24:14 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_error(char **a)
{
	int	i;

	i = 1;
	while (a[i])
	{
		if (ft_isdigit(a[i][0]))
		{
			ft_putstr_fd("unset: not a valid identifier: ", STDERR);
			ft_putendl_fd(a[i], STDERR);
		}
		else if (!ft_charscmp(a[i], "+-*/=()~`!@#$^"))
		{
			ft_putstr_fd("unset: not a valid identifier: ", STDERR);
			ft_putendl_fd(a[i], STDERR);
		}
		i++;
	}
}

void	unset_middle(t_mini *mini, char *a, int flag)
{
	t_env	*current;
	t_env	*temp;

	if (flag == 0)
		current = mini->copy_env;
	else
		current = mini->env;
	while (current->next != NULL)
	{
		if (!ft_strncmp(a, current->next->value, ft_strlen(a)) && \
			ft_strlen(a) == env_name_size(current->next->value))
		{
			temp = current->next;
			current->next = current->next->next;
			ft_memdel(temp->value);
			ft_memdel(temp);
			break ;
		}
		else
			current = current->next;
	}
}

int	secret_unset(char **a, t_mini *mini)
{
	t_env	*temp;
	int		i;

	ft_error(a);
	i = 1;
	while (a[i])
	{
		if (!ft_strncmp(a[i], mini->copy_env->value, ft_strlen(a[i])) && \
				ft_strlen(a[i]) == env_name_size(mini->copy_env->value))
		{
			temp = mini->copy_env;
			mini->copy_env = mini->copy_env->next;
			ft_memdel(temp->value);
			ft_memdel(temp);
		}
		else
			unset_middle(mini, a[i], 0);
		i++;
	}
	return (0);
}

int	ft_unset(char **a, t_mini *mini)
{
	t_env	*temp;
	int		i;

	secret_unset(a, mini);
	i = 1;
	while (a[i])
	{
		if (!ft_strncmp(a[i], mini->env->value, ft_strlen(a[i])) && \
				ft_strlen(a[i]) == env_name_size(mini->env->value))
		{
			temp = mini->env;
			mini->env = mini->env->next;
			ft_memdel(temp->value);
			ft_memdel(temp);
		}
		else
			unset_middle(mini, a[i], 1);
		i++;
	}
	return (0);
}
