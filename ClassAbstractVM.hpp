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
#include "ClassOperand.hpp"

class AbstractVM {
    public:
        AbstractVM(void);
        AbstractVM(AbstractVM const &vm);
        AbstractVM &operator=(AbstractVM const &vm);
        ~AbstractVM(void);

//		Factory		    getFactory(void);
        eOperandType    getType(std::string const &type);
		bool 		    getExist_error(void);
		bool 		    getExist_exit(void);
		bool 		    getEsc(void);

        void 		    valid_data(std::string const &str);
        void            add_data(std::string const &str);

        void            Push(std::string const & str, eOperandType type);
        void       	    Assert(std::string const & str, eOperandType type);

        void	        add(void);
        void	        sub(void);


	class LexicalErrorExcept : public std::exception{
		public:
            LexicalErrorExcept();
            LexicalErrorExcept(std::string nline, std::string str)
                    : _nline(nline), _str(str) {}
            const char *what() const throw()
            {
                std::string error_exept("Error: Lexical - line ");
                error_exept = (error_exept + _nline + " --> " + _str);
                return (error_exept.c_str());
            }
		private:
			std::string                 _nline;
			std::string	                _str;
	};

	class DoubExitExcept : public std::exception{
		public:
			DoubExitExcept();
			DoubExitExcept(std::string nline) : _nline(nline) {}
			const char *what() const throw()
			{
				std::string error_exept("Error: Double exit - line ");
				error_exept = (error_exept + _nline);
				return (error_exept.c_str());
			}
		private:
			std::string                 _nline;
	};

    class EmptyStackExcept : public std::exception{
    public:
        EmptyStackExcept();
        EmptyStackExcept(std::string nline) : _nline(nline) {}
        const char *what() const throw()
        {
            std::string error_exept("Error: Stack is empty - line " + _nline);
//            error_exept = (error_exept + _nline);
            return (error_exept.c_str());
        }
    private:
        std::string                 _nline;
    };

    class ErrorAssertExcept : public std::exception{
    public:
        ErrorAssertExcept();
        ErrorAssertExcept(std::string nline, std::string assert_s, std::string stack_s)
                : _nline(nline), _assert_s(assert_s), _stack_s(stack_s) {}
        const char *what() const throw()
        {
            std::string error_exept("Error: Assertion is fail --> "
                                    + _assert_s + " != " + _stack_s);
            return (error_exept.c_str());
        }
    private:
        std::string                 _nline;
        std::string                 _assert_s;
        std::string                 _stack_s;
    };

    private:
        Factory							factory;
        std::vector<const IOperand *>	v;
        int 							i;
        bool 							exist_error;
        bool 							exist_exit;
        bool							esc;

};

#endif
