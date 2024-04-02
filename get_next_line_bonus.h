#ifndef GET_NEXT_LINE_BONUSH
#define GET_NEXT_LINE_BONUSH

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

#include <fcntl.h> //for 0_RDONLY
#include <stdlib.h> //for malloc and free
#include <unistd.h> //for printf, BUFFER_SIZE
#include <stdio.h> 

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;

int		found_newline(t_list *list);
t_list	*find_last_node(t_list *list);
char	*gt_line(t_list *list);
void	copy_str(t_list *list, char *str);
int		len_to_newline(t_list *list);
void	polish_list(t_list **list);
char	*get_next_line(int fd);
void	dealloc(t_list **list, t_list *clean_node, char *buf);
void	create_list(t_list **list, int fd);
void	append(t_list **list, char *buf, int fd);

#endif