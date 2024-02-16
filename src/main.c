// TODO :
// Get the menu going for now :)

#include "maker.h"

int	exit_game()
{
	exit (0);
}

int	mouse_press(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	fprintf(stderr, " %d ", button);
	if (button == 4)
		_data()->fdf->zoom++;
	if (button == 5)
		_data()->fdf->zoom--;
	if (button == 1 || button == 3)
	{
		if (button == 1 && _data()->fdf->mouse_pressed == 0 && _data()->fdf->mouse_r_pressed == 0)
		{
			mlx_mouse_hide(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr);
			_data()->fdf->mouse_pressed = 1;
		}
		else if (button == 1 && _data()->fdf->mouse_pressed == 1 && _data()->fdf->mouse_r_pressed == 0)
		{
			mlx_mouse_show(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr);
			_data()->fdf->mouse_pressed = 0;
		}
		if (button == 3 && _data()->fdf->mouse_r_pressed == 0 && _data()->fdf->mouse_pressed == 0)
		{
			mlx_mouse_hide(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr);
			_data()->fdf->mouse_r_pressed = 1;
		}
		else if (button == 3 && _data()->fdf->mouse_r_pressed == 1 && _data()->fdf->mouse_pressed == 0)
		{
			mlx_mouse_show(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr);
			_data()->fdf->mouse_r_pressed = 0;
		}
		mlx_mouse_move(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, WIN_HEIGHT / 2, WIN_WIDTH / 2);
	}
	return (1);
}

int	mouse_release(int button, int x, int y, void *param)
{
	printf("coucou\n");
	(void)x;
	(void)y;
	(void)param;
	(void)button;
	_data()->fdf->mouse_pressed = 0;
	return (1);
}

int	mouse_move(int x, int y, void *param)
{
	(void)param;

	_data()->fdf->mouse_previous_x = _data()->fdf->mouse_x;
	_data()->fdf->mouse_previous_y = _data()->fdf->mouse_y;
	_data()->fdf->mouse_x = x;
	_data()->fdf->mouse_y = y;


	if (_data()->fdf->mouse_pressed == 1)
	{
		_data()->rot_x += (x - _data()->fdf->mouse_previous_x) * 0.002;
		_data()->rot_y += (y - _data()->fdf->mouse_previous_y) * 0.002;
		project();
		link_dots();
	}
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
	_data()->fdf->zoom = 12;
	_data()->fdf->x_offset = 0;
	_data()->fdf->y_offset = 0;
	_data()->fdf->z_offset = 1;

	_data()->w = 0;
	_data()->a = 0;
	_data()->s = 0;
	_data()->d = 0;
	_data()->projected = 0;
	_data()->rot_x = 0;
	_data()->rot_y = 0;
	_data()->rot_z = 0;
	_data()->fdf->mouse_pressed = 0;
	_data()->fdf->mouse_r_pressed = 0;
	_data()->fdf->mouse_x = 0;
	_data()->fdf->mouse_y = 0;
	_data()->fdf->mouse_mute = 0;
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


void	hooks_menu(void)
{
	// _data()->graphics->menu_img.image = mlx_get_data_addr(_data()->graphics->menu_img.image, &_data()->graphics->menu_img.bpp, &_data()->graphics->menu_img.line_length, &_data()->graphics->menu_img.endian);
	mlx_hook(_data()->graphics->menu_ptr, 17, 0L, exit_game, NULL);
	mlx_hook(_data()->graphics->menu_ptr, 2, 1L << 0, move_around, NULL);
	mlx_mouse_hook(_data()->graphics->menu_ptr, &mouse_press, NULL);
	// mlx_hook(_data()->graphics->menu_ptr, 5, 1 << 5, mouse_release, NULL);
	// mlx_hook(_data()->graphics->menu_ptr, 6, 0L, mouse_move, NULL);
	// mlx_mouse_move(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr,)

	// mlx_hook(_data()->graphics->menu_ptr, 3, 1L << 1, key_release, NULL);
	// mlx_loop_hook(_data()->graphics->mlx_ptr, &update_window, NULL);
}

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
            // printf("%d ", matrix[i][j]);
        }
        // printf("\n");
    }
}

void translate_matrix_to_point_struct(void)
{
	int i;
	int x;
	int y;
	int aqua = AQUA;
	int blue = BLUE;
	_data()->fdf->p = malloc(sizeof(t_point *) * _data()->fdf->rows);
	_data()->fdf->og_p = malloc(sizeof(t_point *) * _data()->fdf->rows);
	i = 0;
	while (i < _data()->fdf->rows)
	{
		_data()->fdf->p[i] = malloc(sizeof(t_point) * _data()->fdf->cols);
		_data()->fdf->og_p[i] = malloc(sizeof(t_point) * _data()->fdf->cols);
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
			if (_data()->fdf->p[x][y].z > 3)
			{
				_data()->fdf->p[x][y].color = aqua;
				_data()->fdf->og_p[x][y].color = aqua;
			}
			else
			{
				_data()->fdf->p[x][y].color = blue;
				_data()->fdf->og_p[x][y].color = blue;
			}
			_data()->fdf->og_p[x][y].x = x;
			_data()->fdf->og_p[x][y].y = y;
			_data()->fdf->og_p[x][y].z = _data()->fdf->map[x][y];
			y++;
		}
		x++;
	}
}

