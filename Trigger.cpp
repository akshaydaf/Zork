/*
 * Trigger.cpp
 *
 *  Created on: Dec 5, 2016
 *      Author: adaftard
 */
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

//header files
#include "Condition.h"
#include "Trigger.h"

Trigger::Trigger(xml_node<> * node){
	this->times = false;
	this->commandexist = false;
	this->type = "single";
	for (xml_node<> * child = node->first_node(); child; child = child->next_sibling()){
		if (string(child->name()) == string("type")){
			this->type = child->value();
		}
		else if(string(child->name()) == string("command")){
			this->command = child->value();
			this -> commandexist = true;
		}
		else if(string(child->name()) == string("print")){
			this->print = child->value();
		}
		else if(string(child->name()) == string("action")){
			this->action.push_back(child->value());
		}
		else if(string(child->name()) == string("condition")){
			Condition *cond = new Condition(child);
			this->conditions.push_back(cond);
		}
	}
}
