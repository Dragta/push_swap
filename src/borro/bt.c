void	start_bt(t_compendium *all)
{
/*	const int	c_m[] = {0, 14, 14, 14, 32, 16, 2688, 3136, 3584, 1344, 896, 448};
	const int	h_m[] = {0, 3470, 2894, 14, 0, 0,
		3972, 3906, 3584, 3460, 3394, 448};

	all->cut_mask = (int *)c_m;
	all->heir_mask = (int *)h_m;*/
	all->done[0] = 0;
	all->cut[0] = 0;
	all->tolerance = TOLERANCE;
	count_stacks(all);
	backtrack(all);
}
