#include "shell.h"

/**
 * _memcpy - Copy information between void pointers.
 *
 * This function copies data from the source pointer to the destination pointer
 * for the specified size.
 *
 * @newptr: Destination pointer.
 * @ptr: Source pointer.
 * @size: Size of the new pointer.
 *
 * Return: This function does not return a value.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
    char *char_ptr = (char *)ptr;
    char *char_newptr = (char *)newptr;
    unsigned int i;

    /* Copy data from source pointer to destination pointer */
    for (i = 0; i < size; i++)
        char_newptr[i] = char_ptr[i];
}



/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}


/**
 * _reallocdp - Reallocate memory block of a double pointer.
 *
 * This function reallocates memory for a double pointer to accommodate the new size.
 *
 * @ptr: Double pointer to the memory previously allocated.
 * @old_size: Size, in bytes, of the allocated space of ptr.
 * @new_size: New size, in bytes, of the new memory block.
 *
 * Return: Returns ptr.
 *         If new_size == old_size, returns ptr without changes.
 *         If malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
    char **newptr;
    unsigned int i;

    /* Allocate new memory block if ptr is NULL */
    if (ptr == NULL)
        return (malloc(sizeof(char *) * new_size));

    /* Return ptr if new_size is equal to old_size */
    if (new_size == old_size)
        return (ptr);

    /* Allocate memory for the new double pointer */
    newptr = malloc(sizeof(char *) * new_size);
    if (newptr == NULL)
        return (NULL);

    /* Copy data from old pointer to new pointer */
    for (i = 0; i < old_size; i++)
        newptr[i] = ptr[i];

    /* Free the old pointer */
    free(ptr);

    return (newptr);
}

