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