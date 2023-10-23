/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moelalj <moelalj@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:40:07 by moelalj           #+#    #+#             */
/*   Updated: 2022/11/07 15:48:24 by moelalj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include <unistd.h>

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}
int	ft_strlen(const char *str)
{
	int	counter;

	counter = 0;
	while (str[counter])
	{
		counter++;
	}
	return (counter);
}
int	ft_hexa_lower(unsigned int nb)
{
	char					*str;
	int						count;

	count = 0;
	str = "0123456789abcdef";
	if (nb >= 0 && nb <= 15)
		count += ft_putchar(str[nb]);
	else
	{
		count += ft_hexa_lower(nb / 16);
		count += ft_hexa_lower(nb % 16);
	}
	return (count);
}

int	ft_putnbr(int nb)
{
	int		count;
	long	n;

	n = nb;
	count = 0;
	if (n < 0)
	{
		count += ft_putchar('-');
		n = n * -1;
	}
	if (n >= 0 && n <= 9)
		count += ft_putchar(n + '0');
	else
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	return (count);
}

int	ft_putstr(char *str)
{
	int	i;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = ft_strlen(str);
	write(1, str, i);
	return (i);
}


int	formats(va_list p_args, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (c == 's')
		count += ft_putstr(va_arg(p_args, char *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(p_args, int));
	else if (c == 'x')
		count += ft_hexa_lower(va_arg(p_args, unsigned long));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	p_args;
	int		i;
	int		count;

	va_start(p_args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += formats(p_args, format[i]);
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(p_args);
	return (count);
}

int main()
{
	int	a;

	a = 42;
	ft_printf("%d", a);
	return (0);
}
