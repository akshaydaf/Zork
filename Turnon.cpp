/*
 * Turnon.cpp
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
using namespace std;
using namespace rapidxml;
#include "Turnon.h"

Turnon::Turnon(xml_node<> * node){
	for (xml_node<> * child = node->first_node(); child; child = child->next_sibling()){
		if (string(child->name()) == string("print")){
			this->print = child->value();
		}
		else if (string(child->name()) == string("action")){
			this->action = child->value();
		}
	}
}
