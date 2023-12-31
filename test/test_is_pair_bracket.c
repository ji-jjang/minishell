#include "minishell.h"

void	test_is_pair_bracket(void)
{
	const char	*str = "(";
	const char	*str2 = ")(";
	const char	*str3 = "('()')";
	const char	*str4 = "(\")\"";
	const char	*str5 = "";

	ft_assert(is_pair_bracket(str), false, "is_pair_bracket line: 17 fail");
	ft_assert(is_pair_bracket(str2), false, "is_pair_bracket line: 18 fail");
	ft_assert(is_pair_bracket(str3), true, "is_pair_bracket line: 19 fail");
	ft_assert(is_pair_bracket(str4), false, "is_pair_bracket line: 20 fail");
	ft_assert(is_pair_bracket(str5), true, "is_pair_bracket line: 21 fail");
}
