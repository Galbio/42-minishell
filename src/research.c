

#include "regex.h"

static void	nothing(int key, void *value)
{
	(void)key;
	(void)value;
}

static void	add_to_list(t_list **head, t_list **cur, void *value)
{
	if (!(*head))
	{
		*head = ft_lstnew(value);
		*cur = *head;
		return ;
	}
	(*cur)->next = ft_lstnew(value);
	*cur = (*cur)->next;
}

t_list	*search_pattern(char *path, char *pattern)
{
	t_array	all;
	int		i;
	t_list	*head;
	t_list	*cur;

	all = ft_scandir(path, SCANDIR_SORT_DESCENDING, pattern[0] == '.', 0);
	i = 0;
	head = NULL;
	while (i < ft_array_count(all))
	{
		if (regex_match((char *)all[i], pattern))
			add_to_list(&head, &cur, all[i]);
		else
			free(all[i]);
		i++;
	}
	ft_array_unset(&all, nothing);
	return (head);
}