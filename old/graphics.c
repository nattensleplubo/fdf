#include "maker.h"

void    ft_pixel_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    //TODO research to understand this formula cf aurelienbrabant.fr
	if (x < 0)
		return ;
	if (y < 0)
		return ;
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(int *)pixel = color;
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 500)
	{
		j = 0;
		while (j < 500)
		{
			ft_pixel_put(img, j++, i, color);
		}
		++i;
	}
}

void     ft_put_rectangle(t_img *img, int x0, int y0, int x1, int y1, int color)
{
    int pY;
    int pX;

    pY = y0;
    while (pY < y0 + x1)
    {
        pX = x0;
        while (pX < x0 + y1)
            ft_pixel_put(img, pX++, pY, color);
        pY++;
    }
}

// int	update_window(void)
// {
// 	char	*number;

// 	number = ft_itoa(_data()->map_size);
// 	render_background(&_data()->graphics->menu_img, BLACK);
// 	mlx_put_image_to_window(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, _data()->graphics->menu_img.image, 0, 0);
// 	if (_data()->map_created == 0)
// 	{
// 		mlx_string_put(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, (WIN_HEIGHT / 2) - 80, (WIN_WIDTH / 2) - 20, 0x00FFFFFF, "Choose the size of the map :");
// 		mlx_string_put(_data()->graphics->mlx_ptr, _data()->graphics->menu_ptr, WIN_HEIGHT / 2 , WIN_WIDTH / 2, 0x00FFFFFF, number);
// 	}
// 	return (0);
// }