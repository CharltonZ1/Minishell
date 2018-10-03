/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 05:26:24 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:30:55 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	fork_child(char **path, char *command[], char **envp)
{
	pid_t	pid;
	int		i;

	pid = fork();
	if (pid == 0)
	{
		i = -1;
		if (path != NULL)
			while (path[++i])
				execve(path[i], command, envp);
		if (execve(command[0], command, envp) == -1)
			ft_putendl_fd("Command Failed", 2);
		exit(0);
	}
	else
	{
		wait(NULL);
		if (path != NULL)
		{
			i = -1;
			while (path[++i])
				free(path[i]);
			free(path);
		}
	}
}

void		parse_command(char *command[], char **envp)
{
	int		i;
	int		var;
	char	*mem;
	char	**path;

	i = 0;
	if (((var = find(envp, "PATH")) == -1) ||
	(ft_strchr(command[0], '/') != NULL))
	{
		fork_child(NULL, command, envp);
		return ;
	}
	if ((path = ft_strsplit(&envp[var][4 + 1], ':')) == NULL)
		exit(0);
	i = -1;
	while (path[++i])
	{
		mem = path[i];
		if (!(path[i] = ft_strcjoin(path[i], command[0], '/')))
			exit(0);
		free(mem);
	}
	fork_child(path, command, envp);
}
