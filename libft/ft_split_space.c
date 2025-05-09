/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 07:40:56 by dfasius           #+#    #+#             */
/*   Updated: 2024/12/16 07:40:57 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fill_size(char **arg, int sq, int dq)
{
	int		len;

	len = 0;
	while ((**arg) && (!ft_is_whitespace(**arg) || sq || dq))
	{
		if (!dq && (**arg) == '\'')
			sq = !sq;
		else if (!sq && (**arg) == '"')
			dq = !dq;
		else
			len++;
		(*arg)++;
	}
	return (len);
}

int	split_space_size(char *arg)
{
	int		len;

	len = 0;
	while (*arg)
	{
		while (*arg && ft_is_whitespace(*arg))
			arg++;
		if (*arg && !ft_is_whitespace(*arg))
		{
			fill_size(&arg, 0, 0);
			len++;
		}
	}
	return (len);
}

char	*fill_ft_split_space(char **arg, int sq, int dq)
{
	char	*arr;
	char	*store;
	int		j;

	j = 0;
	store = *arg;
	arr = malloc(sizeof(char) * (fill_size(&store, 0, 0) + 1));
	if (!arr)
		return (NULL);
	while ((**arg)
		&& (!ft_is_whitespace(**arg) || sq || dq))
	{
		if (!dq && (**arg) == '\'')
			sq = !sq;
		else if (!sq && (**arg) == '"')
			dq = !dq;
		else
			arr[j++] = (**arg);
		(*arg)++;
	}
	return (arr[j] = '\0', arr);
}

char	**ft_split_space(char *arg)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof(char *) * (split_space_size(arg) + 1));
	if (!cmds)
		return (NULL);
	while (*arg)
	{
		while (*arg && ft_is_whitespace(*arg))
			arg++;
		if (*arg && !ft_is_whitespace(*arg))
		{
			cmds[i++] = fill_ft_split_space(&arg, 0, 0);
			if (!cmds[i - 1])
				return (ft_free_2d(&cmds), NULL);
		}
	}
	return (cmds[i] = NULL, cmds);
}
