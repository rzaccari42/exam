/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razaccar <razaccar@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:24:41 by razaccar          #+#    #+#             */
/*   Updated: 2025/10/04 15:39:37 by razaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class bigint {
	public:
		bigint();
		bigint(int part);
		bigint(std::string const& part);
		bigint(bigint const& other);
		~bigint();

		bigint& operator=(bigint const& bigint);
		bigint	operator+(bigint const& bigint);
		bigint&	operator+=(bigint const& bigint);
		bigint	operator++(int);
		bigint&	operator++();

		bool	operator<(bigint const& bigint);
		bool	operator<=(bigint const& bigint);
		bool	operator>(bigint const& bigint);
		bool	operator>=(bigint const& bigint);
		bool	operator==(bigint const& bigint);
		bool	operator!=(bigint const& bigint);

		bigint	operator>>(int i);
		bigint	operator<<(int i);
		bigint	operator>>(bigint const& bigint);
		bigint	operator<<(bigint const& bigint);
		bigint& operator>>=(int i);
		bigint& operator<<=(int i);
		bigint& operator>>=(bigint const& bigint);
		bigint& operator<<=(bigint const& bigint);

		std::string	getNumber() const;
	private:
		std::string	number_;
};

std::ostream&	operator<<(std::ostream& os, bigint const& bigint);
