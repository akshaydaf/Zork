/*
 * Turnon.h
 *
 *  Created on: Dec 6, 2016
 *      Author: adaftard
 */

#ifndef TURNON_H_
#define TURNON_H_
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
class Turnon{
public:
	Turnon(xml_node<>*);
	~Turnon(){};
	std::string print;
	std::string action;
};
#endif /* TURNON_H_ */
