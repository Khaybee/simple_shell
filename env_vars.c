#include "main.h"

/**
 * search_env - checks if typed variable is of an env variable
 *
 * @list: head of the linked list
 * @str: input string
 * @data: data structure
 * Return: no return
 */
void search_env(var_list **list, char *str, runtime_data *data)
{
	char **_envir;
	int i, j, c, val;

	_envir = data->_env;
	for (i = 0; _envir[i]; i++)
	{
		for (c = 1, j = 0; _envir[i][j]; j++)
		{
			if (_envir[i][j] == '=')
			{
				val = _strlen(_envir[i] + j + 1);
				add_var_node(list, c, _envir[i] + j + 1, val);
				return;
			}

			if (str[c] == _envir[i][j])
				c++;
			else
				break;
		}
	}
	for (c = 0; str[c]; c++)
	{
		if (str[c] == ' ' || str[c] == '\t' || str[c] == ';' || str[c] == '\n')
			break;
	}

	add_var_node(list, c, NULL, 0);
}


/**
 * search_vars - check if typed variable is $$ or $?
 *
 * @head: head of linked list
 * @str: input string
 * @status: last status of Shell
 * @data: data structure
 * Return: return x
 */

int search_vars(var_list **head, char *str, char *status, runtime_data *data)
{
	int x, list, bol;

	list = _strlen(status);
	bol = _strlen(data->pid);

	for (x = 0; str[x]; x++)
	{
		if (str[x] == '$')
		{
			if (str[x + 1] == '?')
			{
				add_var_node(head, 2, status, list), x++;
			}
			else if (str[x + 1] == '$')
				add_var_node(head, 2, data->pid, bol), x++;
			else if (str[x + 1] == '\n')
				add_var_node(head, 0, NULL, 0);
			else if (str[x + 1] == '\0')
				add_var_node(head, 0, NULL, 0);
			else if (str[x + 1] == ' ')
				add_var_node(head, 0, NULL, 0);
			else if (str[x + 1] == '\t')
				add_var_node(head, 0, NULL, 0);
			else if (str[x + 1] == ';')
				add_var_node(head, 0, NULL, 0);
			else
				search_env(head, str + x, data);
		}
	}

	return (x);
}

/**
 * replaced_string - replaces string into the variables
 *
 * @head: head of linked list
 * @str: input string
 * @new_str: new input strings (replaced)
 * @new_len: new length
 * Return: replaced string
 */
char *replaced_string(var_list **head, char *str, char *new_str, int new_len)
{
	var_list *index;
	int a, c, b;

	index = *head;
	for (c = a = 0; a < new_len; a++)
	{
		if (str[c] == '$')
		{
			if (!(index->var_len) && !(index->len_value))
			{
				new_str[a] = str[c];
				c++;
			}
			else if (index->var_len && !(index->len_value))
			{
				for (b = 0; b < index->var_len; b++)
					c++;
				a--;
			}
			else
			{
				for (b = 0; b < index->len_value; b++)
				{
					new_str[a] = index->value[b];
					a++;
				}
				c += (index->var_len);
				a--;
			}
			index = index->next;
		}
		else
		{
			new_str[a] = str[c];
			c++;
		}
	}

	return (new_str);
}


/**
 * replace_var - calls functions to replace string into the vars
 *
 * @str: input the string
 * @data: data structure
 * Return: replaced string.
 */
char *replace_var(char *str, runtime_data *data)
{
	var_list *head, *index;
	char *status, *new_str;
	int old_len, new_len;

	status = int_to_string(data->status);
	head = NULL;

	old_len = search_vars(&head, str, status, data);

	if (head == NULL)
	{
		free(status);
		return (str);
	}

	index = head;
	new_len = 0;

	while (index != NULL)
	{
		new_len += (index->len_value - index->var_len);
		index = index->next;
	}

	new_len += old_len;

	new_str = malloc(sizeof(char) * (new_len + 1));
	new_str[new_len] = '\0';

	new_str = replaced_string(&head, str, new_str, new_len);

	free(str);
	free(status);
	free_var_list(&head);

	return (new_str);
}
