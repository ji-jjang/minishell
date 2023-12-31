#include "minishell_bonus.h"

static char	*_getkey(char *str)
{
	char	*value;
	char	*key;

	value = get_value_export(str);
	if (value == NULL)
		return (ft_strdup(str));
	key = get_key(str, value);
	return (key);
}

char	*ft_getenv(t_list *env_list, char *env)
{
	t_node	*cur_node;
	char	*tmp;
	char	*key;

	cur_node = env_list->head;
	while (cur_node)
	{
		key = _getkey((char *)cur_node->content);
		if (ft_strlen(env) != 0 && ft_strcmp(key, env) == 0)
		{
			free(key);
			tmp = ft_strchr((char *)cur_node->content, '=');
			if (tmp == NULL)
				return ("");
			return (tmp + 1);
		}
		if (key)
			free(key);
		cur_node = cur_node->next;
	}
	return (NULL);
}

void	ft_setenv(t_list *env_list, char *key, char *command)
{
	t_node	*cur_node;
	char	*env_key;

	cur_node = env_list->head;
	while (cur_node)
	{
		env_key = _getkey((char *)cur_node->content);
		if (ft_strcmp(env_key, key) == 0)
		{
			free(env_key);
			free(cur_node->content);
			cur_node->content = ft_strdup(command);
			return ;
		}
		if (env_key)
			free(env_key);
		cur_node = cur_node->next;
	}
	return ;
}
