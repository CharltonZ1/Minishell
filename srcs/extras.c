/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 05:26:21 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:26:22 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int		find(char **envp, char *to_find)
{
	int	i;

	i = 0;
	while (envp[i] &&
			((ft_strncmp(envp[i], to_find, ft_strlen(to_find)) != 0)
			|| &envp[i][ft_strlen(to_find)] > &envp[i][0] +
			ft_strlen(envp[i])
			|| envp[i][ft_strlen(to_find)] != '='))
		i++;
	if (envp[i] == NULL)
		return (-1);
	else
		return (i);
}

char	**new_env(char **envp)
{
	char	**new_env;
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	new_env[i] = NULL;
	i = -1;
	while (envp[++i])
		new_env[i] = ft_strdup(envp[i]);
	return (new_env);
}
