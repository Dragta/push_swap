#include <math.h>
#include <stdio.h>

int	main(void)
{
	int		n, tot = 610;
	double	nd, phi;

	phi = (sqrt(5)-1)/2 * tot;
	nd = phi;
	n = -1;
	while (++n < 500)
	{
		printf("%i ", (int)nd);
		nd += phi;
		if (nd > tot)
			nd -= tot;
	}
	return (0);
}
