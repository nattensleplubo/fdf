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

	_data()->fdf = malloc(sizeof(t_fdf));
	_data()->fdf->zoom = 20;
	_data()->fdf->x_offset = 500;
	_data()->fdf->y_offset = 200;
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
	srand(time(NULL));
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
			int randomNumber = rand() % 201;
			map[i][j] = randomNumber;
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

void translate_matrix_to_point_struct(void)
{
	int i;
	int x;
	int y;
	_data()->fdf->p = malloc(sizeof(t_point *) * _data()->fdf->rows);
	i = 0;
	while (i < _data()->fdf->rows)
	{
		_data()->fdf->p[i] = malloc(sizeof(t_point) * _data()->fdf->cols);
		i++;
	}
	x = 0;
	while (x < _data()->fdf->rows)
	{
		y = 0;
		while (y < _data()->fdf->cols)
		{
			_data()->fdf->p[x][y].x = x;
			_data()->fdf->p[x][y].y = y;
			_data()->fdf->p[x][y].z = _data()->fdf->map[x][y];
			y++;
		}
		x++;
	}
}

void	string_to_int_tab(char *str, int x)
{
	char	**splitted_line;
	int		i;

	splitted_line = ft_split(str, ' ');
	i = 0;
	while (splitted_line[i])
		i++;
	_data()->fdf->cols = i;
	_data()->fdf->map[x] = malloc(sizeof(int) * i);
	i = 0;
	while (splitted_line[i])
	{
		printf("%s ", splitted_line[i]);
		_data()->fdf->map[x][i] = ft_atoi(splitted_line[i]);
		i++;
	}
}

void	file_to_map(void)
{
	int tmp_fd;
	_data()->fdf->rows = 0;

	tmp_fd = open(_data()->map_name, O_RDONLY);
	while (get_next_line(tmp_fd))
		_data()->fdf->rows++;
	close(tmp_fd);
	tmp_fd = open(_data()->map_name, O_RDONLY);
	_data()->map_char = malloc(sizeof(char *) * _data()->fdf->rows);
	_data()->fdf->map = malloc(sizeof(int *) * _data()->fdf->rows);
	for (int i = 0; i < _data()->fdf->rows; i++)
	{
		_data()->map_char[i] = get_next_line(tmp_fd);
		// printf("%s", _data()->map_char[i]);
		string_to_int_tab(_data()->map_char[i], i);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	_data()->map_name = argv[1];
	init_menu();
    draw_side_menu(_data()->graphics);
	// _data()->fdf->map = generate_fake_map();
	file_to_map();
	printMatrix(_data()->fdf->map, _data()->fdf->rows, _data()->fdf->cols);
	translate_matrix_to_point_struct();
	project();
    mlx_put_image_to_window(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, _data()->graphics->menu_img.image, 0, 0);
	mlx_loop(_data()->graphics->mlx_ptr);
}
