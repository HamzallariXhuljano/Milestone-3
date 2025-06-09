/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xhamzall <xhamzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:05:31 by gnicolo           #+#    #+#             */
/*   Updated: 2025/06/06 19:59:38 by xhamzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env_and_exit(t_env *start, char *input)
{
	int	i;

	i = start->exit_code;
	ft_free_env2(start->env_copy);
	printf("Exiting shell...\n");
	free(start);
	free(input);
	exit(i);
}

void	ft_free_input_exit(t_env *start, char *input)
{
	if (input)
		free(input);
	ft_free_env2(start->env_copy);
	printf("Exiting shell...\n");
	free(start);
	close(0);
	close(1);
	close(2);
	exit(EXIT_SUCCESS);
}

void	ft_init_start(t_env *start, char **envp)
{
	start->exit_code = 0;
	start->env_copy = ft_copy_env(envp);
	start->input = NULL;
	init_shell();
}

void	ft_exec_something(t_env *start)
{
	ft_second_parse(start);
	g_sigint = 0;
	ft_set_argv(start->word);
	ft_exec_all(start);
	ft_free_env(start);
}

// MAIN PRIMA DI CD
int	main(int argc, char **argv, char **envp)
{
	t_env	*start;

	start = ft_calloc(sizeof(t_env), 1);
	if (argc != 1 || argv[1] != NULL)
		return (write(2, "Error: No arguments expected\n", 29), 1);
	ft_init_start(start, envp);
	while (1)
	{
		check_signal(start->exit_code, start);
		start->input = readline("Minishell> ");
		ft_check_exit_code(start);
		add_history(start->input);
		if (start->input == NULL)
			ft_free_env_and_exit(start, start->input);
		if (ft_strcmp(start->input, "exit") == 0)
			ft_free_env_and_exit(start, start->input);
		else
		{
			if (ft_first_parse(start, start->input))
				continue ;
			ft_exec_something(start);
		}
	}
	clear_history();
	return (0);
}
