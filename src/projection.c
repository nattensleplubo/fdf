#include "maker.h"

void printMatrixx(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // printf("%d ", matrix[i][j]);
        }
        // printf("\n");
    }
}

void	x_pos_rotation(int i, int j)
{
	double angle = _data()->rot_x;

	int x = _data()->fdf->p[i][j].x;
	int y = _data()->fdf->p[i][j].y;
	_data()->fdf->p[i][j].y = y * cos(angle) + _data()->fdf->p[i][j].z * sin(angle);
	_data()->fdf->p[i][j].z = -y * sin(angle) + _data()->fdf->p[i][j].z * cos(angle);
}

void	y_pos_rotation(int i, int j)
{
	double angle = _data()->rot_y;

	int x = _data()->fdf->p[i][j].x;
	int z = _data()->fdf->p[i][j].z;
	_data()->fdf->p[i][j].x = x * cos(angle) + z * sin(angle);
	_data()->fdf->p[i][j].z = -x * sin(angle) + z * cos(angle);
}

void	z_pos_rotation(int i, int j)
{
	double angle = _data()->rot_z;

	int x = _data()->fdf->p[i][j].x;
	int y = _data()->fdf->p[i][j].y;
	int z = _data()->fdf->p[i][j].z;
	_data()->fdf->p[i][j].x = x * cos(angle) - y * sin(angle);
	_data()->fdf->p[i][j].y = x * sin(angle) + y * cos(angle);
}


void	draw_background(void)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			ft_pixel_put(&_data()->graphics->menu_img, i, j, BACKGROUND);
			j++;
		}
		i++;
	}
}

void	iso(int *x, int *y, int z)
{
	// fprintf(stderr, "%d ", z);
	int previous_x;
	int previous_y;

	// *x = *x * _data()->fdf->zoom;
	// *y = *y * _data()->fdf->zoom;

	previous_x = *x;
	previous_y = *y;
	z = z;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	link_dots(void)
{
	draw_background();

	int i;
	int j;
	t_point **coord;

	coord = _data()->fdf->p;

	i = 0;
	while (i < _data()->fdf->rows)
	{
		j = 0;
		while (j < _data()->fdf->cols)
		{
			if (j != _data()->fdf->cols - 1)
				ft_draw_line(&_data()->graphics->menu_img, COLOR_FLAMINGO, coord[i][j].x + _data()->fdf->x_offset, coord[i][j].y + _data()->fdf->y_offset, coord[i][j + 1].x + _data()->fdf->x_offset, coord[i][j + 1].y + _data()->fdf->y_offset);
			if (i != _data()->fdf->rows - 1)
				ft_draw_line(&_data()->graphics->menu_img, COLOR_FLAMINGO, coord[i][j].x + _data()->fdf->x_offset, coord[i][j].y + _data()->fdf->y_offset, coord[i + 1][j].x + _data()->fdf->x_offset, coord[i + 1][j].y + _data()->fdf->y_offset);
			j++;
		}
		i++;
	}
	draw_side_menu(_data()->graphics);
	mlx_put_image_to_window(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, _data()->graphics->menu_img.image, 0, 0);
}

void	project(void)
{
	for (int i = 0; i < _data()->fdf->rows; i++)
	{
		for (int j = 0; j < _data()->fdf->cols; j++)
		{
			_data()->fdf->p[i][j].x = _data()->fdf->og_p[i][j].x;
			_data()->fdf->p[i][j].y = _data()->fdf->og_p[i][j].y;
			_data()->fdf->p[i][j].z = _data()->fdf->og_p[i][j].z;
			_data()->fdf->p[i][j].color = _data()->fdf->og_p[i][j].color;
		}
	}
	for (int i = 0; i < _data()->fdf->rows; i++) {
		for (int j = 0; j < _data()->fdf->cols; j++) {
			_data()->fdf->p[i][j].x *= _data()->fdf->zoom;
			_data()->fdf->p[i][j].y *= _data()->fdf->zoom;
			_data()->fdf->p[i][j].z *= _data()->fdf->zoom / _data()->fdf->z_offset;
			_data()->fdf->p[i][j].x -= (_data()->fdf->cols * _data()->fdf->zoom) / 2;
			_data()->fdf->p[i][j].y -= (_data()->fdf->rows * _data()->fdf->zoom) / 2;
			x_pos_rotation(i, j);
			y_pos_rotation(i, j);
			z_pos_rotation(i, j);
			iso(&_data()->fdf->p[i][j].x, &_data()->fdf->p[i][j].y, _data()->fdf->p[i][j].z);
			_data()->fdf->p[i][j].x += (WIN_HEIGHT - 200) / 2 + _data()->fdf->x_offset;
			_data()->fdf->p[i][j].y += (WIN_WIDTH + _data()->fdf->rows * _data()->fdf->zoom) / 2 + _data()->fdf->y_offset;
		}
	}
}