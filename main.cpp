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
#include "ClassFactory.hpp"
#include "ClassIOperand.hpp"
#include "ClassOperand.hpp"



void    push_comm(std::string str)
{

}

void    pars_command(std::string str)
{
    if (str.find("push"))
        push_comm(str);
    else if (str.find("pop"))
        pop_comm(str);
    else if (str.find("dump"))
        dump_comm(str);
    else if (str.find("assert"))
        assert_comm(str);
    else if (str.find("add"))
        add_comm(str);
    else if (str.find("sub"))
        sub_comm(str);
    else if (str.find("mul"))
        mul_comm(str);
    else if (str.find("div"))
        div_comm(str);
    else if (str.find("mod"))
        mod_comm(str);
    else if (str.find("print"))
        print_comm(str);
    else if (str.find("exit"))
        exit_comm(str);
    else
        error(str);
}

int     main(int ac, char** av)
{
    int 		i;
	std::string str;
	std::vector <std::string> v_str;
	AbstractVM	vm;

	i = 0;
	std::ifstream	ifstr(av[1]);

	if (ac == 2){
		while(std::getline(std::cin, str))
		{
			pars_command(str);
		}
	}
	else if (ac == 1){

		while(1)
		{
			std::cout << i++ << ". ";
			std::cin >> str;
			if (str == ";;")
				break;
			v_str.push_back(str);
		}
	}
	else
	{
		std::cout	<< "Usege: Add asembly commands or just put it in stdin"
					 << std::endl;
	}

    return (0);
}