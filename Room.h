/*
 * Room.hpp
 *
 *  Created on: Dec 4, 2016
 *      Author: adaftard
 */

#ifndef ROOM_HPP_
#define ROOM_HPP_
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

using namespace std;
using namespace rapidxml;

class Room{
public:
	Room(xml_node<>*);
	~Room(){};
	std::string name;
	std::string status;
	std::string type;
	std::string description;
	vector<Border*> borders;
	vector<string> containers;
	vector<string> items;
	vector<string> creatures;
	vector<Trigger*> triggers;
};

#endif /* ROOM_HPP_ */
