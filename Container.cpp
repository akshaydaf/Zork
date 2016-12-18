/*
 * Container.cpp
 *
 *  Created on: Dec 6, 2016
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
using namespace std;
#include "Item.h"
#include "Trigger.h"
#include "Container.h"

Container::Container(xml_node<> * node){
	this -> acceptparam = false;
	for (xml_node<> * child = node->first_node(); child; child = child->next_sibling()){
		if (string(child->name()) == string("name")){
			this->name = child->value();
		}
		else if (string(child->name()) == string("status")){
			this->status = child->value();
		}
		else if (string(child->name()) == string("description")){
			this->description = child->value();
		}
		else if (string(child->name()) == string("accept")){
			this->accept.push_back(child->value());
			this->acceptparam = true;
		}
		else if (string(child->name()) == string("item")){
			this->items.push_back(child->value());
		}
		else if (string(child->name()) == string("trigger")){
			Trigger *trig = new Trigger(child);
			this->triggers.push_back(trig);
		}
	}
}
