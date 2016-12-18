/*
 * Room.cpp
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

#include "Trigger.h"
#include "Border.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "Room.h"
using namespace std;
using namespace rapidxml;
Room::Room(xml_node<> * node){
	for (xml_node<> * child = node->first_node(); child; child = child->next_sibling()){
		if (string(child->name()) == string("name")){
			this->name = child->value();
		}
		else if (string(child->name()) == string("status")){
			this->status = child->value();
		}
		else if (string(child->name()) == string("type")){
			this->type = child->value();
		}
		else if (string(child->name()) == string("description")){
			this->description = child->value();
		}
		else if (string(child->name()) == string("border")){
			Border *bord = new Border(child);
			this->borders.push_back(bord);
		}
		else if (string(child->name()) == string("container")){
			this->containers.push_back(child->value());
		}
		else if (string(child->name()) == string("item")){
			this->items.push_back(child->value());
		}
		else if (string(child->name()) == string("creature")){
			this->creatures.push_back(child->value());
		}
		else if (string(child->name()) == string("trigger")){
			Trigger *trig = new Trigger(child);
			this->triggers.push_back(trig);
		}
	}
}
