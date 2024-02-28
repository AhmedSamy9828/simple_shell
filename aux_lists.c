#include "shell.h"

/**
 * add_sep_node_end - Add a separator node to the end of the separator list
 * 
 * This function creates a new separator node with the given separator character
 * and adds it to the end of the separator list.
 * 
 * @head: Pointer to the head of the separator list
 * @sep: Separator character to be added
 * 
 * Return: Pointer to the head of the updated separator list
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
    sep_list *new_node, *temp;

    /* Allocate memory for the new node */
    new_node = malloc(sizeof(sep_list));
    if (new_node == NULL)
        return (NULL);

    /* Initialize the new node */
    new_node->separator = sep;
    new_node->next = NULL;

    /* If the list is empty, set the new node as the head */
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        /* Traverse the list to find the last node */
        temp = *head;
        while (temp->next != NULL)
            temp = temp->next;

        /* Add the new node to the end of the list */
        temp->next = new_node;
    }

    /* Return the updated head of the list */
    return (*head);
}

/**
 * free_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
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
 * free_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
