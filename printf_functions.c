#include "main.h"

/**
 * printf_char - Prints a char to standard output
 * @args: arguments
 * @buffer: Buffer
 * @flags: flags
 * @width: Width parameter
 * @precision: Precision parameter
 * @size: Size parameter
 * Return: Int,Number of chars printed to standard output
 */
int printf_char(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(args, int);

	return (printf_write_char(c, buffer, flags, width, precision, size));
}

/**
 * printf_string - Prints a string to standard output
 * @args: arguments
 * @buffer: Buffer
 * @flags:  Flags
 * @width: Width parameter
 * @precision: Precision parameter
 * @size: Size parameter
 * Return: Int,Number of chars printed to standard output
 */
int printf_string(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(args, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
	return (write(1, str, length));
}
/**
 * printf_percent - Prints a literal percent sign to standard output
 * @args: arguments
 * @buffer: Buffer
 * @flags: Flags
 * @width: Width parameter
 * @precision: Precision parameter
 * @size: Size parameter
 * Return: Int,Number of chars printed to standard output.
 */
int printf_percent(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(args);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * printf_int - Prints an int to the standard output.
 * @args: arguments
 * @buffer: Buffer
 * @flags: Flags
 * @width: Width parameter
 * @precision: Precision parameter
 * @size: Size parameter
 * Return: Int,Number of chars printed to standard output
 */
int printf_int(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(args, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_num(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * printf_binary - Prints an unsigned number to standard output
 * @args: arguments
 * @buffer: Buffer
 * @flags: Flags parameter
 * @width: Width parameter
 * @precision: Precision parameter
 * @size: Size parameter
 * Return: Int, number of chars printed to standard output
 */
int printf_binary(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(args, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

