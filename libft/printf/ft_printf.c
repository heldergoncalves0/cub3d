/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helferna <helferna@students.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:18:54 by helferna          #+#    #+#             */
/*   Updated: 2023/01/14 03:09:40 by helferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr(char *str, char c, int toggle)
{
	int	length;

	length = 0;
	if (toggle)
	{
		write(1, &c, 1);
		return (1);
	}
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[length])
		length++;
	write (1, str, length);
	return (length);
}

static int	ft_putnbr_base(size_t nbr, int b, char *base, int toggle)
{
	int	length;

	length = 0;
	if (toggle)
	{
		if (nbr == 0)
		{
			length += write(1, "(nil)", 5);
			return (length);
		}
		length += ft_putstr("0x", 0, 0);
	}
	if (nbr / b == 0)
		length += ft_putstr (NULL, base[nbr], 1);
	else
	{
		length += ft_putnbr_base (nbr / b, b, base, 0);
		length += ft_putnbr_base (nbr % b, b, base, 0);
	}
	return (length);
}

int	check_signal(int nbr, long long signal)
{
	signal = 1;
	if (nbr < 0)
	{
		signal = -1;
		return (signal);
	}
	return (signal);
}

static	void	ft_format(char option, va_list args, int *length)
{
	long long	signal;
	int			nbr;

	signal = 0;
	if (option == 'c')
		*length += ft_putstr(NULL, va_arg(args, int), 1);
	else if (option == 's')
		*length += ft_putstr(va_arg(args, char *), 0, 0);
	else if (option == '%')
		*length += ft_putstr(NULL, '%', 1);
	else if (option == 'd' || option == 'i')
	{
		nbr = va_arg(args, int);
		*length += write(1, "-", (nbr < 0));
		signal = check_signal(nbr, signal);
		*length += ft_putnbr_base((nbr * signal), 10, DECIMAL, 0);
	}
	else if (option == 'p')
		*length += ft_putnbr_base(va_arg(args, long), 16, HEX_MIN, 1);
	else if (option == 'u')
		*length += ft_putnbr_base(va_arg(args, unsigned int), 10, DECIMAL, 0);
	else if (option == 'x')
		*length += ft_putnbr_base(va_arg(args, unsigned int), 16, HEX_MIN, 0);
	else if (option == 'X')
		*length += ft_putnbr_base(va_arg(args, unsigned int), 16, HEX_MAX, 0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start (args, str);
	while (str[i])
	{
		if (str[i] == '%')
			ft_format(str[++i], args, &print_length);
		else
		{
			ft_putstr(NULL, str[i], 1);
			print_length++;
		}
		i++;
	}
	return (print_length);
	va_end (args);
}

/*int	main(void)
{
	char	i = 's';
	char	i2[20] = "Hello World";
	int		i3 = 34;
	int		i4 = -23;
	int		*i5 = &i3;

	printf("Printf char: %c\n", i);
	ft_printf("Ft_Printf char: %c\n\n", i);

	printf("Printf string: %s\n", i2);
	ft_printf("Ft_Printf string: %s\n\n", i2);

	printf("Printf percent: %%\n");
	ft_printf("Ft_Printf percent: %%\n\n");

	printf("Printf integer: %d || %i\n", i3, i4);
	ft_printf("Ft_Printf integer: %d || %i\n\n", i3, i4);

	printf("Printf pointer: %p\n", &i5);
	ft_printf("Ft_Printf pointer: %p\n\n", &i5);

	printf("Printf unsigned number: %u\n", i3);
	ft_printf("Ft_Printf unsigned number: %u\n\n", i3);

	printf("Printf number in hexadecimal: %x\n", i);
	ft_printf("Ft_Printf number in hexadecimal: %x\n\n", i);

	printf("Printf number in hexadecimal(UP): %X\n", i);
	ft_printf("Ft_Printf number in hexadecimal(UP): %X\n\n", i);
	
	return (0);
}*/
