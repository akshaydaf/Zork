/*
 * Container.h
 *
 *  Created on: Dec 6, 2016
 *      Author: adaftard
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

#include "Trigger.h"
#include "Item.h"
using namespace std;
using namespace rapidxml;
class Container{
public:
	Container(xml_node<>*);
	~Container(){};
	std::string name;
	std::string status;
	std::string description;
	vector<string> accept;
	bool acceptparam;
	vector<string> items;
	vector<Trigger*> triggers;
};
#endif /* CONTAINER_H_ */
