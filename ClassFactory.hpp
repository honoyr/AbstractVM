/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassFactory.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:38:15 by dgonor            #+#    #+#             */
/*   Updated: 2018/12/05 17:38:17 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLASSFACTORY_HPP
#define CLASSFACTORY_HPP

#include "ClassIOperand.hpp"

class Factory{

public:
	Factory ();
	Factory(Factory const &rhs);
	~Factory();

	Factory &operator=(Factory const &rhs);

    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private:
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;

};

#endif