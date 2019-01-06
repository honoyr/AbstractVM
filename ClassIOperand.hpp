/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassIOperand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:38:44 by dgonor            #+#    #+#             */
/*   Updated: 2018/12/05 17:38:46 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSIOPERAND_HPP
#define CLASSIOPERAND_HPP

#include <algorithm>
#include <exception>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <stack>
#include <list>

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {
public:
    virtual int                 getPrecision( void ) const = 0; // Precision of the type of the instance
    virtual eOperandType        getType( void ) const = 0; // Type of the instance
	virtual void				getPrint(void) const = 0;
    virtual IOperand const *    operator+( IOperand const & rhs ) const = 0; // Sum
    virtual IOperand const *    operator-( IOperand const & rhs ) const = 0; // Difference
    virtual IOperand const *    operator*( IOperand const & rhs ) const = 0; // Product
    virtual IOperand const *    operator/( IOperand const & rhs ) const = 0; // Quotient
    virtual IOperand const *    operator%( IOperand const & rhs ) const = 0; // Modulo
//    virtual IOperand const *    operator=( IOperand const & rhs ) const = 0; // Modulo
    virtual bool                operator==( IOperand const & rhs ) const = 0; // Equal to
//    virtual bool                operator!=( IOperand const & rhs ) const = 0; // Not Equal to
    virtual bool                operator>( IOperand const & rhs ) const = 0; // Greater than
    virtual bool                operator<( IOperand const & rhs ) const = 0; // Less than
    virtual std::string const & toString( void ) const = 0; // String representation of the instance
    virtual ~IOperand( void ) {}

};

#endif