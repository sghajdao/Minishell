#include "minishell.h"

size_t	envlen(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*env_to_string(t_env *lst)
{
	int		i;
	int		j;
	char	*env;

	if (!(env = malloc(BUFF_SIZE)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				j++;
				i++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

void	ft_lstadd_front_env(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*p;

	if (!*alst)
		*alst = new;
	else
	{
		p = *alst;
		while (p -> next)
			p = p -> next;
		p -> next = new;
	}
}

t_env	*ft_lstnew_env(void *content)
{
	t_env	*c;

	c = (t_env *)malloc(BUFF_SIZE);
	if (!c)
		return (NULL);
	c -> value = ft_strdup(content);
	c -> next = NULL;
	return (c);
}
