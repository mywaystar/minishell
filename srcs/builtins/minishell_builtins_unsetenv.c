/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_unsetenv.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/24 19:49:01 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		minishell_builtins_unsetenv_error_missing(void)
{
	ft_putendl_fd("unsetenv: You must provide a variable", 2);
	return (2);
}

int		minishell_builtins_unsetenv_error_two_many(void)
{
	ft_putendl_fd("unsetenv: Two many arguments", 2);
	return (2);
}

void	minishell_builtins_unsetenv_free(void *content, size_t size)
{
	t_env		*env;

	UNUSED(size);
	env = content;
	if (!content)
		return ;
	if (env->var)
		free(env->var);
	if (env->value)
		free(env->value);
	free(env);
}

int		minishell_builtins_unsetenv(void *sh_, char **cmds)
{
	t_sh		*sh;
	t_list		*cur;
	t_env		*env;
	int			i;

	sh = (t_sh *)sh_;
	if (!cmds[1])
		return (minishell_builtins_unsetenv_error_missing());
	if (cmds[2])
		return (minishell_builtins_unsetenv_error_two_many());
	i = 0;
	cur = sh->env_list;
	while (cur)
	{
		env = cur->content;
		cur = cur->next;
		if (ft_strcmp(cmds[1], env->var) == 0)
		{
			ft_lstdel_at(&sh->env_list, i, &minishell_builtins_unsetenv_free);
			return (0);
		}
		i++;
	}
	return (0);
}
