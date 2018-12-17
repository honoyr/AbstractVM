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
#include <map>

AbstractVM::AbstractVM(void): i(0), exist_error(false), exist_exit(false), esc(false) {}
AbstractVM::AbstractVM(AbstractVM const &copy){
	if (this != &copy)
		*this = copy;
}
AbstractVM&		AbstractVM::operator=(AbstractVM const &vm){
    exist_error = getExist_error();
    exist_exit  = getExist_exit();
    esc = getEsc();
	return *this;}
AbstractVM::~AbstractVM(void){}

eOperandType        AbstractVM::getType(std::string const &type) {
    std::map<std::string, eOperandType > types = {
            {"int8", Int8},
            {"int16", Int16},
            {"int32", Int32},
            {"float", Float},
            {"double", Double}
    };
    return (types[type]);
}
bool 		AbstractVM::getExist_error(void){return this->exist_error;}
bool 		AbstractVM::getExist_exit(void){return this->exist_exit;}
bool 		AbstractVM::getEsc(void){ return this->esc;}

void 		AbstractVM::valid_data(std::string const &str){

	std::cmatch		result;

	std::regex 		arg("[ \t]*((push)|(assert))[ \t]+?((int8)|(int16)|(int32)|(float)|(double))[ \t]*?\\(([-]?[0-9]*.[0-9]*)\\)[ \t]*([;].*)?");
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

void 		AbstractVM::add_data(std::string const &str){

    std::map<std::string, void (AbstractVM::*)(std::string const &str, eOperandType type)> arg_exe ={
            {"assert", &AbstractVM::assert},
            {"push", &AbstractVM::push}
    };

    std::map<std::string, void (AbstractVM::*)(std::string const &str, eOperandType type)> fun_exe = {
            {"add", &AbstractVM::add},
            {"sub", &AbstractVM::sub}
    };
    std::cmatch		result;

    std::regex 		arg("[ \t]*((push)|(assert))[ \t]+?((int8)|(int16)|(int32)|(float)|(double))[ \t]*?\\(([-]?[0-9]*.[0-9]*)\\)[ \t]*([;].*)?");
    std::regex 		fun("[\t ]*((exit)|(print)|(mod)|(div)|(mul)|(sub)|(add)|(dump)|(pop)|(sum)|(avr)|(sort)|(min)|(max))[\t ]*([;].*)?");
    std::regex		comm("[\t ]*([;].*)?");

    this->i++;
    if (regex_match(str, arg))
    {
        std::regex_search(str.begin(), str.end(), result, arg);
        (this->*arg_exe[result.str(1)])(getType(result.str(4)), result.str(10));
    }

}

//EXEPTION______________________________________________________________________________
//
