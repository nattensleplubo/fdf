#include "maker.h"

void printMatrixx(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // printf("%d ", matrix[i][j]);
        }
        // printf("\n");
    }
}

void	x_pos_rotation(void)
{
	for (int i = 0; i < _data()->fdf->rows; i++)
	{
		for (int j = 0; j < _data()->fdf->cols; j++)
		{
			int x = _data()->fdf->p[i][j].x;
			int y = _data()->fdf->p[i][j].y;
			_data()->fdf->p[i][j].y = y * cos(0.1) + _data()->fdf->p[i][j].z * sin(0.1);
			_data()->fdf->p[i][j].z = -y * sin(0.1) + _data()->fdf->p[i][j].z * cos(0.1);
		}
	}
}

// void	x_neg_rotation(void)
// {

// }

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
			ft_pixel_put(&_data()->graphics->menu_img, i, j, BLACK);
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

	*x = *x * _data()->fdf->zoom;
	*y = *y * _data()->fdf->zoom;

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
			if (i != _data()->fdf->rows - 1)
				ft_draw_line(&_data()->graphics->menu_img, AQUA, coord[i][j].x + _data()->fdf->x_offset, coord[i][j].y + _data()->fdf->y_offset, coord[i + 1][j].x + _data()->fdf->x_offset, coord[i + 1][j].y + _data()->fdf->y_offset);
			if (j != _data()->fdf->cols - 1)
				ft_draw_line(&_data()->graphics->menu_img, AQUA, coord[i][j].x + _data()->fdf->x_offset, coord[i][j].y + _data()->fdf->y_offset, coord[i][j + 1].x + _data()->fdf->x_offset, coord[i][j + 1].y + _data()->fdf->y_offset);
			j++;
		}
		i++;
	}
	draw_side_menu(_data()->graphics);
	mlx_put_image_to_window(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, _data()->graphics->menu_img.image, 0, 0);
}

void	project(void)
{
	_data()->fdf->projected_map = ft_cpy_int_tab(_data()->fdf->map, _data()->fdf->rows, _data()->fdf->cols);
	for (int i = 0; i < _data()->fdf->rows; i++) {
		for (int j = 0; j < _data()->fdf->cols; j++) {
			iso(&_data()->fdf->p[i][j].x, &_data()->fdf->p[i][j].y, _data()->fdf->p[i][j].z);
		}
	}
}