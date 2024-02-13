// TODO :
// Get the menu going for now :)

#include "maker.h"

int	exit_game()
{
	exit (0);
}

void	data_init(t_data *data)
{
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
	_data()->graphics->menu_ptr = mlx_new_window(_data()->graphics->mlx_ptr, WIN_HEIGHT, WIN_WIDTH, _data()->map_name);
	_data()->graphics->menu_img.image = mlx_new_image(_data()->graphics->mlx_ptr, WIN_HEIGHT, WIN_WIDTH);
	_data()->graphics->menu_img.addr = mlx_get_data_addr(_data()->graphics->menu_img.image, &_data()->graphics->menu_img.bpp, &_data()->graphics->menu_img.line_length, &_data()->graphics->menu_img.endian);
}

void draw_side_menu(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	int color = GREY;
	while (i < WIN_WIDTH)
	{
		j = WIN_HEIGHT - 200;
		while (j < WIN_HEIGHT)
		{
			mlx->menu_img.addr[i * (mlx->menu_img.line_length) + (j * (mlx->menu_img.bpp / 8))] = (color & 0xFF0000) >> 16;
			mlx->menu_img.addr[i * (mlx->menu_img.line_length) + (j * (mlx->menu_img.bpp / 8)) + 1] = (color & 0xFF00) >> 8;
			mlx->menu_img.addr[i * (mlx->menu_img.line_length) + (j * (mlx->menu_img.bpp / 8)) + 2] = (color & 0xFF);
			j++;
		}
		i++;
	}
}


// void	hooks_menu(void)
// {
// 	// _data()->graphics->menu_img.image = mlx_get_data_addr(_data()->graphics->menu_img.image, &_data()->graphics->menu_img.bpp, &_data()->graphics->menu_img.line_length, &_data()->graphics->menu_img.endian);
// 	mlx_hook(_data()->graphics->menu_ptr, 17, 0L, exit_game, NULL);
// 	mlx_key_hook(_data()->graphics->menu_ptr, &print_menu, NULL);
// 	mlx_loop_hook(_data()->graphics->mlx_ptr, &update_window, NULL);
// }

int **generate_fake_map() {
	int	**map;
	int	i;
	int	j;

	i = 0;
	map = (int **)malloc(sizeof(int *) * 5);
	if (!map)
		return (NULL);
	while (i < 5)
	{
		map[i] = (int *)malloc(sizeof(int) * 5);
		j = 0;
		while (j < 5)
		{
			map[i][j] = j + i;
			j++;
		}
		i++;
	}
	return (map);
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	_data()->map_name = argv[1];
	init_menu();
    draw_side_menu(_data()->graphics);
	_data()->map = generate_fake_map();
	printMatrix(_data()->map, 5, 5);
    mlx_put_image_to_window(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, _data()->graphics->menu_img.image, 0, 0);
	mlx_loop(_data()->graphics->mlx_ptr);
}
