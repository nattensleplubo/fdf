#include "maker.h"

void	alloc_map(void)
{
	int	i = 0;
	int j = 0;
	_data()->map = malloc(sizeof(char *) * _data()->map_size + 1);
	_data()->map[_data()->map_size] = NULL;
	while (i < _data()->map_size)
	{
		_data()->map[i] = calloc(1, sizeof(char) * _data()->map_size + 2);
		_data()->map[i][_data()->map_size] = '\n';
		j = 0;
		while (j < _data()->map_size)
		{
			_data()->map[i][j] = '0';
			j++;
		}
		i++;
	}
	// ft_tabsize(_data()->map);
}

void	print_map(void)
{
	for (int i = 0; i < _data()->map_size; i++)
	{
		for (int j = 0; j < _data()->map_size; j++)
		{
			if (_data()->map[i][j] == '0')
				ft_put_rectangle(&_data()->graphics->editor_img, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLACK);
			else if (_data()->map[i][j] == '1')
				ft_put_rectangle(&_data()->graphics->editor_img, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
			else if (_data()->map[i][j] == 'N')
				ft_put_rectangle(&_data()->graphics->editor_img, i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
		}
	}
	
}

void	print_cursor(void)
{
	if (_data()->map[_data()->curs_coord[0]][_data()->curs_coord[1]] == '0')
		ft_put_rectangle(&_data()->graphics->editor_img, _data()->curs_coord[0] * 30, _data()->curs_coord[1] * 30, TILE_SIZE, TILE_SIZE, RED);
	else
		ft_put_rectangle(&_data()->graphics->editor_img, _data()->curs_coord[0] * 30, _data()->curs_coord[1] * 30, TILE_SIZE, TILE_SIZE, PINK);
}

int	update_editor(void)
{
	print_map();
	print_cursor();
	mlx_put_image_to_window(_data()->graphics->mlx_ptr, _data()->graphics->editor_ptr, _data()->graphics->editor_img.image, 0, 0);
	return (0);
}

void	do_map(void)
{
	_data()->map_created = 1;
	alloc_map();
	mlx_destroy_window(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr);
	_data()->graphics->editor_ptr = mlx_new_window(_data()->graphics->mlx_ptr, _data()->map_size * TILE_SIZE, _data()->map_size * TILE_SIZE, _data()->map_name);
	_data()->graphics->editor_img.image = mlx_new_image(_data()->graphics->mlx_ptr, MENU_WIDTH, MENU_HEIGHT);
	_data()->graphics->editor_img.addr = mlx_get_data_addr(_data()->graphics->editor_img.image, &_data()->graphics->editor_img.bpp, &_data()->graphics->editor_img.line_length, &_data()->graphics->editor_img.endian);

	mlx_hook(_data()->graphics->editor_ptr, 17, 0L, exit_game, NULL);
	mlx_key_hook(_data()->graphics->editor_ptr, &editor_key, NULL);
	mlx_loop_hook(_data()->graphics->mlx_ptr, &update_editor, NULL);
}

int	move_possible(int next_x, int next_y)
{
	if (next_x > _data()->map_size - 1 || next_y > _data()->map_size - 1 || next_x < 0 || next_y < 0)
		return (0);
	return (1);
}

void	write_map(void)
{
	int	fd = open(_data()->map_name, O_RDWR | O_TRUNC);
	int i = 0;
	int	j = 0;

	write(fd, "NO sprites/Bricks.xpm\n", 22);
	write(fd, "EA sprites/Castle-Wall.xpm\n", 27);
	write(fd, "WE sprites/Metal.xpm\n", 21);
	write(fd, "SO sprites/Wood.xpm\n\n", 21);
	write(fd, "F 252,253,255\n", 14);
	write(fd, "C 1,2,2\n\n", 9);

	// while (_data()->map[i])
	// {
	// 	write(fd, _data()->map[i], ft_strlen(_data()->map[i]));
	// 	i++;
	// }

	while (i < _data()->map_size)
	{
		j = 0;
		while (j < _data()->map_size)
		{
			write(fd, &_data()->map[j][i], 1);
			j++;
		}
		write(fd, "\n", 1);
		i++;
	}

	close(fd);
	exit (0);
}


int	editor_key(int keycode)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		exit_game();
	if ((keycode == KEY_D || keycode == KEY_RIGHT) && move_possible(_data()->curs_coord[0] + 1, _data()->curs_coord[1]))
		_data()->curs_coord[0]++;
	if ((keycode == KEY_A || keycode == KEY_LEFT) && move_possible(_data()->curs_coord[0] - 1, _data()->curs_coord[1]))
		_data()->curs_coord[0]--;
	if ((keycode == KEY_W || keycode == KEY_UP) && move_possible(_data()->curs_coord[0], _data()->curs_coord[1] - 1))
		_data()->curs_coord[1]--;
	if ((keycode == KEY_S || keycode == KEY_DOWN) && move_possible(_data()->curs_coord[0], _data()->curs_coord[1] + 1))
		_data()->curs_coord[1]++;
	if (keycode == 32)
	{
		if (_data()->map[_data()->curs_coord[0]][_data()->curs_coord[1]] == '0')
			_data()->map[_data()->curs_coord[0]][_data()->curs_coord[1]] = '1';
		else if (_data()->map[_data()->curs_coord[0]][_data()->curs_coord[1]] == '1' || _data()->map[_data()->curs_coord[0]][_data()->curs_coord[1]] == 'N')
			_data()->map[_data()->curs_coord[0]][_data()->curs_coord[1]] = '0';
	}
	if (keycode == 110)
		_data()->map[_data()->curs_coord[0]][_data()->curs_coord[1]] = 'N';
	if (keycode == 65293)
		write_map();

	return (0);
}

int	print_menu(int keycode)
{
	printf("keycode : %d\n", keycode);
	if (keycode == KEY_UP /*&& i <= 100*/)
		_data()->map_size++;
	else if (keycode == KEY_DOWN && _data()->map_size != 0)
		_data()->map_size--;
	else if (keycode == KEY_ESC || keycode == KEY_Q)
		exit (0);
	else if (keycode == 65293 && _data()->map_size >= 3)
		do_map();
	printf("map size : %d\n", _data()->map_size);
	return (0);
}