void	string_to_int_tab(char *str, int x)
{
	char	**splitted_line;
	int		i;
	int		j;

	splitted_line = ft_split(str, ' ');
	i = 0;
	while (splitted_line[i])
		i++;
	_data()->fdf->cols = i;
	_data()->fdf->map[x] = malloc(sizeof(int) * i);
	j = i - 1;
	i = 0;
	while (splitted_line[i])
	{
		// printf("%s ", splitted_line[i]);
		_data()->fdf->map[x][i] = ft_atoi(splitted_line[j]);
		j--;
		i++;
	}
}

void	file_to_map(void)
{
	int tmp_fd;
	_data()->fdf->rows = 0;

	tmp_fd = open(_data()->map_name, O_RDONLY);
	fprintf(stderr, "Calculating rows... ");
	while (get_next_line(tmp_fd))
		_data()->fdf->rows++;
	close(tmp_fd);
	fprintf(stderr, "Done!\n");
	tmp_fd = open(_data()->map_name, O_RDONLY);
	_data()->map_char = malloc(sizeof(char *) * _data()->fdf->rows);
	_data()->fdf->map = malloc(sizeof(int *) * _data()->fdf->rows);
	fprintf(stderr, "Reading map and putting in int matrix... ");
	for (int i = 0; i < _data()->fdf->rows; i++)
	{
		_data()->map_char[i] = get_next_line(tmp_fd);
		string_to_int_tab(_data()->map_char[i], i);
	}
	fprintf(stderr, "Done !\n");
}

int	move_around(int key, void *param)
{
	(void)param;

	if (key == KEY_W)
		_data()->fdf->y_offset += _data()->fdf->zoom;
	else if (key == KEY_S)
		_data()->fdf->y_offset -= _data()->fdf->zoom;
	else if (key == KEY_A)
		_data()->fdf->x_offset += _data()->fdf->zoom;
	else if (key == KEY_D)
		_data()->fdf->x_offset -= _data()->fdf->zoom;
	else if (key == 61)
	{
		_data()->fdf->zoom = _data()->fdf->zoom + 1;
	}
	else if (key == 45)
		_data()->fdf->zoom = _data()->fdf->zoom - 1;
	else if (key == KEY_LEFT)
		_data()->rot_x += 0.05;
	else if (key == KEY_RIGHT)
		_data()->rot_x -= 0.05;
	else if (key == KEY_UP)
		_data()->rot_y += 0.05;
	else if (key == KEY_DOWN)
		_data()->rot_y -= 0.05;
	else if (key == KEY_Q)
		_data()->rot_z += 0.05;
	else if (key == KEY_E)
		_data()->rot_z -= 0.05;
	else if (key == KEY_R)
		_data()->fdf->z_offset -= 0.02;
	else if (key == KEY_F)
		_data()->fdf->z_offset += 0.02;
	else if (key == KEY_ESC)
		exit(0);
	project();
	link_dots();
}

int	update_window(void)
{
	if (_data()->w == 1)
	{
		_data()->fdf->y_offset = _data()->fdf->y_offset - 6;
		_data()->w = 0;
	}
	if (_data()->s == 1)
	{
		_data()->fdf->y_offset = _data()->fdf->y_offset + 6;
		_data()->s = 0;
	}
	if (_data()->a == 1)
	{
		_data()->fdf->x_offset = _data()->fdf->x_offset - 6;
		_data()->a = 0;
	}
	if (_data()->d == 1)
	{
		_data()->fdf->x_offset = _data()->fdf->x_offset + 6;
		_data()->d = 0;
	}


	if (_data()->fdf->mouse_pressed == 1 || _data()->fdf->mouse_r_pressed == 1)
	{
		int x;
		int y;
		mlx_mouse_get_pos(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, &x, &y);
		if (x != WIN_HEIGHT / 2 || y != WIN_WIDTH / 2)
		{
			if (_data()->fdf->mouse_pressed == 1)
			{
				if (_data()->fdf->mouse_previous_x != x && !_data()->fdf->mouse_r_pressed)
				{
					_data()->fdf->mouse_previous_x = WIN_HEIGHT / 2;
					_data()->fdf->mouse_x = x;
					_data()->rot_x += (x - _data()->fdf->mouse_previous_x) * 0.002;
				}
				if (_data()->fdf->mouse_previous_y != y && !_data()->fdf->mouse_r_pressed)
				{
					_data()->fdf->mouse_previous_y = WIN_WIDTH / 2;
					_data()->fdf->mouse_y = y;
					_data()->rot_y += (y - _data()->fdf->mouse_previous_y) * 0.002;
				}
			}
			else if (_data()->fdf->mouse_r_pressed == 1)
			{
				_data()->fdf->x_offset += x - WIN_HEIGHT / 2;
				_data()->fdf->y_offset += y - WIN_WIDTH / 2;
			}
			mlx_mouse_move(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, WIN_HEIGHT / 2, WIN_WIDTH / 2);
		}
	}
	project();
	link_dots();
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	_data()->map_name = argv[1];
	init_menu();
	hooks_menu();

	printf("File to map ...\n");
	file_to_map();
	printf("File to map done\n");

	printf("Matrix to point structure ...\n");
	translate_matrix_to_point_struct();
	printf("Matrix to point structure done\n");

	printf("Projection ...\n");
	project();
	printf("Projection done\n");

	printf("Dots linking ...\n");
	link_dots();
	printf("Dots linking done\n");

	mlx_put_image_to_window(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, _data()->graphics->menu_img.image, 0, 0);
	mlx_loop_hook(_data()->graphics->mlx_ptr, &update_window, NULL);
	mlx_loop(_data()->graphics->mlx_ptr);
}
