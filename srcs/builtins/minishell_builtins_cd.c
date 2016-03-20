/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_cd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/03/15 13:10:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int   minishell_builtins_cd_error_no_file_directory(char *path)
{
  ft_putstr_fd("cd: ", 2);
  ft_putstr_fd(path, 2);
  ft_putstr_fd(": No such file or directory\n", 2);
  return (2);
}

int   minishell_builtins_cd_error_not_directory(char *path)
{
  ft_putstr_fd("cd: ", 2);
  ft_putstr_fd(path, 2);
  ft_putstr_fd(": Not a directory\n", 2);
  return (2);
}

int   minishell_builtins_cd_error_permission(char *path)
{
  ft_putstr_fd("cd: ", 2);
  ft_putstr_fd(path, 2);
  ft_putstr_fd(": Permission denied\n", 2);
  return (2);
}

void  minishell_builtins_cd_update_path(t_sh *sh, char *old_path, char *path)
{
  char  *cmds[4];

  UNUSED(sh);
  //UNUSED(old_path);
  cmds[0] = ft_strdup("setenv");
  cmds[1] = ft_strdup("OLDPWD");
  cmds[2] = old_path;
  cmds[3] = NULL;
  minishell_builtins_setenv(sh, cmds);
  cmds[0] = ft_strdup("setenv");
  cmds[1] = ft_strdup("PWD");
  cmds[2] = path;
  minishell_builtins_setenv(sh, cmds);
}

int   minishell_builtins_cd(void *sh_, char **cmds)
{
  t_sh        *sh;
  struct stat stat_;
  char        *path;
  char        old_path[257];
  char        new_path[257];

  sh = (t_sh *)sh_;
  if (cmds[1] && ft_strcmp(cmds[1], "-") == 0)
    cmds[1] = minishell_get_env(sh, "OLDPWD");
  path = (cmds[1] && ft_strcmp(cmds[1], "~") != 0) ? cmds[1] :
  ft_strdup(minishell_get_env(sh, "HOME"));
  if (!path)
    path = ".";
  if (lstat(path, &stat_) == -1)
    return (minishell_builtins_cd_error_no_file_directory(path));
  if (!S_ISDIR(stat_.st_mode))
    return (minishell_builtins_cd_error_not_directory(path));
  getcwd(old_path, 256);
  if (chdir(path) != 0)
    return (minishell_builtins_cd_error_permission(path));
  getcwd(new_path, 256);
  minishell_builtins_cd_update_path(sh, ft_strdup(old_path), ft_strdup(new_path));
  return (0);
}
