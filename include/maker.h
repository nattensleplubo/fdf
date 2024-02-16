#ifndef MAKER_H

# define MAKER_H

//! DEFINES
# define WIN_WIDTH 900
# define WIN_HEIGHT 1600

# define KEY_ESC 65307
# define KEY_Q 113
# define KEY_E 101

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

# define KEY_R 114
# define KEY_F 102

# define RED 0xFF0000
# define LGREY 0x808080
# define GREY 0x1E1E1E
# define BLACK 0x1000000
# define BACKGROUND 0x222222
# define WHITE 0xFFFFFF
# define LIME 0x00FF00 
# define GREEN 0x008000 
# define PURPLE 0x800080 
# define TEAL 0x008080 
# define BLUE 0x0000FF 
# define AQUA 0x00FFFF
# define PINK 0xFFC0CB

# define COLOR_DISCO		0x9A1F6A
# define COLOR_BRICK_RED	0xC2294E
# define COLOR_FLAMINGO		0xEC4B27
# define COLOR_JAFFA		0xEF8633
# define COLOR_SAFFRON		0xF3AF3D

# define SOL_1 0xF89F5B
# define XMUR_1 0xE53F71
# define YMUR_1 0x9C3587
# define PLA_1 0x653780

# define SOL_2 0x3F1651
# define XMUR_2 0x3F1651
# define YMUR_2 0x3F1651
# define PLA_2 0x3F1651

# define FT_ABS(X) (((X) < 0) ? (-(X)) : (X))

//!LIBRARIES
# include <time.h>
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include <limits.h>
# include "libft.h"


//! STRUCTS
typedef struct	s_data
{
	char	*map_name;
	char	**map_char;
	int		fd;

	struct s_mlx	*graphics;
	struct s_fdf	*fdf;
	
	int				map_created;

	int	w;
	int	a;
	int	s;
	int	d;

	int projected;

	double rot_x;
	double rot_y;
	double rot_z;
}	t_data;

typedef struct s_fdf {
	int **map;
	int **projected_map;
	int rows;
	int cols;
	int map_max_height;
	int zoom;

	int		x_offset;
	int		y_offset;
	float	z_offset;

	int mouse_pressed;
	int mouse_r_pressed;
	int	mouse_x;
	int	mouse_y;
	int mouse_previous_x;
	int mouse_previous_y;
	int mouse_mute;

	struct s_point	**p;
	struct s_point	**og_p;
}				t_fdf;

typedef struct	s_img
{
	void	*image;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_point
{
	int x;
	int y;
	int z;
	int color;
}				t_point;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*editor_ptr;
	void	*menu_ptr;
	void	*window_ptr;
	t_img	menu_img;
	t_img	editor_img;
}	t_mlx;

//! PROTOS
t_data	*_data(void);
void	project(void);
void    ft_pixel_put(t_img *img, int x, int y, int color);
void	ft_draw_line(t_img *img, int color, int x1, int y1, int x2, int y2);
void	ft_color_line(t_img *img, t_point point, int x1, int y1, int x2, int y2);
void	link_dots(void);
int	move_around(int key, void *param);
void	x_pos_rotation(int i, int j);
void	y_pos_rotation(int i, int j);
void	z_pos_rotation(int i, int j);

#endif
