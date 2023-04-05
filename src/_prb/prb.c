#include <stdio.h>

int	suma(int a)
{
	return (a + 1);
}

int	resta(int a)
{
	return (a - 1);
}

void	asigna(int (**f) (int))
{
	f[0] = &suma;
	f[1] = &resta;
}

int	main(void)
{
	int	(*f[2])(int);

	asigna(f);
	printf("después del 5, el %i\n", (*f[0])(5));
	printf("antes del 5, el %i\n", (*f[1])(5));
	return (0);
}
