/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassFactory.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:38:15 by dgonor            #+#    #+#             */
/*   Updated: 2018/12/05 17:38:17 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ClassFactory.hpp"
#include "ClassOperand.hpp"
#include <climits>

IOperand const * Factory::createInt8( std::string const & value ) const {
	return (new Operand<char>(static_cast<char>(std::stoi(value))));
}
IOperand const * Factory::createInt16( std::string const & value ) const {
	return (new Operand<short>(static_cast<short>(std::stoi(value))));
}
IOperand const * Factory::createInt32( std::string const & value ) const {
	return (new Operand<int>(static_cast<int>(std::stoi(value))));
}
IOperand const * Factory::createFloat( std::string const & value ) const {
	return (new Operand<float>(static_cast<float>(std::stof(value))));
}
IOperand const * Factory::createDouble( std::string const & value ) const {
	return (new Operand<double>(static_cast<double>(std::stod(value))));
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
    IOperand const	*(Factory::*method[])(std::string const &value) const = {
            &Factory::createInt8,
            &Factory::createInt16,
            &Factory::createInt32,
            &Factory::createFloat,
            &Factory::createDouble
    };
    return ((this->*method[type])(value));
}