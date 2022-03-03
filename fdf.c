/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghan <eel-ghan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:27:01 by eel-ghan          #+#    #+#             */
/*   Updated: 2022/03/03 01:55:27 by eel-ghan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// void	img_pix_put(t_img *img, t_point p, int color)
// {
// 	char	*pixel;

// 	if (p.x < WIDTH & p.y >= 0 && p.y < HEIGHT)
// 	{
// 		pixel = img->addr + (p.y * img->line_len + p.x * (img->bpp / 8));
// 		*(int *)pixel = color;
// 	}
// }

void	img_pix_put(t_img *img, t_point p, int color)
{
	char    *pixel;
	int		i;

	if (p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT)
	{
		i = img->bpp - 8;
		pixel = img->addr + (p.y * img->line_len + p.x * (img->bpp / 8));
		while (i >= 0)
		{
			/* big endian, MSB is the leftmost bit */
			if (img->endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			/* little endian, LSB is the leftmost bit */
			else
				*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		if (open(av[1], O_RDONLY) == -1)
			terminate(ERR_MAP_READING);
		read_file(&data, av[1]);
		if (display(data, av[1]))
			terminate(ERR_MAP_READING);
	}
	else
		terminate(ERR_USAGE);
	return (0);
}