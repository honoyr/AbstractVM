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
	return *this;
}

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

bool 		AbstractVM::getExist_error(void){
    if (!this->exist_exit)
        throw NoExistExitExcept();
    return this->exist_error;
}

bool 		AbstractVM::getExist_exit(void)     {return this->exist_exit;}
bool 		AbstractVM::getEsc(void)            {return this->esc;}

void        AbstractVM::setIterLine()           {this->i = 0;}
void        AbstractVM::setExit()               {this->esc = true;}

void 		AbstractVM::valid_data(std::string const &str){
	std::regex 		arg("[ \t]*((push)|(assert))[ \t]+?((int8)|(int16)|(int32)|(float)|(double))[ \t]*?\\(([-]?[0-9]*.[0-9]*)\\)[ \t]*([;].*)?");
	std::regex 		fun("[\t ]*((exit)|(print)|(delim)|(mod)|(div)|(mul)|(sub)|(add)|(dump)|(pop)|(sum)|(avrg)|(asort)|(dsort)|(min)|(max))[\t ]*([;].*)?");
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

void 		AbstractVM::data_management(std::string const &str){

    std::map<std::string, void (AbstractVM::*)(std::string const &str, eOperandType type)> arg_exe ={
            {"assert", &AbstractVM::Assert},
            {"push", &AbstractVM::Push},
    };

    std::map<std::string, void (AbstractVM::*)()> fun_exe = {
            {"add", &AbstractVM::Add},
            {"sub", &AbstractVM::Sub},
            {"mul", &AbstractVM::Mul},
            {"div", &AbstractVM::Div},
            {"mod", &AbstractVM::Mod},
            {"dump", &AbstractVM::Dump},
            {"print", &AbstractVM::Print},
            {"delim", &AbstractVM::Delim},
            {"sum", &AbstractVM::Sum},
            {"max", &AbstractVM::Max},
            {"min", &AbstractVM::Min},
            {"avrg", &AbstractVM::Avrg},
            {"asort", &AbstractVM::Asort},
            {"dsort", &AbstractVM::Dsort},
            {"pop", &AbstractVM::Pop},
            {"exit", &AbstractVM::Exit}
    };

    std::smatch		result;
    std::regex 		arg("[ \t]*((push)|(assert))[ \t]+?((int8)|(int16)|(int32)|(float)|(double))[ \t]*?\\(([-]?[0-9]*.[0-9]*)\\)[ \t]*([;].*)?");
    std::regex 		fun("[\t ]*((exit)|(print)|(delim)|(mod)|(div)|(mul)|(sub)|(add)|(dump)|(pop)|(sum)|(avrg)|(asort)|(dsort)|(min)|(max))[\t ]*([;].*)?");
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
    v.push_back(factory.createOperand(type, str)); }

void	    AbstractVM::Assert(std::string const & str, eOperandType type){
    const IOperand     *assert;

	assert = factory.createOperand(type, str);
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    if(!(*v.back() == *assert))
        throw ErrorAssertExcept(std::to_string(this->i), v.back()->toString(), str);
}

void         AbstractVM::Exit(void){ esc = true; }

void	    AbstractVM::Pop(void){
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    else
        v.pop_back();
}

void	    AbstractVM::Add(void){
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
void	    AbstractVM::Sub(void){
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

void	    AbstractVM::Mul(void){
    if (v.size() < 2)
        throw LessThanTwoArgExcept(std::to_string(this->i));
    const IOperand *a = v.back();
    v.pop_back();
    const IOperand *b = v.back();
    v.pop_back();
    const IOperand *c = *a * *b;
    Push(c->toString(), c->getType());
    delete a;
    delete b;
    delete c;
}


void	    AbstractVM::Div(void){
    if (v.size() < 2)
        throw LessThanTwoArgExcept(std::to_string(this->i));
    const IOperand *a = v.back();
    v.pop_back();
    const IOperand *b = v.back();
    v.pop_back();
    const IOperand *c = *a / *b;
    Push(c->toString(), c->getType());
    delete a;
    delete b;
    delete c;
}

void	    AbstractVM::Mod(void){
    if (v.size() < 2)
        throw LessThanTwoArgExcept(std::to_string(this->i));
    const IOperand *a = v.back();
    v.pop_back();
    const IOperand *b = v.back();
    v.pop_back();
    const IOperand *c = *a % *b;
    Push(c->toString(), c->getType());
    delete a;
    delete b;
    delete c;
}

void	    AbstractVM::Dump(void){
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    else
		for(int i = v.size() - 1 ; i >= 0; i--)
			v[i]->getPrint();
}

void	    AbstractVM::Print(void){
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    else
    {
        if (v.back()->getType() != Int8)
            throw PrintExcept(v.back()->toString(), std::to_string(this->i));
        std::cout   << static_cast<char>(std::stoi(v.back()->toString()));
    }
}

void	    AbstractVM::Delim(void){
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    else
        std::cout  << "__________________"
                   << std::endl;
}

void	    AbstractVM::Sum(void){
    if (v.size() < 2)
        throw LessThanTwoArgExcept(std::to_string(this->i));
    const IOperand *a = factory.createOperand(Int32, std::to_string(0));

    for(int i = 0; i < v.size(); i++)
        a = *a + *(v[i]);
	std::cout << "SUMM ";
	a->getPrint();
//    delete a;
}

void	    AbstractVM::Max(void){
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    else
    {
        const IOperand *a = factory.createOperand(Int32, std::to_string(INT32_MIN));

        for(int i = 0; i < v.size(); i++)
            if (*(v[i]) > *a)
                a = (v[i]);
		std::cout << "MAX ";
		a->getPrint();
//        delete a;
    }
}

void	    AbstractVM::Min(void){
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    else
	{
        const IOperand *a = factory.createOperand(Int32, std::to_string(INT32_MAX));

        for (int i = 0; i < v.size(); i++)
            if (*(v[i]) < *a)
				a = (v[i]);
		std::cout << "MIN ";
        a->getPrint();
//        delete a;
    }
}

void	    AbstractVM::Avrg(void){
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    else {
        const IOperand *a = factory.createOperand(Int32, std::to_string(0));

        for (int i = 0; i < v.size(); i++)
            a = *a + *(v[i]);

//		const IOperand *b = ;
        a = *a / *(factory.createOperand(a->getType(), std::to_string(v.size())));
		std::cout << "AVRG ";
		a->getPrint();
//        delete a;
    }
}

void	    AbstractVM::Asort(void){
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    else {
        const IOperand *tmp;

        for (int i = 0; i < v.size(); i++)
            for (int j = 0; j < v.size(); j++)
            {
                if (i != j && *(v[i]) > *(v[j]))
                {
                    tmp = v[i];
                    v[i] = v[j];
                    v[j] = tmp;

                }
            }
//        delete tmp;
    }
}

void	    AbstractVM::Dsort(void){
    if (v.empty())
        throw EmptyStackExcept(std::to_string(this->i));
    else {
        const IOperand *tmp;

        for (int i = 0; i < v.size(); i++)
            for (int j = 0; j < v.size(); j++)
            {
                if (i != j && *(v[i]) < *(v[j]))
                {
                    tmp = v[i];
                    v[i] = v[j];
                    v[j] = tmp;

                }
            }
//        delete tmp;
    }
}

//EXEPTION______________________________________________________________________________
//
