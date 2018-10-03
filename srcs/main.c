/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 05:26:28 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:32:35 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void		parse_line(char *line, char *command[])
{
	int	i;

	i = -1;
	while (*line && *line != '\n' && *line != '#')
	{
		while (*line == ' ' || *line == '\t' || *line == '\'' || *line == '"')
			*(line++) = '\0';
		if (*line && *line != '\n' && *line != '#')
			command[++i] = line;
		while (*line && *line != '\n' && *line != ' ' && *line != '\t' &&
				*line != '\'' && *line != '"')
			line++;
	}
	command[++i] = NULL;
	*line = '\0';
}

int			main(int argc, char **argv)
{
	char		*line;
	char		*command[1024];
	char		**new_enp;
	extern char **environ;

	new_enp = new_env(environ);
	handle_shell(new_enp, 1);
	if (argc == 1 && argv[1] == NULL)
		while (1)
		{
			signal(SIGINT, siginthandler);
			ft_putstr("%% ");
			if ((line = readline(1)) != NULL)
			{
				signal(SIGINT, siginthandler2);
				parse_line(line, command);
				subs_env_var(command, new_enp);
				new_enp = parse_builtins(command, new_enp);
				free(line);
			}
		}
	return (0);
}
