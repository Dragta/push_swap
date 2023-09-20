
void	count_stacks(t_compendium *all)
{
	t_data	*i;
	int		p;
	int		s;

	s = -1;
	while (++s < 2)
	{
		all->count[s] = 0;
		i = all->top[s];
		if (!i)
			continue ;
		i->pos = all->min_target - s;
		p = 0;
		while (i != all->block_top[s])
		{
			i->pos = all->top[s]->pos + s + (1 - 2 * s) * (p++ + s);
			i = i->next;
			if (i == all->top[s])
				break ;
		}
		all->count[s] = p;
		if (all->count_blocked[s])
		{
			i = all->top[s]->prev;
			p = 0;
			while (i != all->block_btm[s])
			{
				i->pos = all->top[s]->pos - (s + 1) * ++p;
				i = i->prev;
			}
			all->count[s] += p + all->count_blocked[s];
		}
	}
}
