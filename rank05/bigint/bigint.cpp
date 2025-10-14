/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:25:00 by razaccar          #+#    #+#             */
/*   Updated: 2025/10/04 16:18:42 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: check input string is only digits

#include "bigint.hpp"
#include <cstddef>
#include <string>
#include <iostream>

bigint::bigint() : number_("0") {}

bigint::bigint(int part) : number_(std::to_string(part)) {}

bigint::bigint(std::string const& part) : number_(part) {}

bigint::bigint(bigint const& other) : number_(other.number_) {}

bigint::~bigint() {}

void	align_numbers(std::string& s1, std::string& s2) {
	int diff = s1.size() - s2.size();
	if (diff < 0) diff *= -1;
	if (s1.size() < s2.size()) s1.insert(0, diff, '0');
	if (s2.size() < s1.size()) s2.insert(0, diff, '0');
}

std::string	add(std::string const& lhs, std::string const& rhs) {
	std::string result;
	std::string s1(lhs);
	std::string s2(rhs);

	align_numbers(s1, s2);
	int	sum = 0, rest = 0;
	for (int i = s1.size() - 1; i >= 0; i--) {
		int d1 = s1[i] - '0';
		int d2 = s2[i] - '0';
		sum = d1 + d2 + rest;
		result.insert(result.begin(), (sum % 10) + '0');
		rest = sum / 10;
	}
	return result;
}

bigint&	bigint::operator=(bigint const& rhs) {
	if (this == &rhs) return *this;
	number_ = rhs.number_;
	return *this;
}

bigint	bigint::operator+(bigint const& rhs) {
	bigint result(add(number_, rhs.number_));
	return result;
}

bigint&	bigint::operator+=(bigint const& rhs) {
	number_ = add(number_, rhs.number_);
	return *this;
}

bigint	bigint::operator++(int) {
	bigint result(*this);
	number_ = add(number_, "1");
	return result;
}

bigint&	bigint::operator++() {
	number_ = add(number_, "1");
	return *this;
}

bool	bigint::operator<(bigint const& rhs) {
	if (number_.compare(rhs.number_) < 0) return true;
	return false;
}

bool	bigint::operator<=(bigint const& rhs) {
	if (number_.compare(rhs.number_) < 0) return true;
	if (number_.compare(rhs.number_) == 0) return true;
	return false;
}

bool	bigint::operator>(bigint const& rhs) {
	if (number_.compare(rhs.number_) > 0) return true;
	return false;
}

bool	bigint::operator>=(bigint const& rhs) {
	if (number_.compare(rhs.number_) > 0) return true;
	if (number_.compare(rhs.number_) == 0) return true;
	return false;
}

bool	bigint::operator==(bigint const& rhs) {
	if (number_.compare(rhs.number_) == 0) return true;
	return false;
}

bool	bigint::operator!=(bigint const& rhs) {
	if (number_.compare(rhs.number_) == 0) return false;
	return true;
}

bigint	bigint::operator>>(int i) {
	bigint result(*this);
	if (i >= result.number_.size()) {
		result.number_ = "0";
		return result;
	}
	result.number_.erase(result.number_.size() - i, i);
	return result;
}

bigint	bigint::operator<<(int i) {
	bigint result(*this);
	result.number_.append(i, '0');
	return result;
}

bigint	bigint::operator>>(bigint const& rhs) {
	bigint result(*this);
	return result >> std::stol(rhs.number_, NULL);
}

bigint	bigint::operator<<(bigint const& rhs) {
	bigint result(*this);
	return result << std::stol(rhs.number_, NULL);
}

bigint& bigint::operator>>=(int i) {
	*this = *this >> i;
	return *this;
}

bigint& bigint::operator<<=(int i) {
	*this = *this << i;
	return *this;
}

bigint& bigint::operator>>=(bigint const& rhs) {
	*this = *this >> rhs;
	return *this;
}

bigint& bigint::operator<<=(bigint const& rhs) {
	*this = *this << rhs;
	return *this;
}

std::ostream&	operator<<(std::ostream& os, bigint const& bigint) {
	os << bigint.getNumber();
	return os;
}

std::string	bigint::getNumber() const {
	return number_;
}
