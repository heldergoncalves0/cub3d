/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:36:31 by helferna          #+#    #+#             */
/*   Updated: 2022/10/26 17:39:26 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int ch)
{
	return (ch >= 32 && ch <= 126);
}
