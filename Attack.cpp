/*
 * Attack.cpp
 *
 *  Created on: Dec 9, 2016
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

#include "Condition.h"
#include "Attack.h"
using namespace std;
using namespace rapidxml;

Attack::Attack(xml_node<> * node){
	this->conditionstat = false;
	this->printtrue = false;
	for (xml_node<> * child = node->first_node(); child; child = child->next_sibling()){
		if (string(child->name()) == string("action")){
			this->action.push_back(child->value());
		}
		else if (string(child->name()) == string("print")){
			this->print = child->value();
			this->printtrue = true;
		}
		else if (string(child->name()) == string("condition")){
			Condition *cond = new Condition(child);
			this->condition = cond;
			this->conditionstat = true;
		}
	}
}
