/*
 * Trigger.hpp
 *
 *  Created on: Dec 5, 2016
 *      Author: adaftard
 */

#ifndef TRIGGER_HPP_
#define TRIGGER_HPP_
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "Condition.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;
class Trigger{
public:
	std::string type;
	std::string command;
	std::string print;
	vector<string> action;
	vector<Condition*> conditions;
	bool times; //number of times trigger was triggered
	bool commandexist;
	Trigger(xml_node<> * node);
	~Trigger(){};
};
#endif /* TRIGGER_HPP_ */
