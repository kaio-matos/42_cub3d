#include <cub.h>

t_state *state(void)
{
	static t_state	state;

	return (&state);
}
