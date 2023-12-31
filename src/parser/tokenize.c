#include "minishell.h"
#include "linked_list.h"

static bool	is_double_operator(char *prev_str, char *line)
{
	return (ft_strlen(prev_str) == 1
		&& is_operator(*prev_str) && is_operator(*line) && !is_quote(*line));
}

static bool	is_single_operator_no_space(char *prev_str, char *line)
{
	return (ft_strlen(prev_str) == 1
		&& is_operator(*prev_str) && !is_operator(*line) && !is_space(*line));
}

static void	substr_quote(char **prev_str, char **line)
{
	if (**line == '"')
		*prev_str = ft_strjoin(*prev_str, read_quote_content(line, '"'));
	if (**line == '\'')
		*prev_str = ft_strjoin(*prev_str,
				read_quote_content(line, '\''));
}

static void	make_token(char *line, char **prev_str, t_list *cmd_list)
{
	while (*line)
	{
		if (is_double_operator(*prev_str, line))
			put_token_double_operator(prev_str, &line, cmd_list);
		else if (is_single_operator_no_space(*prev_str, line))
			put_token_single_operator_no_space(prev_str, &line, cmd_list);
		else if (is_quote(*line))
			substr_quote(prev_str, &line);
		else if (is_bracket(*line))
			put_token_bracket_content(prev_str, &line, cmd_list);
		else if (is_operator(*line))
			put_token_single_operator(prev_str, &line, cmd_list);
		else if (is_space(*line))
		{
			put_token_before_space(prev_str, &line, cmd_list);
			if (!*line)
				break ;
		}
		else
			*prev_str = ft_charjoin(*prev_str, *line);
		++line;
	}
}

t_list	*tokenize(char *line)
{
	char	*prev_str;
	t_list	*cmd_list;

	cmd_list = init_list();
	prev_str = ft_strdup("");
	make_token(line, &prev_str, cmd_list);
	if (prev_str)
		put_token_in_list(prev_str, cmd_list);
	return (cmd_list);
}
