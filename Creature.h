/*
 * Creature.h
 *
 *  Created on: Dec 6, 2016
 *      Author: adaftard
 */

#ifndef CREATURE_H_
#define CREATURE_H_
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

#include "Trigger.h"
#include "Attack.h"
using namespace std;
using namespace rapidxml;

class Creature{
public:
	Creature(xml_node<>*);
	~Creature(){};
	std::string name;
	std::string status;
	std::string description;
	vector<string> vulnerability;
	//string attack;
	vector<Trigger*> triggers;
	bool trigtrue;
	Attack* attack;
	bool attrue;
};
#endif /* CREATURE_H_ */
