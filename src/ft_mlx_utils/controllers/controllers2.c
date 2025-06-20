/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllers2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afpachec <afpachec@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:22:31 by afpachec          #+#    #+#             */
/*   Updated: 2025/06/20 02:34:05 by afpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controllers.h"

static double normalize_pressure(Sint16 value)
{
	return fmax(0.0, (double)value / 32767.0);
}

static void	set_to_raw_if_x(bool is_x, Sint16 *x, Sint16 *y, Sint16 raw)
{
	if (is_x)
		*x = raw;
	else
		*y = raw;
	if (abs(*x) < CONTROLLERS_DEADZONE)
		*x = 0;
	if (abs(*y) < CONTROLLERS_DEADZONE)
		*y = 0;
}

static t_ftm_key_hook_values	get_joystick_vals(int axis, Sint16 raw)
{
	t_ftm_key_hook_values	val;
	static Sint16			lx = 0, ly = 0, rx = 0, ry = 0;
	bool 					is_left;
	bool 					is_x;

	val = (t_ftm_key_hook_values){0};
	is_x = (axis == SDL_CONTROLLER_AXIS_LEFTX || axis == SDL_CONTROLLER_AXIS_RIGHTX);
	is_left = (axis == SDL_CONTROLLER_AXIS_LEFTX || axis == SDL_CONTROLLER_AXIS_LEFTY);
	if (is_left)
		set_to_raw_if_x(is_x, &lx, &ly, raw);
	else
		set_to_raw_if_x(is_x, &rx, &ry, raw);
	val.key = FTM_GAMEPAD_RSTICK;
	val.coords.x = fabs((double)rx / 32767.0 * 0.5 + 0.5);
	val.coords.y = fabs((double)ry / 32767.0 * 0.5 + 0.5);
	if (is_left)
	{
		val.key = FTM_GAMEPAD_LSTICK;
		val.coords.x = fabs((double)lx / 32767.0 * 0.5 + 0.5);
		val.coords.y = fabs((double)ly / 32767.0 * 0.5 + 0.5);
	}
	return (val);
}

static t_ftm_key_hook_values	get_axis_vals(SDL_Event *event)
{
	t_ftm_key_hook_values	val;
	int						axis;
	Sint16					raw;

	val = (t_ftm_key_hook_values){0};
	raw = event->caxis.value;
	axis = event->caxis.axis;
	if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT || axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
	{
		val.key = (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT) ? FTM_GAMEPAD_L2 : FTM_GAMEPAD_R2;
		val.pressure = normalize_pressure(raw);
		val.down = (val.pressure > 0.05);
		return (val);
	}
	return (get_joystick_vals(axis, raw));
}

void	ftm_controller_event_handler(void *userdata, SDL_Event *event)
{
	t_ftm_controller		*controller;
	t_ftm_key_hook_values	val;

	controller = (t_ftm_controller *)userdata;
	if (!controller || !controller->key_hook)
		return ;
	val = (t_ftm_key_hook_values){0};
	if (event->type == SDL_CONTROLLERBUTTONDOWN || event->type == SDL_CONTROLLERBUTTONUP)
	{
		val.key = -(event->cbutton.button + 1);
		val.down = (event->type == SDL_CONTROLLERBUTTONDOWN);
	}
	else if (event->type == SDL_CONTROLLERAXISMOTION)
		val = get_axis_vals(event);
	else
		return ;
	val.controller = controller;
	controller->key_hook(val);
	return ;
}
