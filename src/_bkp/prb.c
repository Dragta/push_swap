#include <stdio.h>

int	main(void)
{
	int	var;
	int	sgn;

	var = 5;
	sgn = -1;
	printf("ini 1: sgn: %i, var: %i\n", sgn, var);
	while (sgn > 0 && var--)
		printf("sgn: %i, var: %i\n", sgn, var);
	printf("ini 2: sgn: %i, var: %i\n", sgn, var);
	while (sgn < 0 && var--)
		printf("sgn: %i, var: %i\n", sgn, var);
	return (0);
}
ini 1: sgn: -1, var: 5
ini 2: sgn: -1, var: 5
sgn: -1, var: 4
sgn: -1, var: 3
sgn: -1, var: 2
sgn: -1, var: 1
sgn: -1, var: 0
