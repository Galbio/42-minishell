typedef s_list {
    void *content;
    struct s_list *next;
}   t_list;

void ft_list_remove_if(t_list **begin, void *data_ref, int (*cmp)())
{
    t_list *ptr;

    if (*begin)
    {
        ptr = *begin;
        if (cmp((*begin)->data, data_ref) == 0)
        {
            begin = &(*begin)->next;
            free(ptr);
            ft_list_remove_if(begin, data_ref, cmp);
        }
        else
        {
            ft_list_remove_if(&(*begin)->next, data_ref, cmp);
        }
    }
}