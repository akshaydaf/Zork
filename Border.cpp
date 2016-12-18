/*
 * Border.cpp
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
#include "Border.h"

Border::Border(xml_node<> * node){
	for (xml_node<> * child = node->first_node(); child; child = child->next_sibling()){
		if (string(child->name()) == string("direction")){
			if (string(child->value()) == string("north")){
				this->direction = "n";
			}
			else if (string(child->value()) == string("east")){
				this->direction = "e";
			}
			else if (string(child->value()) == string("south")){
				this->direction = "s";
			}
			else if (string(child->value()) == string("west")){
				this->direction = "w";
			}
		}
		else if (string(child->name()) == string("name")){
			this->name = child->value();
		}
	}
}
