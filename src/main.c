#include "minishell.h"

void	do_minishell(t_list *env_list)
{
	t_list	*tokenized_list;
	t_tree	*cmd_tree;
	t_list	*cmd_list;
	char	*line;

	while (1)
	{
		line = get_line();
		if (is_line_null(line))
			break ;
		if (!(has_line_content(line) && add_history_line(line)) || \
		!is_correct_pair(line))
		{
			free(line);
			continue ;
		}
		if (!can_parse(&tokenized_list, &cmd_tree, &cmd_list, line))
			continue ;
		make_heredoc(cmd_list);
		if (is_catched_interrupt(tokenized_list, cmd_tree, cmd_list))
			continue ;
		execute(cmd_list, env_list);
		free_rest(tokenized_list, cmd_tree, cmd_list);
	}
	free_list_node_content(env_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*env_list;

	env_list = init_environment(envp);
	if (argc >= 2)
		return (do_subshell(argc, argv, env_list));
	do_minishell(env_list);
	return (0);
}
