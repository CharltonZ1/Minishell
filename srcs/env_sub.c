/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 18:26:19 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:32:24 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/minishell.h"

void		subs_env_var(char *command[], char **envp)
{
	int		i;
	int		del;
	int		var;

	i = -1;
	while (command[++i])
	{
		if (command[i][0] == '$')
		{
			if ((var = find(envp, &command[i][1])) != -1)
				command[i] = &envp[var][ft_strlen(command[i])];
			else
			{
				del = i;
				while (command[del + 1] != NULL)
				{
					command[del] = command[del + 1];
					del++;
				}
				command[del] = NULL;
			}
		}
	}
}
