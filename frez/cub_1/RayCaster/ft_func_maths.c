/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_maths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:50:39 by bouhammo          #+#    #+#             */
/*   Updated: 2024/12/01 19:26:49 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

bool  is_looking_up(double angle)
{
	if(rad_to_deg(angle) > 180 && rad_to_deg(angle) < 360)
		return true;
	return false;
}

bool is_looking_down(double angle)
{
	
	if(rad_to_deg(angle) > 0 && rad_to_deg(angle) < 180)
		return true;
	return false;
}

bool is_looking_right(double angle)
{
	// printf(" cos = [%f] \n\n", cos(angle));

	if((angle < (0.5 * M_PI) ) ||  ( angle > (1.5 * M_PI)))
		return true;
	return false;
    // if ((angle >= 0 && angle < 90) || (angle >= 270 && angle < 360))
    //     return true;
    // return false;
}

bool is_looking_left(double angle)
{
	printf(" cos = [%f] \n\n", cos(angle));
	if(cos(angle) <= 0 )
		return true;
	return false;
    // angle = rad_to_deg(angle);
    // if (angle >= 90 && angle < 270)
    //     return true;
    // return false;
}




// bool is_looking_right(double angle)
// {
// 	printf(" ------+>>>>> /////////////////////////////   \n\n ");

// 	if(rad_to_deg(angle) < 90 && rad_to_deg(angle) > 270)
// 		return true;
// 	return false;
// }
// bool is_looking_left(double angle)
// {
// 	printf("  --------======???? ||||||||||||||||||||||||||||||||||||||||||||||||||   \n\n ");

// 	if(rad_to_deg(angle) > 90 && rad_to_deg(angle) < 270)
// 		return true;
// 	return false;
// }

