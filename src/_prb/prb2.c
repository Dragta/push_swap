#include <stdio.h>
#include <unistd.h>

void	print_1_step(int op)
{
	if (op < 1 || op > 11)
		return ;
	if (op ==  3)
		write(1, "s", 1);
	if (op < 4)
		write(1, "s", 1);
	else if (op < 6)
		write(1, "p", 1);
	else
		write(1, "r", 1);
	if (op > 7)
		write(1, "r", 1);
	if (594 & (1 << op))
		write(1, "a", 1);
	if (1188 & (1 << op))
		write(1, "b", 1);
	if (op ==  11)
		write(1, "r", 1);
	write(1, "\n", 1);
}

int	main(void)
{
	char	i;

	i = -1 + '0';
	while (++i < (14 + '0'))
	{
		write(1, &i, 1);
		write(1, ": ", 2);
		print_1_step(i - '0');
	}
	return (0);
}
