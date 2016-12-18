/*
 * Border.h
 *
 *  Created on: Dec 6, 2016
 *      Author: adaftard
 */

#ifndef BORDER_H_
#define BORDER_H_
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
class Border{
public:
	Border(xml_node<>*);
	~Border(){};
	std::string direction;
	std::string name;
};

#endif /* BORDER_H_ */
