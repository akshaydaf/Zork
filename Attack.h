/*
 * Attack.h
 *
 *  Created on: Dec 8, 2016
 *      Author: adaftard
 */

#ifndef ATTACK_H_
#define ATTACK_H_
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"

#include "Condition.h"
using namespace std;
using namespace rapidxml;

class Attack{
public:
	Attack(xml_node<>*);
	~Attack(){};
	vector<string> action;
	std::string print;
	bool printtrue;
	Condition* condition;
	bool conditionstat;
};

#endif /* ATTACK_H_ */
