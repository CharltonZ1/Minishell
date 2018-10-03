/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chadams <chadams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 18:23:40 by chadams           #+#    #+#             */
/*   Updated: 2018/09/17 05:32:06 by chadams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/minishell.h"

static char		*malloc_line(char *line, int loop)
{
	char	*new_line;

	if (!(new_line = malloc(sizeof(char) * (loop + 1 + 255 + 1))))
		exit(0);
	if (line != NULL)
		ft_strcpy(new_line, line);
	new_line[loop + 256] = '\0';
	free(line);
	return (new_line);
}

char			*readline(int fd)
{
	char	*line;
	int		loop;

	loop = 0;
	line = malloc_line(NULL, 0);
	while (loop == 0 || (line[loop - 1] != '\n' && line[loop - 1] != -1))
	{
		if (read(fd, &line[loop++], 1) == 0)
		{
			ft_putchar('\n');
			free(line);
			return (NULL);
		}
		if (loop % 255 == 0)
			line = malloc_line(line, loop);
	}
	line[loop] = '\0';
	return (line);
}
