/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:46:13 by dgonor            #+#    #+#             */
/*   Updated: 2018/11/29 19:46:14 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClassAbstractVM.hpp"
//#include "ClassFactory.hpp"
//#include "ClassIOperand.hpp"
#include "ClassOperand.hpp"
#include <fstream>

void	valid_if_exception(AbstractVM &vm, std::string str)
{
	try {
		vm.valid_data(str);
	}
	catch (std::exception &e){
		std::cout << e.what() << std::endl;
	}
}

void    management(AbstractVM &vm, std::string str)
{
    try {
        vm.data_management(str);
    }
    catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void	pars_stdin(std::string str, AbstractVM & vm)
{
	std::vector <std::string> v_str;

    vm.setIterLine();
    while(1)
	{
		std::getline(std::cin, str);
		(!std::cin) ? exit(0) : (void)NULL;
        if (str == ";;") {
            break;
        }
		v_str.push_back(str);
	}
	for(unsigned long i = 0; i < v_str.size(); i++)
		valid_if_exception(vm, v_str[i]);
	vm.setIterLine();
		try {
			if (!vm.getExist_error())
				for(unsigned long i = 0; i < v_str.size(); (i++ && !vm.getEsc()))
					management(vm, v_str[i]);
		}
		catch (std::exception &e){
			std::cout   << e.what() << std::endl;
		}
}

void	pars_stream(std::string &str, AbstractVM &vm, std::ifstream &ifstrm)
{
    vm.setIterLine();
	while(std::getline(ifstrm, str))
        valid_if_exception(vm, str);
	try {
		if (!vm.getExist_error())
		{
			ifstrm.clear(), ifstrm.seekg(0, ifstrm.beg);
			while (std::getline(ifstrm, str) && !vm.getEsc())
				management(vm, str);
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	ifstrm.close();
}

int     main(int ac, char** av)
{
	std::string str;
	AbstractVM	vm;

	std::ifstream	ifstrm(av[1]);
	if (ac == 1)
		pars_stdin(str, vm);
	else if (ac == 2){
        if (!ifstrm)
            std::cout << "Unreadable file"
                      << std::endl;
        else
		    pars_stream(str, vm, ifstrm);
	}
	else
		std::cout	<< "Usege: Add asembly commands or just put it in stdin"
					 << std::endl;
    return (0);
}