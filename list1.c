#include "main.h"
/**
 * add_var_node - adds the variable at the end of the
 * var_list
 * @head: head of the linked list.
 * @len_var: length of the var
 * @val: value of the  var
 * @len_val: length of value
 * Return: the address of the head
 */
var_list *add_var_node(var_list **head, int len_var, char *val, int len_val)
{
	var_list *new, *temp;

	new = malloc(sizeof(var_list));
	if (new == NULL)
		return (NULL);
	new->var_len = len_var;
	new->value = val;
	new->len_value = len_val;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (*head);
}

/**
 * free_var_list - frees the var_list
 * @head: head of the linked list
 */
void free_var_list(var_list **head)
{
	var_list *temp;
	var_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}
