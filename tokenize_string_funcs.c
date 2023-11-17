#include <stdlib.h>

char *_get_next_word(char *str, char *delims);
char **strtow(char *str, char *delims);
int _get_word_count(char *str, char *delims);
int _get_word_length(char *str, char *delims);
int _is_delim(char ch, char *delims);

/**
 * _get_next_word - Gets the next word in a string
 *
 * @str: string to get next word from
 * @delims: delimitors to use to delimit words
 *
 * Return: pointer to first char of next word
 */

char *_get_next_word(char *str, char *delims)
{
	int idx = 0;
	int pending = 0;

	while (*(str + idx))
	{
		if (_is_delim(str[idx], delims))
		{
			pending = 1;
		}
		else if (pending)
		{
			break;
		}
		idx++;
	}
	return (str + idx);
}

/**
 * strtow - Takes a string and seperates its words
 *
 * @str: string to seperate into words
 * @delims: delimitors to use to delimit words
 *
 * Return: 2D array of pointers to each word
 */

char **strtow(char *str, char *delims)
{
	char **words = NULL;
	int word_count, word_length, n, idx = 0;

	if (str == NULL || !*str)
	{
		return (NULL);
	}
	word_count = _get_word_count(str, delims);

	if (word_count == 0)
	{
		return (NULL);
	}
	words = malloc((word_count + 1) * sizeof(char *));
	if (words == NULL)
	{
		return (NULL);
	}
	while (idx < word_count)
	{
		word_length = _get_word_length(str, delims);
		if (_is_delim(*str, delims))
		{
			str = _get_next_word(str, delims);
		}
		words[idx] = malloc((word_length + 1) * sizeof(char));
		if (words[idx] == NULL)
		{
			while (idx >= 0)
			{
				idx--;
				free(words[idx]);
			}
			free(words);
			return (NULL);
		}
		n = 0;
		while (n < word_length)
		{
			words[idx][n] = *(str + n);
			n++;
		}
		words[idx][n] = '\0';
		str = _get_next_word(str, delims);
		idx++;
	}
	words[idx] = NULL;
	return (words);
}

/**
 * _get_word_count - Gets the word count of a string
 *
 * @str: string to get word count from
 * @delims: delimitors to use to delimit words
 *
 * Return: the word count of the string
 */

int _get_word_count(char *str, char *delims)
{
	int word_count = 0, pending = 1, idx = 0;

	while (*(str + idx))
	{
		if (_is_delim(str[idx], delims))
		{
			pending = 1;
		}
		else if (pending)
		{
			pending = 0;
			word_count++;
		}
		idx++;
	}
	return (word_count);
}

/**
 * _get_word_length - Gets the word length of cur word in str
 *
 * @str: string to get word length from current word
 * @delims: delimitors to use to delimit words
 *
 * Return: word length of current word
 */

int _get_word_length(char *str, char *delims)
{
	int word_length = 0, pending = 1, idx = 0;

	while (*(str + idx))
	{
		if (_is_delim(str[idx], delims))
		{
			pending = 1;
		}
		else if (pending)
		{
			word_length++;
		}
		if (word_length > 0 && _is_delim(str[idx], delims))
		{
			break;
		}
		idx++;
	}
	return (word_length);
}

/**
 * _is_delim - Checks if stream has delimitor char
 *
 * @ch: character in stream
 *
 * @delims: Pointer to null terminated array of delimitors
 *
 * Return: 1 (success) 0 (failure)
 */

int _is_delim(char ch, char *delims)
{
	int idx = 0;

	while (delims[idx])
	{
		if (delims[idx] == ch)
		{
			return (1);
		}
		idx++;
	}
	return (0);
}
