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

template <typename T>
class Operand : public IOperand{

public:
	Operand(){}
	~Operand(){}

	private:
		std::string     str;
		eOperandType    type;
		Factory			factory;

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
				return (NULL);
		}

		T					convert_type(std::string str) const
		{
			if (type == Int8)
				return ((static_cast<char>(atoi(str))));
			else if (type == Int16)
				return ((static_cast<short int>(atoi(str))));
			else if (type == Int32)
				return ((static_cast<int>(atof(str))));
			else if (type == Float)
				return ((atof(str)));
			else if (type == Double)
				return ((strtod(str, NULL)));
		}
};

#endif