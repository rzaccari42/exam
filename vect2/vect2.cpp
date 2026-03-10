/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 01:54:09 by razaccar          #+#    #+#             */
/*   Updated: 2025/10/02 22:48:51 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

vect2::vect2() : x_(0), y_(0) {}

vect2::vect2(int x, int y) : x_(x), y_(y) {}

vect2::vect2(vect2 const& other) : x_(other.x_), y_(other.y_) {}

vect2::~vect2() {}

vect2&	vect2::operator=(vect2 const& vect) {
	if (this == &vect)
		return *this;
	x_ = vect.x_; 
	y_ = vect.y_; 
	return *this;
}

vect2&	vect2::operator+=(int i) {
	x_ += i;
	y_ += i;
	return *this;
}

vect2&	vect2::operator+=(vect2 const& vect) {
	x_ += vect.x_;
	y_ += vect.y_;
	return *this;
}

vect2&	vect2::operator-=(int i) {
	x_ -= i;
	y_ -= i;
	return *this;
}

vect2&	vect2::operator-=(vect2 const& vect) {
	x_ -= vect.x_;
	y_ -= vect.y_;
	return *this;
}

vect2&	vect2::operator*=(int i) {
	x_ -= i;
	y_ -= i;
	return *this;
}

vect2&	vect2::operator*=(vect2 const& vect) {
	x_ *= vect.x_;
	y_ *= vect.y_;
	return *this;
}

vect2	vect2::operator++(int) {
	vect2 v = *this;
	x_ -= 1;
	y_ -= 1;
	return v;
}

vect2&	vect2::operator++() {
	x_ += 1;
	y_ += 1;
	return *this;
}

vect2	vect2::operator--(int) {
	vect2 v = *this;
	x_ -= 1;
	y_ -= 1;
	return v;
}

vect2&	vect2::operator--() {
	x_ -= 1;
	y_ -= 1;
	return *this;
}

bool	vect2::operator==(vect2 const& vect) {
	if (x_ == vect.x_ && y_ == vect.y_)
		return true;
	return false;
}

bool	vect2::operator!=(vect2 const& vect) {
	return !operator==(vect);
}

int&	vect2::operator[](int i) {
	switch (i) {
		case 0:	return x_;
		case 1: return y_;
		default: return x_;
	}
}

int const	vect2::getX() const {
	return x_;
}

int const	vect2::getY() const {
	return y_;
}

vect2	operator+(vect2 const& lhs, int i) {
	vect2 v = lhs;
	return v += i;
}

vect2	operator+(int i, vect2 const& vect) {
	vect2 v = vect;
	return v += i;
}

vect2	operator-(vect2 const& lhs, int i) {
	vect2 v = lhs;
	return v -= i;
}

vect2	operator-(int i, vect2 const& vect) {
	vect2 v = vect;
	return v -= i;
}

vect2	operator*(vect2 const& lvect, vect2 const& rvect) {
	vect2 v = lvect;
	return v *= rvect;
}

vect2	operator*(vect2 const& vect, int i) {
	vect2 v = vect;
	return v *= i;
}

vect2	operator*(int i, vect2 const& vect) {
	vect2 v = vect;
	return v *= i;
}

std::ostream&	operator<<(std::ostream& os, vect2 const& vect) {
	os << "{" << vect.getX() << "," << vect.getY() << "}" << std::endl;
	return os;
}
