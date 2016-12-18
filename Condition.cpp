/*
 * Condition.cpp
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

using namespace rapidxml;
#include "Condition.h"
Condition::Condition(xml_node<> * node){
	this->has = "";
	this->object = "";
	this->owner = "";
	this->status = "";
	for (xml_node<> * child = node->first_node(); child; child = child->next_sibling()){
		if (string(child->name()) == string("has")){
			this->has = child->value();
		}
		else if (string(child->name()) == string("object")){
			this->object = child->value();
		}
		else if (string(child->name()) == string("owner")){
			this->owner = child->value();
		}
		else if (string(child->name()) == string("status")){
			this->status = child->value();
		}
	}
}
