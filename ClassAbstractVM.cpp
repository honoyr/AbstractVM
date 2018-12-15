/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassAbstractVM.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:48:41 by dgonor            #+#    #+#             */
/*   Updated: 2018/11/29 19:48:45 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassAbstractVM.hpp"

AbstractVM::AbstractVM(void): {}
AbstractVM::AbstractVM(AbstractVM const &copy){
	factory = copy.factory;
	v = copy.v;
	i = copy.i;
	exist_error = copy.exist_error;
	exist_exit = copy.exist_exit;
	esc = copy.esc;
	return *this;
}
AbstractVM&		AbstractVM &operator=(AbstractVM const &vm){return *this;}
AbstractVM::~AbstractVM(void){}

void 		AbstractVM::valid_data(std::string const &str){

	std::cmatch		result;

	std::regex 		arg("([\t ]*(push)(assert))[\t ]+?((int[8|16|32])|(Float)|(Double))[\t ]*?\\((([-]?[0-9]*.[0-9]*)))\\)[\t ]*([;].*)?");
	std::regex 		fun("[\t ]*((exit)|(print)|(mod)|(div)|(mul)|(sub)|(add)|(dump)|(pop)|(sum)|(avr)|(sort)|(min)|(max))[\t ]*([;].*)?");
	std::regex		comm("[\t ]*([;].*)?");

	this->i++;

    if (!regex_match(str, arg) && !regex_match(str, fun) && !regex_match(str, comm)){
        exist_error = true;
        throw LexicalErrorExcept(std::to_string(this->i), str);
    }
    else if (regex_match(str, fun) && str.find("exit") != std::string::npos){
        if (exist_exit)
        {
            exist_error = true;
            throw DoubExitExcept(std::to_string(this->i));
        }
        exist_exit = true;
    }

}



//EXEPTION______________________________________________________________________________
//
