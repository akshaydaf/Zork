/*
 * Item.h
 *
 *  Created on: Dec 6, 2016
 *      Author: adaftard
 */

#ifndef ITEM_H_
#define ITEM_H_
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

#include "Trigger.h"
#include "Turnon.h"
using namespace std;
using namespace rapidxml;

class Item{
public:
	Item(xml_node<>*);
	~Item(){};
	std::string name;
	std::string status;
	std::string description;
	std::string writing;
	vector<Turnon*> turnons;
	bool pickup;
	vector<Trigger*> triggers;
};

#endif /* ITEM_H_ */
