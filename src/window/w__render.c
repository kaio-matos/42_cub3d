#include <cub.h>

int	w__render(void)
{
	static unsigned int	timer;

	timer += 1;
	if (timer <= 120)
		return (0);
	if (!w())
		return (1);
	timer = 0;
	return (0);
}
