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
#include <cmath>

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
    ~Operand(void){}


    eOperandType		getType(void)       const { return (this->type); }
    std::string const & toString( void )    const { return str; }
	int					getPrecision(void)  const { return (static_cast<int>(type)); }

    template <typename Z>
    IOperand const *    convert_diff_type(Z a, Z b, eOperandType type, char c) const
    {
        if (b == 0)
            throw DivideByZeroExcept();
        else if (c == '-')
            return (factory.createOperand(type, std::to_string(a - b)));
        else if (c == '/')
            return (factory.createOperand(type, std::to_string(a / b)));
        else if (c == '%')
        {
            if (typeid(Z) == typeid(float) || typeid(Z) == typeid(double))
                return (factory.createOperand(type, std::to_string(fmod(a, b))));
            else
                return (factory.createOperand(type, std::to_string((static_cast<int>(a)
                                                                    % static_cast<int>(b)))));
        }
    }

//    template <typename X>
//    bool    compare(X &a, X &b, eOperandType type, char c) const
//    {
//
//        if (c == '<')
//            return (factory.createOperand(type, std::to_string(a - b)));
//        else if (c == '>')
//            return (factory.createOperand(type, std::to_string(a / b)));
//        else if (c == '==')
//        {
//            if (typeid(Z) == typeid(float) || typeid(Z) == typeid(double))
//                return (factory.createOperand(type, std::to_string(fmod(a, b)));
//            else
//                return (factory.createOperand(type, std::to_string((static_cast<int>(a)
//                                                                    % static_cast<int>(b)))));
//        }
//        else
//        {
//
//        }
//    }
//
//	Operand		&operator=(const IOperand & rhs ) {
//
//		this->str = (*rhs).toString();
//		this->type = (*rhs).getType();
//	}
//
//	Operand		&operator=(IOperand const & rhs ) {
//
//		this->str = std::to_string(this->value);
//		this->type = (*rhs).getType();
//		return (*this);
//	}

    IOperand const * operator+( IOperand const & rhs ) const {

//        std::cout   <<  rhs.getPrecision() // DELETE
//                    << std::endl
//                    << this->getPrecision()
//                    << std::endl;


        if (rhs.getPrecision() > this->getPrecision())
             return (rhs + *this);
        return (factory.createOperand(this->type, std::to_string(
                convert_type(rhs.toString()) + convert_type(this->toString()))));
    }

    IOperand const * operator-( IOperand const & rhs ) const {
        if (rhs.getPrecision() > this->getPrecision())
        {
            if (rhs.getType() == Int16)
                return (convert_diff_type(static_cast<short>(std::stoi(this->str)), static_cast<short>(std::stoi(rhs.toString())), rhs.getType(), '-'));
            else if (rhs.getType() == Int32)
                return (convert_diff_type(std::stoi(this->str), std::stoi(rhs.toString()), rhs.getType(), '-'));
            else if (rhs.getType() == Float)
                return (convert_diff_type(std::stof(this->str), std::stof(rhs.toString()), rhs.getType(), '-'));
            else if (rhs.getType() == Double)
                return (convert_diff_type(std::stod(this->str), std::stod(rhs.toString()), rhs.getType(), '-'));
        }
        return (factory.createOperand(this->type, std::to_string(
                convert_type(rhs.toString()) - convert_type(this->toString()))));
    }

    IOperand const * operator*( IOperand const & rhs ) const {

        if (rhs.getPrecision() > this->getPrecision())
            return (rhs * *this);
        return (factory.createOperand(this->type, std::to_string(
                convert_type(rhs.toString()) * convert_type(this->toString()))));
    }

    IOperand const * operator/( IOperand const & rhs ) const {

        if (rhs.getPrecision() > this->getPrecision())
        {
            if (rhs.getType() == Int16)
                return (convert_diff_type(static_cast<short>(std::stoi(this->str)), static_cast<short>(std::stoi(rhs.toString())), rhs.getType(), '/'));
            else if (rhs.getType() == Int32)
                return (convert_diff_type(std::stoi(this->str), std::stoi(rhs.toString()), rhs.getType(), '/'));
            else if (rhs.getType() == Float)
                return (convert_diff_type(std::stof(this->str), std::stof(rhs.toString()), rhs.getType(), '/'));
            else if (rhs.getType() == Double)
                return (convert_diff_type(std::stod(this->str), std::stod(rhs.toString()), rhs.getType(), '/'));
        }
        if (convert_type(rhs.toString()) == 0)
            throw DivideByZeroExcept();
        return (factory.createOperand(this->type, std::to_string(
                convert_type(rhs.toString()) / convert_type(this->toString()))));
    }

    IOperand const * operator%( IOperand const & rhs ) const {

        if (rhs.getPrecision() > this->getPrecision())
        {
            if (rhs.getType() == Int16)
                return (convert_diff_type((static_cast<short>(std::stoi(this->str))),
                                          (static_cast<short>(std::stoi(rhs.toString()))), rhs.getType(), '%'));
            else if (rhs.getType() == Int32)
                return (convert_diff_type((std::stoi(this->str)), (std::stoi(rhs.toString())), rhs.getType(), '%'));
            else if (rhs.getType() == Float)
                return (convert_diff_type((std::stof(this->str)), (std::stof(rhs.toString())), rhs.getType(), '%'));
            else if (rhs.getType() == Double)
                return (convert_diff_type((std::stod(this->str)), (std::stod(rhs.toString())), rhs.getType(), '%'));

        }
        if (convert_type(rhs.toString()) == 0)
            throw DivideByZeroExcept();
        return (factory.createOperand(this->type, std::to_string(fmod(convert_type(rhs.toString()),
                                                                      convert_type(this->toString())))));
    }


