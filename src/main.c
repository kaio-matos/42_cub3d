#include <cub.h>

int	main(void)
{
	w__init(300, 300);
	w__open();
	mlx_loop_hook(w()->init, w__render, NULL);
	mlx_hook(w()->window, 17, WINDOW_X, w__close, NULL);
	mlx_loop(w()->init);
	mlx_loop_end(w()->init);
	return (0);
}
