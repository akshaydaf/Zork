/*
 * Condition.hpp
 *
 *  Created on: Dec 5, 2016
 *      Author: adaftard
 */

#ifndef CONDITION_HPP_
#define CONDITION_HPP_
#include <string>
#include <stdio>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"

using namespace std;
using namespace rapidxml;
class Condition{
public:
	Condition(xml_node<>*);
	~Condition(){};
	std::string has;
	std::string object;
	std::string owner;
	std::string status;
};

#endif /* CONDITION_HPP_ */
