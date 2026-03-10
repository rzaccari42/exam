/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 01:38:11 by razaccar          #+#    #+#             */
/*   Updated: 2025/10/03 02:53:35 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <ostream>

class vect2 {
	public:
		vect2();
		vect2(int x, int y);
		vect2(vect2 const& other);
		~vect2();

		vect2&	operator=(vect2 const& vect);
		vect2&	operator+=(int i);
		vect2&	operator+=(vect2 const& vect);
		vect2&	operator-=(int i);
		vect2&	operator-=(vect2 const& vect);
		vect2&	operator*=(int i);
		vect2&	operator*=(vect2 const& vect);
		vect2	operator++(int);
		vect2&	operator++();
		vect2	operator--(int);
		vect2&	operator--();
		bool	operator==(vect2 const& vect);
		bool	operator!=(vect2 const& vect);
		int&	operator[](int i);

		int const	getX() const;
		int const	getY() const;
	private:
		int	x_;
		int	y_;
};

vect2	operator+(int i, vect2 const& vect);
vect2	operator-(vect2 const& vect, int i);
vect2	operator-(int i, vect2 const& vect);
vect2	operator*(vect2 const& lvect, vect2 const& rvect);
vect2	operator*(vect2 const& vect, int i);
vect2	operator*(int i, vect2 const& vect);

std::ostream&	operator<<(std::ostream& os, vect2 const& vect);
