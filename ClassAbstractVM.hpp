/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassAbstractVM.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:48:41 by dgonor            #+#    #+#             */
/*   Updated: 2018/11/29 19:48:45 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASSABSTRACTVM_HPP
#define CLASSABSTRACTVM_HPP

#include <algorithm>
#include <exception>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
#include <regex>
#include <stack>
#include <list>
#include "ClassIOperand.hpp"
#include "ClassFactory.hpp"

class AbstractVM {
	AbstractVM ();
	~AbstractVM();

public:
	IOperand	push(eOperandType type, std::string const & str);

	void 		valid_data(std::string const &str);

private:
	Factory							factory;
	std::vector<const IOperand *>	v;
	int 							i;
	bool 							exist_error;
	bool 							exist_exit;
	bool							esc;

};

#endif
