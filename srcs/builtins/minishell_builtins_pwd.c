/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_pwd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	minishell_builtins_pwd(void *sh_, char **cmds)
{
	t_sh	*sh;
	char	path[PATH_MAX];

	UNUSED(cmds);
	sh = (t_sh *)sh_;
	getcwd(path, PATH_MAX);
	ft_putendl(path);
	return (0);
}
