#include <cub.h>

t_window	*w(void)
{
	static t_window	window_instance;

	return (&window_instance);
}

void	w__init(int width, int height)
{
	t_window	*win;

	win = w();
	win->width = width;
	win->height = height;
	win->init = mlx_init();
	if (!win->init)
		printf("MLX could not be initialized\n"); // TODO: handle error
}

void	w__open(void)
{
	t_window	*win;

	win = w();
	win->window = mlx_new_window(win->init, win->width, win->height, "So_Long");
	if (!win->window)
		printf("MLX window could be opened\n"); // TODO: handle error
}

int	w__close(void)
{
	if (w()->init && w()->window)
		mlx_destroy_window(w()->init, w()->window);
	if (w()->init)
	{
		mlx_destroy_display(w()->init);
		free(w()->init);
	}
	return (0);
}
