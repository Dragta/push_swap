#include <stdio.h>
#include <stdlib.h>

void	fn(void)
{
	system("leaks -q prb");
}

int	main()
{
	char	*pru;
	int		i;

/*	setvbuf(stdout, NULL, _IONBF, 0);*/
	atexit(fn);
	pru = "esto es un texto\n";
	printf("%s", pru);
	printf("addr %p\n", pru);
	i = -1;
	while (++i < 18)
		printf("%c %i\n", pru[i], (int)pru[i]);
	pru = "otro\n";
	printf("%s", pru);
	printf("addr %p\n", pru);
	i = -1;
	while (++i < 18)
		printf("%c %i\n", pru[i], (int)pru[i]);
	return (0);
}
