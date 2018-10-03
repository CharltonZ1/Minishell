/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 18:13:56 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:26:13 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	cwd2(char *cd)
{
	int	i;

	i = -1;
	while (cd[++i])
		while ((ft_strncmp(&cd[i], "/.", 2)) == 0)
			ft_strcpy(&cd[i], &cd[i + 2]);
	i--;
	while (cd[i] == '/' && i != 0)
		cd[i--] = '\0';
}

static void	cwd(char *cd)
{
	int i;
	int mem;

	i = -1;
	while (cd[++i])
		while ((ft_strncmp(&cd[i], "//", 2)) == 0)
			ft_strcpy(&cd[i], &cd[i + 1]);
	i = -1;
	while (cd[++i])
		while (cd[i] && (ft_strncmp(&cd[i], "/..", 3)) == 0)
		{
			if (i == 0)
				ft_strcpy(&cd[i], "/");
			else
			{
				mem = i + 3;
				while (--i > 0 && cd[i] != '/')
					cd[i] = '\0';
				if (i != 0)
					ft_strcpy(&cd[i], &cd[mem]);
			}
		}
	cwd2(cd);
}

static void	cd2(char *cd, char *command[], char **envp)
{
	int	var;
	DIR	*dir;

	if ((dir = opendir(cd)))
	{
		chdir(cd);
		cwd(cd);
		if ((var = find(envp, "PWD")) != -1)
			set_env("OLDPWD", &envp[var][4], envp);
		else
			set_env("OLDPWD", cd, envp);
		set_env("PWD", cd, envp);
		free(cd);
		closedir(dir);
	}
	else
	{
		ft_putstr("cd: No such file or directory: ");
		ft_putendl_fd(command[0], 2);
		free(cd);
	}
}

void		cd(char *command[], char **envp)
{
	char	*cd;
	int		var;

	if (command[0] == NULL && ((var = find(envp, "HOME")) == -1))
		return ;
	else if (command[0] == NULL && ((var = find(envp, "HOME")) > -1))
		cd = ft_strdup(&envp[var][5]);
	else if (command[0] && command[0][0] == '/')
		cd = ft_strdup(command[0]);
	else if (command[0] && command[0][0] == '~')
	{
		var = find(envp, "HOME");
		cd = ft_strcjoin(&envp[var][4 + 1], &command[0][1], '/');
	}
	else if (command[0] && ft_strcmp(command[0], "-") == 0)
	{
		var = find(envp, "OLDPWD");
		cd = ft_strdup(&envp[var][6 + 1]);
	}
	else
	{
		var = find(envp, "PWD");
		cd = ft_strcjoin(&envp[var][3 + 1], command[0], '/');
	}
	cd2(cd, command, envp);
}
