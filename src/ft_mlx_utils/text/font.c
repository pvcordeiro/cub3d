/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 23:44:03 by afpachec          #+#    #+#             */
/*   Updated: 2025/05/20 01:07:29 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "text.h"

static void	load_char(t_ftm_window *window, t_ftm_font *font, unsigned char c)
{
	char		*path;
	t_ftm_image	*img;

	path = ft_strf("%s/%d.xpm", font->dir, c);
	if (!path)
		return ;
	img = ftm_image_from_file(window, path, true);
	free(path);
	if (img)
		font->characters[c] = img;
}

static char	*get_clean_dir(const char *dir)
{
	if (!dir)
		return (NULL);
	if (ft_str_endswith(dir, "/"))
		return (ft_strndup(dir, ft_strlen(dir) - 1));
	return (ft_strdup(dir));
}

t_ftm_font	*ftm_font_new(t_ftm_window *window, const char *dir)
{
	t_ftm_font	*font;
	char	*clean_dir;
	int		i;

	font = ft_calloc(1, sizeof(t_ftm_font));
	if (!font)
		return (NULL);
	clean_dir = get_clean_dir(dir);
	if (!clean_dir)	
		return (free(font), NULL);
	font->dir = clean_dir;
	i = -1;
	while (++i < 255)
		load_char(window, font, i);
	return (font);
}

void	ftm_clear_font(void *font)
{
	int		i;

	if (!font)
		return ;
	i = -1;
	while (++i < 255)
		ftm_free_image(((t_ftm_font *)font)->characters[i]);
	free(((t_ftm_font *)font)->dir);
}

void	ftm_free_font(void *font)
{
	ftm_clear_font(font);
	free(font);
}
