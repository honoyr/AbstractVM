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
#include <regex>

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

//	std::cmatch		result;

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
            {"assert", &AbstractVM::Assert},
            {"push", &AbstractVM::Push}
    };

    std::map<std::string, void (AbstractVM::*)()> fun_exe = {
            {"add", &AbstractVM::add},
            {"sub", &AbstractVM::sub}
    };
    std::smatch		result;

    std::regex 		arg("[ \t]*((push)|(assert))[ \t]+?((int8)|(int16)|(int32)|(float)|(double))[ \t]*?\\(([-]?[0-9]*.[0-9]*)\\)[ \t]*([;].*)?");
    std::regex 		fun("[\t ]*((exit)|(print)|(mod)|(div)|(mul)|(sub)|(add)|(dump)|(pop)|(sum)|(avr)|(sort)|(min)|(max))[\t ]*([;].*)?");
    std::regex		comm("[\t ]*([;].*)?");

    this->i++;
    if (regex_match(str, arg))
    {
//        std::cout   << result.operator[](2)
//                    << std::endl
//                    << "first"
//                    << result.str()
//                    << result.position()
//                    << std::endl
//                    << result.str(4)
//                    << std::endl
//                    << result.str(0)
//                    << std::endl
//                    << result.str(2)
//                    << std::endl
//                    << result.str(3)
//                    << std::endl
//                    << result.str(5)
//                    << std::endl
//                    << result.str(6)
//                    << std::endl
//                    << result.str(7)
//                    << std::endl
//                    << result.str(8)
//                    << std::endl;

        std::regex_search(str.begin(), str.end(), result, arg);
        (this->*arg_exe[result.str(1)])(result.str(10), getType(result.str(4)));
    }
    else if (regex_match(str, fun))
    {
        std::regex_search(str.begin(), str.end(), result, fun);
        (this->*fun_exe[result.str(1)])();
    }
    else if (regex_match(str, comm))
        NULL;
    else
        throw LexicalErrorExcept(std::to_string(this->i), str);

}

void	    AbstractVM::Push(std::string const & str, eOperandType type){
    v.push_back(factory.createOperand(type, str));
}

void	    AbstractVM::Assert(std::string const & str, eOperandType type){
    const IOperand     *assert;

    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    if(!(assert == factory.createOperand(type, str)))
        throw ErrorAssertExcept(std::to_string(this->i), v.back()->toString(), str);

}

void	    AbstractVM::add(void){
    if (v.size() < 2)
        throw LessThanTwoArgExcept(std::to_string(this->i));
    const IOperand *a = v.back();
    v.pop_back();
    const IOperand *b = v.back();
    v.pop_back();
    const IOperand *c = *a + *b;
    Push(c->toString(), c->getType());
    delete a;
    delete b;
    delete c;
}
void	    AbstractVM::sub(void){
    if (v.size() < 2)
        throw LessThanTwoArgExcept(std::to_string(this->i));
    const IOperand *a = v.back();
    v.pop_back();
    const IOperand *b = v.back();
    v.pop_back();
    const IOperand *c = *a - *b;
    Push(c->toString(), c->getType());
    delete a;
    delete b;
    delete c;
}

//EXEPTION______________________________________________________________________________
//
