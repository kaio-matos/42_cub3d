#include <cub.h>

t_posd	create_posd(double x, double y)
{
	t_posd pd;

	pd.x = x;
	pd.y = y;
	return (pd);
}

t_posi	create_posi(int x, int y)
{
	t_posi pd;

	pd.x = x;
	pd.y = y;
	return (pd);
}

t_posd	posi_to_posd(t_posi pi)
{
	t_posd pd;

	pd.x = pi.x;
	pd.y = pi.y;
	return (pd);
}

void	print_posi(t_posi p, char *name)
{
	if (name)
		printf("%s: { x: %i, y: %i }\n", name, p.x, p.y);
	else
		printf("{ x: %i, y: %i }\n", p.x, p.y);
}

void	print_posd(t_posd p, char *name)
{
	if (name)
		printf("%s: { x: %f, y: %f }\n", name, p.x, p.y);
	else
		printf("{ x: %f, y: %f }\n", p.x, p.y);
}

