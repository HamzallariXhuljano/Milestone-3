/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exc1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnicolo <gnicolo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:53:50 by xhamzall          #+#    #+#             */
/*   Updated: 2025/06/08 16:52:29 by gnicolo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_hel_here(int fd, const char *delimiter,
		t_env *start, const char *tmp_template)
{
	char	*line;

	signal(SIGINT, sigint_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (g_sigint)
			return (close(fd), unlink(tmp_template), NULL);
		line = readline(">");
		if (!line)
		{
			g_sigint = 1;
			return (close(fd), unlink(tmp_template), NULL);
		}
		line = ft_expand_str(line, start, 0, 0);
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (NULL);
}

char	*here_doc_file(const char *delimiter, t_env *start)
{
	char	*tmp_template;
	int		fd;

	tmp_template = ft_strdup("/tmp/heredoc_XXXXXX");
	fd = my_mkstemp(tmp_template);
	if (fd < 0)
		return (NULL);
	g_sigint = 0;
	ft_hel_here(fd, delimiter, start, tmp_template);
	return (tmp_template);
}

void	cleanup_heredoc_files(t_redirect **redirects)
{
	int				i;
	t_redirect		*redir;

	i = 0;
	while (redirects[i])
	{
		redir = redirects[i];
		while (redir)
		{
			if (redir->heredoc_tmpfile)
			{
				unlink(redir->heredoc_tmpfile);
				free(redir->heredoc_tmpfile);
				redir->heredoc_tmpfile = NULL;
			}
			redir = redir->next;
		}
		i++;
	}
}

int	preprocess_all_heredocs(t_redirect **redirects, t_env *start, int i)
{
	t_redirect		*redir;
	char			*tmp;

	while (redirects[i])
	{
		redir = redirects[i];
		while (redir)
		{
			if (!ft_strcmp(redir->operator, "<<"))
			{
				g_sigint = 0;
				tmp = here_doc_file(redir->filename, start);
				if (!tmp || g_sigint)
				{
					if (tmp)
						free(tmp);
					return (-1);
				}
				redir->heredoc_tmpfile = tmp;
			}
			redir = redir->next;
		}
		i++;
	}
	return (0);
}

void	ft_signal_handlers2(int sig)
{
	if (sig == SIGINT)
	{
		g_sigint = 130;
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_sigint = 131;
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
	}
}
