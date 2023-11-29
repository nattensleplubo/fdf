// TODO :
// Get the menu going for now :)

#include "maker.h"

int	exit_game()
{
	exit (0);
}

void	data_init(t_data *data)
{
	data->curs_coord[0] = 0;
	data->curs_coord[1] = 0;
	data->map_size = 0;
	data->map_created = 0;
	data->graphics = malloc(sizeof(t_mlx));
}

t_data	*_data(void)
{
	static t_data	*data = NULL;

	if (!data)
	{
		data = malloc(sizeof(t_data));
		data_init(data);
	}
	return (data);
}

void	init_menu(void)
{
	_data()->graphics->mlx_ptr = NULL;
	_data()->graphics->menu_ptr = NULL;
	_data()->graphics->menu_img.image = NULL;
	_data()->graphics->mlx_ptr = mlx_init();
	_data()->graphics->menu_ptr = mlx_new_window(_data()->graphics->mlx_ptr, MENU_HEIGHT, MENU_WIDTH, "MENU");
	_data()->graphics->menu_img.image = mlx_new_image(_data()->graphics->mlx_ptr, MENU_WIDTH, MENU_HEIGHT);
	_data()->graphics->menu_img.addr = mlx_get_data_addr(_data()->graphics->menu_img.image, &_data()->graphics->menu_img.bpp, &_data()->graphics->menu_img.line_length, &_data()->graphics->menu_img.endian);
}

void	hooks_menu(void)
{
	// _data()->graphics->menu_img.image = mlx_get_data_addr(_data()->graphics->menu_img.image, &_data()->graphics->menu_img.bpp, &_data()->graphics->menu_img.line_length, &_data()->graphics->menu_img.endian);
	mlx_hook(_data()->graphics->menu_ptr, 17, 0L, exit_game, NULL);
	mlx_key_hook(_data()->graphics->menu_ptr, &print_menu, NULL);
	mlx_loop_hook(_data()->graphics->mlx_ptr, &update_window, NULL);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	_data()->map_name = argv[1];
	init_menu();
	hooks_menu();
	mlx_loop(_data()->graphics->mlx_ptr);
}