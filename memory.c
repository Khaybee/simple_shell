#include "main.h"
/**
 * free_data - frees runtime_data
 * @data: data structure
 */
void free_data(runtime_data *data)
{
	unsigned int i;

	for (i = 0; data->_env[i] != NULL; i++)
		free(data->_env[i]);
	free(data->_env);
	free(data->pid);
}

/**
 * _realloc - reallocates memory block
 * @ptr: pointer to the prev memory allocated
 * @old_size: size of the allocated space of ptr
 * @new_size: new size of the new memory block
 * Return: ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(new_ptr, ptr, new_size);
	else
		_memcpy(new_ptr, ptr, old_size);

	free(ptr);
	return (new_ptr);
}
/**
 * _reallocdp - reallocates the memory of a a double pointer
 * @ptr: dp to the prev memory allocated
 * @old_size: size of the allocated space of ptr
 * @new_size: size of the new memory block
 * Return: ptr
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char **new_ptr;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(sizeof(char *) * new_size);
	if (new_ptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		new_ptr[i] = ptr[i];

	free(ptr);

	return (new_ptr);
}
