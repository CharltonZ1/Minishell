/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 05:26:18 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:26:19 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void		unset_env(char **envp, char *command[])
{
	int		loop;
	int		envp_read;
	int		del;

	loop = -1;
	while (command[++loop])
	{
		envp_read = -1;
		while (envp[++envp_read])
		{
			if (!(ft_strncmp(envp[envp_read], command[loop],
						ft_strlen(command[loop]))))
			{
				del = envp_read;
				free(envp[del]);
				while (envp[del + 1] != NULL)
				{
					envp[del] = envp[del + 1];
					del++;
				}
				envp[del] = NULL;
			}
		}
	}
}

static char	**realloc_env(char **envp, int new_size)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (new_size + 2));
	new[new_size + 1] = NULL;
	i = -1;
	while (envp[++i])
	{
		new[i] = ft_strdup(envp[i]);
		free(envp[i]);
	}
	free(envp);
	return (new);
}

char		**set_env(char *command1, char *command2, char **envp)
{
	int		loop;
	int		var;
	char	**new_envp;

	if (command1 == NULL || command2 == NULL)
		return (envp);
	var = find(envp, command1);
	if (var != -1)
	{
		free(envp[var]);
		envp[var] = ft_strcjoin(command1, command2, '=');
	}
	else
	{
		loop = 0;
		while (envp[loop] != NULL)
			loop++;
		new_envp = realloc_env(envp, loop);
		new_envp[loop] = ft_strcjoin(command1, command2, '=');
		return (new_envp);
	}
	return (envp);
}

void		printenv(char *command, char **envp)
{
	int		var;
	int		k;

	k = -1;
	if (command == NULL)
		while (envp[++k] != NULL)
		{
			ft_putstr(envp[k]);
			ft_putchar('\n');
		}
	else
	{
		var = find(envp, command);
		if (var != -1)
			ft_putendl(&envp[var][ft_strlen(command) + 1]);
	}
}
