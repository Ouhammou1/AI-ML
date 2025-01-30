/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_maths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:50:39 by bouhammo          #+#    #+#             */
/*   Updated: 2024/12/24 16:42:13 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle <= 0)
        angle = 2 * M_PI + angle;
    return angle;
}

double	deg_to_rad(double deg)
{
	double angle;

	angle = deg  * (M_PI / 180.0);
	return (angle);
}

double	rad_to_deg(double red)
{
	return (red * (180.0 / M_PI));
}

bool  is_looking_down(double angle)
{
	if(angle > 0 && angle < M_PI)
		return true;
	return false;
}

bool  is_looking_up (double angle)
{
	if(is_looking_down(angle) == false)
		return true;
	return false;
}

bool is_looking_right(double angle)
{
	if(angle  < (0.5 * M_PI) || angle > (1.5 * M_PI))
		return true;
	return false;
}

bool is_looking_left(double angle)
{
	if(is_looking_right(angle) == false)
		return true;
	return false;
}