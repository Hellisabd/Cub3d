#include "../cub3D.h"

int	init_blink(t_cub *cub)
{
	cub->world.black_t = mlx_load_png("assets/walls/black.png");
	if (cub->world.black_t == NULL)
		debug_str(RED, NULL, "failed to load textures");


	cub->world.no_t[1] = mlx_load_png("assets/walls/red_eye_2.png");
	if (cub->world.no_t[1] == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->world.no_t[2] = mlx_load_png("assets/walls/red_eye_3.png");
	if (cub->world.no_t[2] == NULL)
		debug_str(RED, NULL, "failed to load textures");


	cub->world.so_t[1] = mlx_load_png("assets/walls/blue_eye_2.png");
	if (cub->world.so_t[1] == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->world.so_t[2] = mlx_load_png("assets/walls/blue_eye_3.png");
	if (cub->world.so_t[2] == NULL)
		debug_str(RED, NULL, "failed to load textures");


	cub->world.we_t[1] = mlx_load_png("assets/walls/green_red_eye_2.png");
	if (cub->world.we_t[1] == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->world.we_t[2] = mlx_load_png("assets/walls/green_red_eye_3.png");
	if (cub->world.we_t[2] == NULL)
		debug_str(RED, NULL, "failed to load textures");


	cub->world.ea_t[1] = mlx_load_png("assets/walls/green_eye_2.png");
	if (cub->world.no_t[1] == NULL)
		debug_str(RED, NULL, "failed to load textures");
	cub->world.ea_t[2] = mlx_load_png("assets/walls/green_red_eye_3.png");
	if (cub->world.no_t[2] == NULL)
		debug_str(RED, NULL, "failed to load textures");


	cub->world.no[1] = mlx_texture_to_image(cub->mlx, cub->world.no_t[1]);
	cub->world.no[2] = mlx_texture_to_image(cub->mlx, cub->world.no_t[2]);
	cub->world.no[3] = mlx_texture_to_image(cub->mlx, cub->world.black_t);

	cub->world.so[1] = mlx_texture_to_image(cub->mlx, cub->world.so_t[1]);
	cub->world.so[2] = mlx_texture_to_image(cub->mlx, cub->world.so_t[2]);
	cub->world.so[3] = mlx_texture_to_image(cub->mlx, cub->world.black_t);

	cub->world.we[1] = mlx_texture_to_image(cub->mlx, cub->world.we_t[1]);
	cub->world.we[2] = mlx_texture_to_image(cub->mlx, cub->world.we_t[2]);
	cub->world.we[3] = mlx_texture_to_image(cub->mlx, cub->world.black_t);

	cub->world.ea[1] = mlx_texture_to_image(cub->mlx, cub->world.ea_t[1]);
	cub->world.ea[2] = mlx_texture_to_image(cub->mlx, cub->world.ea_t[2]);
	cub->world.ea[3] = mlx_texture_to_image(cub->mlx, cub->world.black_t);


	cub->world.tab_tab_no[1] = image_to_tab(cub->world.no[1]);
	cub->world.tab_tab_no[2] = image_to_tab(cub->world.no[2]);
	cub->world.tab_tab_no[3] = image_to_tab(cub->world.no[3]);

	cub->world.tab_tab_so[1] = image_to_tab(cub->world.so[1]);
	cub->world.tab_tab_so[2] = image_to_tab(cub->world.so[2]);
	cub->world.tab_tab_so[3] = image_to_tab(cub->world.so[3]);

	cub->world.tab_tab_we[1] = image_to_tab(cub->world.we[1]);
	cub->world.tab_tab_we[2] = image_to_tab(cub->world.we[2]);
	cub->world.tab_tab_we[3] = image_to_tab(cub->world.we[3]);

	cub->world.tab_tab_ea[1] = image_to_tab(cub->world.ea[1]);
	cub->world.tab_tab_ea[2] = image_to_tab(cub->world.ea[2]);
	cub->world.tab_tab_ea[3] = image_to_tab(cub->world.ea[3]);


	return (0);
}

void	blink_no(t_cub *cub)
{
	static int	i = 0;
	int	r;
	static bool b = false;

	r = rand();
	if (r % 10 == 0 && b == false)
		b = true;
	if (b == true)
	{
		if (i == 0)
		{
			cub->world.no_i = cub->world.no[0];
			cub->world.tab_no = cub->world.tab_tab_no[0];
		}
		else if (i == 1)
		{
			cub->world.no_i = cub->world.no[1];
			cub->world.tab_no = cub->world.tab_tab_no[1];
		}
		else if (i == 2)
		{
			cub->world.no_i = cub->world.no[2];
			cub->world.tab_no = cub->world.tab_tab_no[2];
		}
		else if (i == 3)
		{
			cub->world.no_i = cub->world.no[3];
			cub->world.tab_no = cub->world.tab_tab_no[3];
		}
		else if (i == 4)
		{
			cub->world.no_i = cub->world.no[2];
			cub->world.tab_no = cub->world.tab_tab_no[2];
		}
		else if (i == 5)
		{
			cub->world.no_i = cub->world.no[1];
			cub->world.tab_no = cub->world.tab_tab_no[1];
		}
		else if (i == 6)
		{
			cub->world.no_i = cub->world.no[0];
			cub->world.tab_no = cub->world.tab_tab_no[0];
			i = -1;
			b = false;
		}
		i++;
	}
}

void	blink_so(t_cub *cub)
{
	static int	i = 0;
	int	r;
	static bool b = false;

	r = rand();
	if (r % 10 == 0 && b == false)
		b = true;
	if (b == true)
	{
		if (i == 0)
		{
			cub->world.so_i = cub->world.so[0];
			cub->world.tab_so = cub->world.tab_tab_so[0];
		}
		else if (i == 1)
		{
			cub->world.so_i = cub->world.so[1];
			cub->world.tab_so = cub->world.tab_tab_so[1];
		}
		else if (i == 2)
		{
			cub->world.so_i = cub->world.so[2];
			cub->world.tab_so = cub->world.tab_tab_so[2];
		}
		else if (i == 3)
		{
			cub->world.so_i = cub->world.so[3];
			cub->world.tab_so = cub->world.tab_tab_so[3];
		}
		else if (i == 4)
		{
			cub->world.so_i = cub->world.so[2];
			cub->world.tab_so = cub->world.tab_tab_so[2];
		}
		else if (i == 5)
		{
			cub->world.so_i = cub->world.so[1];
			cub->world.tab_so = cub->world.tab_tab_so[1];
		}
		else if (i == 6)
		{
			cub->world.so_i = cub->world.so[0];
			cub->world.tab_so = cub->world.tab_tab_so[0];
			i = -1;
			b = false;
		}
		i++;
	}
}

void	blink_we(t_cub *cub)
{
	static int	i = 0;
	int	r;
	static bool b = false;

	r = rand();
	if (r % 10 == 0 && b == false)
		b = true;
	if (b == true)
	{
		if (i == 0)
		{
			cub->world.we_i = cub->world.we[0];
			cub->world.tab_we = cub->world.tab_tab_we[0];
		}
		else if (i == 1)
		{
			cub->world.we_i = cub->world.we[1];
			cub->world.tab_we = cub->world.tab_tab_we[1];
		}
		else if (i == 2)
		{
			cub->world.we_i = cub->world.we[2];
			cub->world.tab_we = cub->world.tab_tab_we[2];
		}
		else if (i == 3)
		{
			cub->world.we_i = cub->world.we[3];
			cub->world.tab_we = cub->world.tab_tab_we[3];
		}
		else if (i == 4)
		{
			cub->world.we_i = cub->world.we[2];
			cub->world.tab_we = cub->world.tab_tab_we[2];
		}
		else if (i == 5)
		{
			cub->world.we_i = cub->world.we[1];
			cub->world.tab_we = cub->world.tab_tab_we[1];
		}
		else if (i == 6)
		{
			cub->world.we_i = cub->world.we[0];
			cub->world.tab_we = cub->world.tab_tab_we[0];
			i = -1;
			b = false;
		}
		i++;
	}
}

void	blink_ea(t_cub *cub)
{
	static int	i = 0;
	int	r;
	static bool b = false;

	r = rand();
	if (r % 10 == 0 && b == false)
		b = true;
	if (b == true)
	{
		if (i == 0)
		{
			cub->world.ea_i = cub->world.ea[0];
			cub->world.tab_ea = cub->world.tab_tab_ea[0];
		}
		else if (i == 1)
		{
			cub->world.ea_i = cub->world.ea[1];
			cub->world.tab_ea = cub->world.tab_tab_ea[1];
		}
		else if (i == 2)
		{
			cub->world.ea_i = cub->world.ea[2];
			cub->world.tab_ea = cub->world.tab_tab_ea[2];
		}
		else if (i == 3)
		{
			cub->world.ea_i = cub->world.ea[3];
			cub->world.tab_ea = cub->world.tab_tab_ea[3];
		}
		else if (i == 4)
		{
			cub->world.ea_i = cub->world.ea[2];
			cub->world.tab_ea = cub->world.tab_tab_ea[2];
		}
		else if (i == 5)
		{
			cub->world.ea_i = cub->world.ea[1];
			cub->world.tab_ea = cub->world.tab_tab_ea[1];
		}
		else if (i == 6)
		{
			cub->world.ea_i = cub->world.ea[0];
			cub->world.tab_ea = cub->world.tab_tab_ea[0];
			i = -1;
			b = false;
		}
		i++;
	}
}

void	blink(t_cub *cub)
{
	cub->anim.count++;
	if (cub->anim.count % 10000 == 0)
	{
		blink_no(cub);
		blink_so(cub);
		blink_we(cub);
		blink_ea(cub);
	}
}
