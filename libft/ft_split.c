/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:57:47 by helferna          #+#    #+#             */
/*   Updated: 2023/03/13 16:37:58 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_word(const char *s, char c)
{
	int	trigger;
	int	i;

	i = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (i);
}

static char	*word(const char *s, int start, int finish)
{
	size_t	i;
	char	*new_str;

	i = 0;
	new_str = malloc(sizeof(char) * (finish - start + 1));
	while (start < finish)
		new_str[i++] = s[start++];
	new_str[i] = '\0';
	return (new_str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**split;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	split = malloc (sizeof(char *) * (count_word(s, c) + 1));
	if (!split || !s)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}
