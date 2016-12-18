/*
 * Creature.cpp
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

#include "Trigger.h"
#include "Creature.h"
Creature::Creature(xml_node<> * node){
	this -> trigtrue = false;
	this -> attrue = false;
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
		else if (string(child->name()) == string("vulnerability")){
			this->vulnerability.push_back(child->value());
		}
		else if (string(child->name()) == string("attack")){
			Attack *att = new Attack(child);
			this->attack = att;
			this -> attrue = true;
		}
		else if (string(child->name()) == string("trigger")){
			Trigger *trig = new Trigger(child);
			this->triggers.push_back(trig);
			this -> trigtrue = true;
		}
	}
}

