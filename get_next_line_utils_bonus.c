#include "get_next_line_bonus.h"

//Corre pela string até achar um '\n'
int	found_newline(t_list *list) 
{
	int	i;

	if (list == NULL)
		return (0);

	while (list)
	{
		i = 0;
		while (list->str_buf[i] != '\0' && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

//Acha o último nó da lista 
t_list	*find_last_node(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next) // enquanto houver outro nó || para quando list->next == NULL
		list = list->next; //vai para o próximo nó da lista até chegar no último 
	return (list); //retorna o último nó (next == NULL)
}

//Acha o tamanho para a nova linha na Linked list
int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

//Copia a string\n
void	copy_str(t_list *list, char *str)
{
	int	i;
	int	j;

	if (list == NULL)
		return ;
	j = 0;
	while (list)
	{
		i = 0; // define i para 0 sempre pra pegar o primeiro char da string
		while (list->str_buf[i] != '\0')
		{
			if (list->str_buf[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->str_buf[i++];
		}
		list = list->next; // vai para a próxima string
	}
	str[j] = '\0';
}

void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*temp;

	if (*list == NULL)
		return ;

	while (*list)
	{
		temp = (*list)->next;
		free ((*list)->str_buf);
		free (*list);
		*list = temp;
	}
	*list = NULL;
	if (clean_node->str_buf[0])
		*list = clean_node;
	else
	{
		free (buf);
		free (clean_node);
	}
}