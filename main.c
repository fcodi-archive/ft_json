#include <libft.h>
#include <escape_control_characters.h>
#define SPACE ' '
#define SIGN_MINUS '-'
#define SIGN_PLUS '+'
#define QUOTATION_MARK '"'
#define SOLIDUS '/'
#define REVERSE_SOLIDUS '\\'
#define UNICODE_CHAR 'u'

_Bool	is_whitespace(const char c)
{
	return (c == SPACE || c == LF || c == CR || c == HT);
}

_Bool	is_sign(const char c)
{
	return (c == SIGN_MINUS || c == SIGN_PLUS);
}

_Bool	is_valid_number(const char *number)
{
	size_t	i;

	if (!number || (*number != SIGN_MINUS && *number != '0'))
		return (FALSE);
	i = 1;
	while (ft_isdigit(number[i]))
		i++;
	if (number[i] == '.')
		while (ft_isdigit(number[++i]))
			continue ;
	if (number[i] == 'e' || number[i] == 'E')
	{
		i++;
		if (is_sign(number[i]))
			i++;
		while (ft_isdigit(number[i]))
			i++;
		if (number[i])
			return (FALSE);
	}
	else if (number[i])
		return (FALSE);
	return (TRUE);
}

_Bool 	check_string_escape_code(const char *escape_code, size_t *i)
{

	if (!escape_code || !ft_strchr("\"\\/bfnrtu", escape_code[*i]))
		return (FALSE);
	if (*escape_code == UNICODE_CHAR)
	{
		while (*i <= 5)
			if (ft_is_base_digit(escape_code[*i], 16))
				++*i;
			else
				return (FALSE);
	}
	return (TRUE);
}

_Bool	is_unicode_control_char(const wchar_t c)
{
	return (c >= L'\u2400' && c <= L'\u2426');
}

_Bool	is_escape_control_char(const char c)
{
	if (c == NUL || c == BEL || c == BS || c == HT || c == LF || c == VT
		|| c == FF || c == CR || c == ESC)
		return (TRUE);
	return (FALSE);
}

_Bool	is_control_char(const char c)
{
	return ((c >= 0x00 && c <= 0x1F) || c == 0x7F);
}

_Bool 	is_valid_string(const char *string)
{
	size_t	i;

	if (!string || *string != QUOTATION_MARK)
		return (FALSE);
	i = 1;
	while (string[i] && string[i] != QUOTATION_MARK)
	{
		if (string[i] == '\\' && !check_string_escape_code(string, &i))
			return (FALSE);
		if (is_control_char(string[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

_Bool	is_object_open_bracket(const char c)
{
	return (c == '{');
}

_Bool	is_object_close_bracket(const char c)
{
	return (c == '}');
}

_Bool	is_object_bracket(const char c)
{
	return (c == '{' || c == '}');
}

_Bool	is_array_open_bracket(const char c)
{
	return (c == '[');
}

_Bool 	is_array_close_bracket(const char c)
{
	return (c == ']');
}

_Bool	is_array_bracket(const char c)
{
	return (c == '[' || c == ']');
}

#include <stdio.h>

int 	main(void)
{
	printf("%d", is_valid_number("-0e456"));
}
