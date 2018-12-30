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

        eOperandType    getType(std::string const &type);
		bool 		    getExist_error(void);
		bool 		    getExist_exit(void);
		bool 		    getEsc(void);

        void            setIterLine(void);
        void            setExit(void);

        void 		    valid_data(std::string const &str);
        void            data_management(std::string const &str);

        void            Push(std::string const & str, eOperandType type);
        void       	    Assert(std::string const & str, eOperandType type);
        void       	    Pop(void);
        void       	    Exit(void);

        void	        Add(void);
        void	        Sub(void);
        void	        Mul(void);
        void	        Div(void);
        void	        Mod(void);

        void	        Dump(void);
        void	        Print(void);
        void			Delim(void);

        void            Sum(void);
        void            Max(void);
        void            Min(void);
        void            Avrg(void);
        void            Asort(void);
        void            Dsort(void);

	class LexicalErrorExcept : public std::exception{
		public:
            LexicalErrorExcept(std::string nline, std::string str)
                    : _nline(nline), _str(str) {}
//           ~LexicalErrorExcept(){}
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

    class LessThanTwoArgExcept : public std::exception{
    public:
        LessThanTwoArgExcept(std::string nline) : _nline(nline) {}
        const char *what() const throw()
        {
            std::string error_exept("Error: Stack has less than 2 arguments - line " + _nline);
//            error_exept = (error_exept + _nline);
            return (error_exept.c_str());
        }
    private:
        std::string                 _nline;
    };

    class PrintExcept : public std::exception{
    public:
        PrintExcept(std::string nline, std::string str)
                : _nline(nline), _str(str) {}
        const char *what() const throw()
        {
            std::string error_exept("Error: Unprintable character - line "
                                    + _nline + " --> " + _str);
            return (error_exept.c_str());
        }
    private:
        std::string                 _nline;
        std::string	                _str;
    };

    class NoExistExitExcept : public std::exception{
    public:
        const char *what() const throw()
        {
            std::string error_exept("Error: The command 'exit' no found");
            return (error_exept.c_str());
        }
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
