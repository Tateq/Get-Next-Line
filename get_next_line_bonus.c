#include "get_next_line_bonus.h"

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

void	append(t_list **list, char *buf, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(list[fd]);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL) //malloc check
		return ;
	if (last_node == NULL) // se list == NULL  (retorno da função find_last_node)
		list[fd] = new_node; //cria um nó para a lista vazia 
	else 
		last_node->next = new_node; //adiciona o nó para o último nó da lista 
	
	new_node->str_buf = buf; //adiciona a str+\0 ao monte
	new_node->next = NULL;
}

void	create_list(t_list	**list, int fd)
{
	int		char_read;
	char	*buf;
	
	while (found_newline(list[fd]) == 0) // enquanto n achar um \n no tamanho do buffer
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
		append (list, buf, fd);
	}
}

/*
Take a fd
returns the next_string
*/

char	*get_next_line(int fd)
{
	static t_list	*list [1025];
	char			*next_line;
    
    //fd are only positives | read gives -1 if some problems on reading
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 
		|| (read(fd, &next_line, 0) < 0))
		return (NULL);
	//create a list until a '\n'
	create_list(list, fd);
	if (list[fd] == NULL) //checa se a lista está vazia || n tem next line
		return (NULL);

	next_line = gt_line(list[fd]);
	
    polish_list(&list[fd]);
	return (next_line);
}

/*int	main()

{
	char	*s;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("file.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
	fd3 = open("file3.txt", O_RDONLY);
	i = 1;
	while (i < 15)
	{
		s = get_next_line(fd1);
		printf("line [%02d] from file 1: %s\n", i, s);
		free(s);
		s = get_next_line(fd2);
		printf("line [%02d] from file 2: %s\n", i, s);
		free(s);
		s = get_next_line(fd3);
		printf("line [%02d] from file 3: %s\n", i, s);
		free(s);
		printf ("\n");
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}