//    bool            operator<( IOperand const & rhs ) const {
//        if (rhs.getPrecision() > this->getPrecision())
//        {
//            if (rhs.getType() == Int16)
//                return (compare(static_cast<short>(std::stoi(this->str)),
//                                          static_cast<short>(std::stoi(rhs.toString()), '<');
//            else if (rhs.getType() == Int32)
//                return (compare((std::stoi(this->str)), (std::stoi(rhs.toString()), '<');
//            else if (rhs.getType() == Float)
//                return (compare(std::stof(this->str), (std::stof(rhs.toString()), '<');
//            else if (rhs.getType() == Double)
//                return (compare(std::stod(this->str), (std::stod(rhs.toString()), '<');
//        }
//        return (compare(convert_type(rhs.toString()), convert_type(this->toString())));
//    }

    bool            operator<( IOperand const & rhs ) const {

        if (rhs.getType() == Int8)
            return ((static_cast<char>(std::stoi(this->str)) <
                     static_cast<char>(std::stoi(rhs.toString()))));
        if (rhs.getType() == Int16)
            return ((static_cast<short>(std::stoi(this->str)) <
                     static_cast<short>(std::stoi(rhs.toString()))));
        else if (rhs.getType() == Int32)
            return ((std::stoi(this->str)) < (std::stoi(rhs.toString())));
        else if (rhs.getType() == Float)
            return ((std::stof(this->str) < (std::stof(rhs.toString()))));
        else if (rhs.getType() == Double)
            return ((std::stod(this->str) < (std::stod(rhs.toString()))));
        else
            return ((convert_type(rhs.toString()) < convert_type(this->toString())));
    }

    bool            operator>( IOperand const & rhs ) const {

        if (rhs.getType() == Int8)
            return ((static_cast<char>(std::stoi(this->str)) >
                     static_cast<char>(std::stoi(rhs.toString()))));
        if (rhs.getType() == Int16)
            return ((static_cast<short>(std::stoi(this->str)) >
                     static_cast<short>(std::stoi(rhs.toString()))));
        else if (rhs.getType() == Int32)
            return ((std::stoi(this->str)) > (std::stoi(rhs.toString())));
        else if (rhs.getType() == Float)
            return ((std::stof(this->str) > (std::stof(rhs.toString()))));
        else if (rhs.getType() == Double)
            return ((std::stod(this->str) > (std::stod(rhs.toString()))));
        else
            return ((convert_type(rhs.toString()) > convert_type(this->toString())));
    }


    bool            operator==( IOperand const & rhs ) const {

        if (rhs.getType() == Int8)
            return ((static_cast<char>(std::stoi(this->str)) ==
                     static_cast<char>(std::stoi(rhs.toString()))));
        if (rhs.getType() == Int16)
            return ((static_cast<short>(std::stoi(this->str)) ==
                     static_cast<short>(std::stoi(rhs.toString()))));
        else if (rhs.getType() == Int32)
            return ((std::stoi(this->str)) == (std::stoi(rhs.toString())));
        else if (rhs.getType() == Float)
            return ((std::stof(this->str) == (std::stof(rhs.toString()))));
        else if (rhs.getType() == Double)
            return ((std::stod(this->str) == (std::stod(rhs.toString()))));
        else
            return ((convert_type(rhs.toString()) == convert_type(this->toString())));
    }

    bool            operator!=( IOperand const & rhs ) const {

        if (rhs.getType() == Int8)
            return ((static_cast<char>(std::stoi(this->str)) !=
                     static_cast<char>(std::stoi(rhs.toString()))));
        if (rhs.getType() == Int16)
            return ((static_cast<short>(std::stoi(this->str)) !=
                     static_cast<short>(std::stoi(rhs.toString()))));
        else if (rhs.getType() == Int32)
            return ((std::stoi(this->str)) != (std::stoi(rhs.toString())));
        else if (rhs.getType() == Float)
            return ((std::stof(this->str) != (std::stof(rhs.toString()))));
        else if (rhs.getType() == Double)
            return ((std::stod(this->str) != (std::stod(rhs.toString()))));
        else
            return ((convert_type(rhs.toString()) != convert_type(this->toString())));
    }

    class DivideByZeroExcept : public std::exception{
    public:
        DivideByZeroExcept(void){}
        const char *what() const throw()
        {
            std::string error_exept("Error: It's bad practise divide by '0' ");
            return (error_exept.c_str());
        }
    };


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
            return ((std::stoi(str)));
        else if (type == Float)
            return (std::stof(str));
        else
            return (std::stod(str));
    }
};

#endif