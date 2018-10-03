/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 05:26:08 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:26:09 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static void	echo(char *command[])
{
	int	k;
	int	nl;

	k = -1;
	nl = 0;
	if (command[0] != NULL)
	{
		if ((ft_strcmp(command[++k], "-n") == 0))
			nl = 1;
		else
			k--;
		while (command[++k] != NULL)
			ft_putendl(command[k]);
	}
	if (nl != 1)
		ft_putchar('\n');
}

static void	ft_exit(char *command[], char **envp)
{
	if (command[0] == NULL)
	{
		handle_shell(envp, -1);
		exit(0);
	}
	else if (command[1] == NULL)
	{
		handle_shell(envp, -1);
		exit(ft_atoi(command[0]));
	}
	else
		ft_putendl("Minishell: exit: too many arguments");
}

char		**parse_builtins(char *command[], char **envp)
{
	if (!command[0])
		return (envp);
	else if (!(ft_strcmp(command[0], "exit")))
		ft_exit(command + 1, envp);
	else if (!(ft_strcmp(command[0], "cd")))
		cd(command + 1, envp);
	else if (!(ft_strcmp(command[0], "setenv")) && command[1] && command[2])
		envp = set_env(command[1], command[2], envp);
	else if (!(ft_strcmp(command[0], "unsetenv")))
		unset_env(envp, command + 1);
	else if ((!(ft_strcmp(command[0], "env")) && !(command[1])) ||
			!(ft_strcmp(command[0], "printenv")))
		printenv(command[1], envp);
	else if (!(ft_strcmp(command[0], "echo")))
		echo(command + 1);
	else
		parse_command(command, envp);
	return (envp);
}
