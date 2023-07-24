#include "main.h"



/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */

void pr_buff(char buff[], int *b_ind);

int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, b_ind = 0;
	va_list list;
	char buff[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buff[b_ind++] = format[i];
			if (b_ind == BUFF_SIZE)
				pr_buff(buff, &b_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			pr_buff(buff, &b_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	pr_buff(buff, &b_ind);

	va_end(list);

	return (printed_chars);
}
void pr_buff(char buff[], int *b_ind)
{
	if (*b_ind > 0)
		write(1, &buff[0], *b_ind);

	*b_ind = 0;
}
