/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassOperand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:46:29 by dgonor            #+#    #+#             */
/*   Updated: 2018/12/05 17:46:31 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLASSOPERAND_HPP
#define CLASSOPERAND_HPP

#include "ClassIOperand.hpp"
#include "ClassFactory.hpp"
#include <typeinfo>
#include <stdlib.h>
#include <cstdlib>

template <typename T>
class Operand : public IOperand{

public:
    Operand(void) : str("0"), type(Int8){}
    Operand(T value) : str(std::to_string(value)), type(identify_type()){}
    Operand(Operand const &copy){
        type = copy.getType();
        str = copy.toString();
    }
	Operand(IOperand const *rhs){
		this->str = (*rhs).toString();
		this->type = (*rhs).getType();
	}
    ~Operand(){}


    eOperandType		getType(void)       const { return (this->type); }
    std::string const & toString( void )    const { return str; }
	int					getPrecision(void)  const { return (static_cast<int>(type)); }

    IOperand const * operator+( IOperand const & rhs ) const {

        std::cout   <<  rhs.getPrecision() // DELETE
                    << std::end
                    << this->getPrecision()
                    << std::end;


        if (rhs.getPrecision() > this->getPrecision())
             return (rhs + *this);
        return (factory.createOperand(this->type, std::to_string(
                convert_type(rhs.toString()) + convert_type(this->toString()))));
    }

    IOperand const * operator-( IOperand const & rhs ) const {

        std::cout   <<  rhs.getPrecision() // DELETE
                    << std::end
                    << this->getPrecision()
                    << std::end;

        if (rhs.getPrecision() > this->getPrecision())
        {
            if (rhs.getType() == Int16)
            {

            }
            if (rhs.getType() == Int32)
            if (rhs.getType() == Float)
            if (rhs.getType() == Double)
                return ()
            return (rhs + *this);
        }
        return (factory.createOperand(this->type, std::to_string(
                convert_type(rhs.toString()) - convert_type(this->toString()))));
    }

private:
    std::string     str;
    Factory			factory;
    eOperandType    type;

    eOperandType		identify_type(void)
    {
        if (typeid(char) == typeid(T))
            return (Int8);
        else if (typeid(short int) == typeid(T))
            return (Int16);
        else if (typeid(int) == typeid(T))
            return (Int32);
        else if (typeid(float) == typeid(T))
            return (Float);
        else if (typeid(double) == typeid(T))
            return (Double);
        else
            return (Double);
    }

    T				    convert_type(std::string str) const
    {
        if (type == Int8)
            return ((static_cast<char>(std::stoi(str))));
        else if (type == Int16)
            return ((static_cast<short int>(std::stoi(str))));
        else if (type == Int32)
            return ((static_cast<int>(std::stoi(str))));
        else if (type == Float)
            return (std::stof(str));
        else
            return (std::stod(str));
    }
};

#endif