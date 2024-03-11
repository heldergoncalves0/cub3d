/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:37:35 by helferna          #+#    #+#             */
/*   Updated: 2023/10/19 00:42:24 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isdigit(int str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

// int main(void)
// {
// 	char *a;
// 	int b;

// 	a = "43434d53";
// 	b = ft_isdigit(a);
// 	printf("%d", b);
// }
