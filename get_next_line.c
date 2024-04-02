/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tornelas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:44:56 by tornelas          #+#    #+#             */
/*   Updated: 2024/03/27 20:34:02 by tornelas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//vai pegar os chars n usados no último gnl
void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buf;
	
	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node == NULL) //malloc check
		return ;
	last_node = find_last_node(*list);
	
	i = 0;
	j = 0;
	while (last_node->str_buf[i] != '\0'
		&& last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] != '\0'
		&& last_node->str_buf[++i])
		buf[j++] = last_node->str_buf[i];
	buf[j] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc (list, clean_node, buf);
}	

char	*gt_line(t_list *list)	//get line\n
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1); //por causa do \0
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
	
}

void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL) //malloc check
		return ;
	if (last_node == NULL) // se list == NULL  (retorno da função find_last_node)
		*list = new_node; //cria um nó para a lista vazia 
	else 
		last_node->next = new_node; //adiciona o nó para o último nó da lista 
	
	new_node->str_buf = buf; //adiciona a str+\0 ao monte
	new_node->next = NULL;
}

void	create_list(t_list	**list, int fd)
{
	int		char_read;
	char	*buf;
	
	while (found_newline(*list) == 0) // enquanto n achar um \n no tamanho do buffer
	{
		buf = malloc(BUFFER_SIZE +1); //+1 por conta do \0 obrigatório
		if (buf == NULL) //checa se o malloc funcionou 
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read) //if doesnt read any char in the fd
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append (list, buf);
	}
}

/*
Take a fd
returns the next_string
*/

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
    char			*next_line;
    
    //fd are only positives | read gives -1 if some problems on reading
    if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, &next_line, 0) < 0)
		return (NULL);
	//create a list until a '\n'
	create_list(&list, fd);

	if (list == NULL) //checa se a lista está vazia || n tem next line
		return (NULL);

	next_line = gt_line(list);
	
    polish_list(&list);
	return (next_line);
}

/*int	main()
{
	int	fd;
	char *line;
	int lines;
	
	lines = 1;
	fd = open("text.txt", O_RDONLY);

	while ((line = get_next_line(fd)))
		printf ("%d->%s\n", lines++, line);
}*/