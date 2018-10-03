/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 05:26:05 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:26:06 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	siginthandler2(int sig_num)
{
	if (sig_num == 2)
	{
		ft_putchar('\n');
		signal(SIGINT, siginthandler2);
	}
}

void	siginthandler(int sig_num)
{
	if (sig_num == 2)
	{
		ft_putchar('\n');
		signal(SIGINT, siginthandler);
		ft_putstr("%% ");
	}
}

void	handle_shell(char **envp, int nbr)
{
	int		loop;
	char	*new_shlvl;

	loop = find(envp, "SHELLRL");
	if (loop > -1)
	{
		new_shlvl = ft_itoa(ft_atoi(ft_strchr(envp[loop], '=') + 1) + nbr);
		if (new_shlvl == NULL)
			exit(0);
		set_env("SHELLRL", new_shlvl, envp);
		free(new_shlvl);
	}
}
