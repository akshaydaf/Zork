#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include <algorithm>
#include <iterator>
#include <sstream>
using namespace rapidxml;
using namespace std;
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "Room.h"
#include <typeinfo>
vector<Room*> rooms;
vector<Creature*> creatures;
vector<Item*> items;
vector<Container*> containers;
vector<string> inventory;
Room* currentroom;
bool ex;
void checkInput(string);
void changeroom(string);
void inven(string);
void victory();
void gg();
void takeitem(string);
void dropitem(string);
void readitem(string);
void opencont(string);
void putitem(string);
void turnon(string);
void attackcreat(string);
void executeaction(string);
void actionupdate(string);
void actionadd(string);
void actiondel(string);
bool checktrigger(string);
void checktrigger_withoutcommand();
bool checkcond(string, string, string, string);
int main(int argc, char* argv[])
{
	file<> xmlFile("samples/triggersample.xml");
	cout << "You can't turn back now..." << endl;
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	xml_node<> * root_node = doc.first_node();

	for (xml_node<> * child = root_node->first_node(); child; child = child->next_sibling()){
		if (string(child->name()) == string("room")){
			Room* room = new Room(child);
			rooms.push_back(room);
		}
		else if (string(child->name()) == string("item")){
			Item* it = new Item(child);
			items.push_back(it);
		}
		else if (string(child->name()) == string("container")){
			Container* cont = new Container(child);
			containers.push_back(cont);
		}
		else if (string(child->name()) == string("creature")){
			Creature* creat = new Creature(child);
			creatures.push_back(creat);
		}
	}
	string userinput;
	currentroom = rooms[0];
	cout << currentroom -> description << endl;
	while (ex != true){
		//User functions
		getline(cin,userinput);
		if (!checktrigger(userinput)){
			if (ex == true){
				break;
			}
			checkInput(userinput);
		}
	}

}

//checks all of the userinputs
void checkInput(string userinput){
	if (userinput == "n" || userinput == "e" || userinput == "s" || userinput == "w"){
		changeroom(userinput);
	}
	else if (userinput == "i"){
		inven(userinput);
	}
	else if (userinput == "open exit" && currentroom -> type == "exit"){
		victory();
	}
	else if (userinput.substr(0,4) == "take"){
		takeitem(userinput);
	}
	else if (userinput.substr(0,4) == "drop"){
		dropitem(userinput);
	}
	else if(userinput.substr(0,4) == "read"){
		readitem(userinput);
	}
	else if(userinput.substr(0,4) == "open"){
		opencont(userinput);
	}
	else if(userinput.substr(0,3) == "put"){
		putitem(userinput);
	}
	else if (userinput.substr(0,7) == "turn on"){
		turnon(userinput);
	}
	else if (userinput.substr(0,6) == "attack"){
		attackcreat(userinput);
	}
	else {
		cout << "Error." << endl;
	}
}

//checks conditions to exit current room
void changeroom(string userinput){
	string currname = currentroom -> name;
	string savename = currentroom -> name;
	vector<Border*>temp = currentroom -> borders;
	if (temp.size() != 0){
		for(unsigned int i=0; i < temp.size(); i++){
			if (string(userinput) == string(temp[i]->direction)){
				savename = temp[i] -> name;
			}
		}
		for (unsigned int i=0; i < rooms.size(); i++){
			if (string(savename) == string(rooms[i]->name)){
				currentroom = rooms[i];
			}
		}
		if (currname == savename){
			cout << "Can't go that way." << endl;
		}
		else{
			cout << currentroom -> description << endl;
		}
	}
}

void inven(string userinput){
	int count = 0;
	if (inventory.size() == 0){
		cout << "Inventory: empty" << endl;
	}
	else{
		cout << "Inventory: ";
		for(unsigned int i=0; i < inventory.size(); i++){
			cout << inventory[i];
			if (count < inventory.size() - 1){
				cout << ", ";
			}
			count += 1;
		}
		cout << endl;
	}
}


void victory(){
	cout << "Game Over" << endl;
	ex = true;
}

void takeitem(string userinput){
	string item = userinput.erase(0,5);
	vector <string> tempitems = currentroom -> items;
	vector <string> tempconts = currentroom -> containers;
	bool t = false;
	for(unsigned int i=0; i < tempitems.size(); i++){
		if (tempitems[i] == item){
			inventory.push_back(tempitems[i]);
			currentroom->items.erase(currentroom->items.begin() + i);
			cout << "Item " + item + " added to inventory" << endl;
			t = true;
		}
	}
	for (unsigned int i=0; i < tempconts.size(); i++){
		for (unsigned int j=0; j < containers.size(); j++){
				for (unsigned int k=0; k < containers[j] -> items.size(); k++){
						for (unsigned int l=0; l < items.size(); l++){
							if (containers[j] -> items[k] == item && items[l] -> name == item && items[l] -> pickup){
								inventory.push_back(item);
								string remstr = tempconts[i];
								containers[j] -> items.erase(containers[j] -> items.begin() + k);
								cout << "Item " + item + " added to inventory" << endl;
								t = true;
							}
						}
				}
		}
	}
	if (!t){
		cout << "Error" << endl;
	}
}

void dropitem(string userinput){
	string item = userinput.erase(0,5);
	bool t = false;
	for(unsigned int i=0; i < inventory.size(); i++){
		if (item == inventory[i]){
			inventory.erase(inventory.begin() + i);
			currentroom->items.push_back(item);
			cout << item + " dropped." << endl;
			t = true;
		}
	}
	if (!t){
		cout << "Error" << endl;
	}
}

void readitem(string userinput){
	string item = userinput.erase(0,5);
	bool t = false;
	for(unsigned int i=0; i < inventory.size(); i++){
		if (item == inventory[i]){
			t = true;
			for (unsigned int j = 0; j < items.size(); j++){
				if (items[j] -> name == item){
					if (items[j] -> writing != ""){
						cout << items[j] -> writing << endl;
					}
					else{
						cout << "Nothing Written" << endl;
					}
				}
			}
		}
	}
	if (!t){
		cout << "Error" << endl;
	}
}

void opencont(string userinput){
	string contname = userinput.erase(0,5);
	unsigned int count;
	bool t = false;
	vector <string> tempconts = currentroom -> containers;
	for (unsigned int k=0; k < tempconts.size(); k++){
		for (unsigned int i=0; i < containers.size(); i++){
			if (contname == containers[i] -> name and contname == tempconts[k]){
				t = true;
				if (containers[i] -> items.size() > 0){
					cout << contname + " contains ";
					for (unsigned int j = 0; j < containers[i] -> items.size(); j++){
						cout << containers[i] -> items[j];
						for (unsigned int l = 0; l < items.size(); l++){
							if (containers[i] -> items[j] == items[l] -> name){
								items[l] -> pickup = true;
							}
						}
						if (count < containers[i] -> items.size() - 1){
							cout << ", ";
						}
						count += 1;
					}
					cout << endl;
				}
				else{
					cout << contname + " is empty." << endl;
				}
			}
		}
	}
	if (!t){
		cout << "Error" << endl;
	}
}

void putitem(string userinput){
	istringstream iss(userinput);
	vector<string> arguments;
	copy (istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(arguments));
	if (arguments.size() != 4){
		cout << "Error" << endl;
		return;
	}
	string item = arguments[1];
	string cont = arguments[3];
	bool itemt = false;
	bool contt = false;
	bool tof = false;
	vector <string> tempconts = currentroom -> containers;
	for (unsigned int i = 0; i < containers.size(); i++){
		for (unsigned int j = 0; j < containers[i]->accept.size(); j++){
			if (containers[i]->accept[j] == item){
				tof = true;
			}
		}
	}
	for (unsigned int i = 0; i < tempconts.size(); i++){
		for (unsigned int j = 0; j < containers.size(); j++){
			if (cont == containers[j]->name && cont == tempconts[i]){
				contt = true;
				for (unsigned int k = 0; k < inventory.size(); k++){
					if (inventory[k] == item){
						itemt = true;
						if (containers[j]->acceptparam){
							if (tof){
								for (unsigned int l = 0; l < items.size(); l++){
									if (item == items[l] -> name){
										items[l] -> pickup = true;
									}
								}
								containers[j] ->items.push_back(item);
								inventory.erase(inventory.begin() + k);
								cout << "Item " + item + " added to " + cont << endl;
								bool success = checktrigger(userinput);
							}
							else{
								cout << cont + " cannot accept item." << endl;
							}
						}
						else{
							for (unsigned int l = 0; l < items.size(); l++){
								if (item == items[l] -> name){
									items[l] -> pickup = true;
								}
							}
							containers[j] ->items.push_back(item);
							inventory.erase(inventory.begin() + k);
							cout << "Item " + item + " added to " + cont << endl;
							bool success = checktrigger(userinput);
						}
					}
				}
			}
		}
	}
	if (!contt){
		cout << "Error" << endl;
	}
	else if (!itemt){
		cout << "Error" << endl;
	}
}

void turnon(string userinput){
	//minor bug with turning on torch
	istringstream iss(userinput);
	vector<string> arguments;
	copy (istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(arguments));
	string item = arguments[2];
	bool t = false;
	for (unsigned int i = 0; i < inventory.size(); i++){
		for (unsigned int j = 0; j < items.size(); j++){
			if (items[j] -> name == item && inventory[i] == item){
				t = true;
				if (items[j] -> turnons.size() > 0){
					for (unsigned int k = 0; k < items[j] -> turnons.size(); k++){
						// one problem here, function turns on and then also prints this crap afterword WHEN WILL THE MADNESS STOP
						cout << "You activate the " + item + "."<< endl;
						cout << items[j] -> turnons[k] -> print << endl;
						executeaction(items[j] -> turnons[k] -> action);
					}
				}
				else{
					cout << "Cannot turn on item!" << endl;
				}
			}
		}
	}
	if (!t){
		cout << "Error" <<endl;
	}
}

void attackcreat(string userinput){
	istringstream iss(userinput);
	vector<string> arguments;
	copy (istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(arguments));
	if (arguments.size() != 4){
		cout << "Error" << endl;
		return;
	}
	string creature = arguments[1];
	string item = arguments[3];
	bool tof = false;
	bool trigger = false;
	vector <string> tempcreats = currentroom -> creatures;
	for (unsigned int i = 0; i < tempcreats.size(); i++){
		for (unsigned int j = 0; j < creatures.size(); j++){
			for (unsigned int l = 0; l < inventory.size(); l++){
				for (unsigned int m = 0; m < creatures[j] -> vulnerability.size(); m++)
					if (tempcreats[i] == creature && creatures[j] -> name == creature && inventory[l] == item && item == creatures[j] -> vulnerability[m]){
						if (creatures[j] -> attrue){
							if (creatures[j] -> attack -> conditionstat != false ){ //!creatures[j] -> trigtrue &&
								string obj = creatures[j] -> attack -> condition -> object;
								string owner = creatures[j] -> attack -> condition -> owner;
								string status = creatures[j] -> attack -> condition -> status;
								string has = creatures[j] -> attack -> condition -> has;
								trigger = checkcond(obj, owner, has, status);
								if (trigger){ //&& inventory[l] == creatures[j] -> vulnerability[m]){
									tof = true;
									cout << "You assault the " + creatures[j] -> name + " with the " + item + "." << endl;
									if (creatures[j] -> attack -> printtrue)
										cout << creatures[j] -> attack -> print << endl;
									for (unsigned int n = 0; n < creatures[j] -> attack -> action.size(); n++){
										executeaction(creatures[j] -> attack -> action[n]);
									}
								}
							}
							else if (item == creatures[j] -> vulnerability[m]){
								tof = true;
								cout << "You assault the " + creatures[j] -> name + " with the " + item + "." << endl;
								cout << creatures[j] -> attack -> print << endl;
								for (unsigned int n = 0; n < creatures[j] -> attack -> action.size(); n++){
									executeaction(creatures[j] -> attack -> action[n]);
								}
							}
						}
						else{
							tof = true;
							cout << "You assault the " + creatures[j] -> name + " with the " + item + "." << endl;
						}
					}
			}
		}
	}
	if (!tof){
		cout << "Error" << endl;
	}
}
void executeaction(string action){
	if (action.substr(0,6) == "Update"){
		actionupdate(action);
	}
	else if (action.substr(0,3) == "Add"){
		actionadd(action);
	}
	else if (action.substr(0,6) == "Delete"){
		actiondel(action);
	}
	else if (action == "Game Over"){
		gg();
	}
	else {
		checkInput(action);
	}
	bool success = checktrigger("");
}
void gg(){
	cout << "Victory!" << endl;
	ex = true;
}
void actionupdate(string action){
	istringstream iss(action);
	vector<string> arguments;
	copy (istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(arguments));
	string item = arguments[1];
	string newstatus = arguments[3];
	for (unsigned int i = 0; i < items.size(); i++){
		if (items[i] -> name == item){
			if (items[i] -> status != newstatus){
				//cout << items[i]->status + ", " + newstatus << endl;
				items[i] -> status = newstatus;
			}
		}
	}
	for (unsigned int i = 0; i < containers.size(); i++){
		if (containers[i] -> name == item){
			if (containers[i] -> status != newstatus){
				//cout << containers[i]->status + ", " + newstatus << endl;
				containers[i] -> status = newstatus;
			}
		}
	}
	for (unsigned int i = 0; i < creatures.size(); i++){
		if (creatures[i] -> name == item){
			if (creatures[i] -> status != newstatus){
				//cout << creatures[i]->status + ", " + newstatus << endl;
				creatures[i] -> status = newstatus;
			}
		}
	}
	for (unsigned int i = 0; i < rooms.size(); i++){
		if (rooms[i] -> name == item){
			if (rooms[i] -> status != newstatus){
				//cout << rooms[i]->status + ", " + newstatus << endl;
				rooms[i] -> status = newstatus;
			}
		}
	}
}

void actionadd(string action){
	istringstream iss(action);
	vector<string> arguments;
	copy (istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(arguments));
	string item = arguments[1];
	string roomcont = arguments[3];
	//add item to room
	for (unsigned int i = 0; i < rooms.size(); i++){
		for (unsigned int j = 0; j < items.size(); j++){
			if (rooms[i] -> name == roomcont && item == items[j] -> name){
				rooms[i]->items.push_back(item);
			}
		}
	}
	//add creature to room
	for (unsigned int i = 0; i < rooms.size(); i++){
		for (unsigned int j = 0; j < creatures.size(); j++){
			if (rooms[i] -> name == roomcont && item == creatures[j] -> name){
				rooms[i]->creatures.push_back(item);
			}
		}
	}
	//add container to room
	for (unsigned int i = 0; i < rooms.size(); i++){
		for (unsigned int j = 0; j < containers.size(); j++){
			if (rooms[i] -> name == roomcont && item == containers[j] -> name){
				rooms[i]->containers.push_back(item);
			}
		}
	}

	//add item to container
	for (unsigned int i = 0; i < containers.size(); i++){
		for (unsigned int j = 0; j < items.size(); j++){
			if (containers[i] -> name == roomcont && item == items[j] -> name){
				containers[i]->items.push_back(item);
			}
		}
	}
}

void actiondel(string action){
	istringstream iss(action);
	vector<string> arguments;
	copy (istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(arguments));
	string obj = arguments[1];
	//erase container
	for (unsigned int i = 0; i < rooms.size(); i++){
		for (unsigned int j = 0; j < rooms[i] -> containers.size(); j++){
			if (rooms[i] -> containers[j] == obj){
				rooms[i] -> containers.erase(rooms[i] -> containers.begin() + j);
			}
		}
	}
	//erase item
	for (unsigned int i = 0; i < rooms.size(); i++){
		for (unsigned int j = 0; j < rooms[i] -> items.size(); j++){
			if (rooms[i] -> items[j] == obj){
				rooms[i] -> items.erase(rooms[i] -> items.begin() + j);
			}
		}
	}
	//erase creature
	for (unsigned int i = 0; i < rooms.size(); i++){
		for (unsigned int j = 0; j < rooms[i] -> creatures.size(); j++){
			if (rooms[i] -> creatures[j] == obj){
				rooms[i] -> creatures.erase(rooms[i] -> creatures.begin() + j);
			}
		}
	}
	//erase room border, essentially deleting a room
	for (unsigned int i = 0; i < rooms.size(); i++){
		for (unsigned int j = 0; j < rooms[i] -> borders.size(); j++){
			if (rooms[i] -> borders[j] -> name == obj){
				rooms[i] -> borders.erase(rooms[i] -> borders.begin() + j);
			}
		}
	}
}
bool checkcond(string object, string owner, string has, string status){
	bool tof;
	if (has == "no"){
		tof = false;
	}
	else if (has == "yes"){
		tof = true;
	}
	bool trig = false;
	if (owner != ""){
		if (owner == "inventory"){
			for (unsigned int i = 0; i < inventory.size(); i++){
				if (object == inventory[i]){
					trig = true;
					if (tof){
						return (true); //true if you want to trigger, else false
					}
					else{
						return (false);
					}
				}
			}
			if (!trig){ //knows if object is in inventory
				if (!tof){
					return (true);
				}
				else{
					return (false);
				}
			}
		}
		else{
			for (unsigned int i = 0; i < containers.size(); i++){
				for (unsigned int j = 0; j < containers[i]-> items.size(); j++){
					for (unsigned int k = 0; k < items.size(); k++){
						if (containers[i] -> items[j] == items[k] -> name && items[k] -> name == object){
							trig = true;
							if (tof){
								return (true); //true if you want to trigger, else false
							}
							else{
								return (false);
							}
						}
					}
				}
			}
			if (!trig){ //knows if object is in inventory
				if (!tof){
					return (true);
				}
				else{
					return (false);
				}
			}
		}
	}
	//check for the status value
	else if (status != ""){
		for (unsigned int i = 0; i < rooms.size(); i++){
			if (object == rooms[i] -> name){
				if (status == rooms[i] -> status){
					return (true);
				}
				else {
					return (false);
				}
			}
		}
		for (unsigned int i = 0; i < containers.size(); i++){
			if (object == containers[i] -> name){
				if (status == containers[i] -> status){
					return (true);
				}
				else {
					return (false);
				}
			}
		}
		for (unsigned int i = 0; i < items.size(); i++){
			if (object == items[i] -> name){
				if (status == items[i] -> status){
					return (true);
				}
				else {
					return (false);
				}
			}
		}
		for (unsigned int i = 0; i < creatures.size(); i++){
			if (object == creatures[i] -> name){
				if (status == creatures[i] -> status){
					return (true);
				}
				else {
					return (false);
				}
			}
		}
	}
	return false;

}

bool checktrigger(string userinput){
	//trigger for room
	for (unsigned int i = 0; i < currentroom->triggers.size();i++){
		for (unsigned int j = 0; j < currentroom->triggers[i]->conditions.size(); j++){
			string obj = currentroom->triggers[i]->conditions[j]->object;
			string owner = currentroom->triggers[i]->conditions[j]->owner;
			string has = currentroom->triggers[i]->conditions[j]->has;
			string status = currentroom->triggers[i]->conditions[j]->status;
			//cout << obj + " " + owner + " " + has + " " + status <<endl;

			if (currentroom->triggers[i]->command == userinput || !currentroom->triggers[i]->commandexist){
				bool triggered = checkcond(obj, owner, has, status);
				if (triggered){
					if (currentroom->triggers[i]->type == "permanent" || (currentroom->triggers[i]->type == "single" && currentroom->triggers[i]->times == false)){
						if (currentroom->triggers[i]->type == "single"){
							currentroom->triggers[i]->times = true;
						}
						cout << currentroom->triggers[i]->print << endl;
						for (unsigned int k = 0; k < currentroom -> triggers[i]-> action.size(); k++){
							executeaction(currentroom -> triggers[i]-> action[k]);
						}
						return (true);
					}
				}
			}
		}
	}
	//trigger for creature
	for (unsigned int i = 0; i < currentroom->creatures.size();i++){
		for (unsigned int j = 0; j < creatures.size(); j++){
			if (currentroom->creatures[i] == creatures[j] -> name){
				for (unsigned int k = 0; k < creatures[j] -> triggers.size(); k++){
					for (unsigned int l = 0; l < creatures[j] -> triggers[k] -> conditions.size(); l++){
						string obj = creatures[j] -> triggers[k] -> conditions[l]->object;
						string owner = creatures[j] -> triggers[k] -> conditions[l]->owner;
						string has = creatures[j] -> triggers[k] -> conditions[l]->has;
						string status = creatures[j] -> triggers[k] -> conditions[l]->status;
						if (creatures[j] -> triggers[k] -> command == userinput || !creatures[j]->triggers[k]->commandexist){
							bool triggered = checkcond(obj, owner, has, status);
							if (triggered){
								if (creatures[j] -> triggers[k] -> type == "permanent" || (creatures[j] -> triggers[k] ->type == "single" && creatures[j] -> triggers[k] ->times == false)){
									if (creatures[j] -> triggers[k] ->type == "single"){
										creatures[j] -> triggers[k] ->times = true;
									}
									cout << creatures[j]->triggers[k]->print << endl;
									for (unsigned int m = 0; m < creatures[j] -> triggers[k] -> action.size(); m++){
										executeaction(creatures[j] -> triggers[k]-> action[m]);
									}
									return (true);
								}
							}
						}
					}
				}
			}
		}
	}

	//trigger for containers
	for (unsigned int i = 0; i < currentroom->containers.size();i++){
		for (unsigned int j = 0; j < containers.size(); j++){
			if (currentroom->containers[i] == containers[j] -> name){
				for (unsigned int k = 0; k < containers[j] -> triggers.size(); k++){
					for (unsigned int l = 0; l < containers[j] -> triggers[k] -> conditions.size(); l++){
						string obj = containers[j] -> triggers[k] -> conditions[l]->object;
						string owner = containers[j] -> triggers[k] -> conditions[l]->owner;
						string has = containers[j] -> triggers[k] -> conditions[l]->has;
						string status = containers[j] -> triggers[k] -> conditions[l]->status;
						if (containers[j] -> triggers[k] -> command == userinput || !containers[j] -> triggers[k] -> commandexist){
							bool triggered = checkcond(obj, owner, has, status);
							if (triggered){
								if (containers[j] -> triggers[k] -> type == "permanent" || (containers[j] -> triggers[k] ->type == "single" && containers[j] -> triggers[k] ->times == false)){
									if (containers[j] -> triggers[k] ->type == "single"){
										containers[j] -> triggers[k] ->times = true;
									}
									cout << containers[j]->triggers[k]->print << endl;
									for (unsigned int m = 0; m < containers[j] -> triggers[k] -> action.size(); m++){
										executeaction(containers[j] -> triggers[k]-> action[m]);
									}
									return (true);
								}
							}
						}
					}
				}
			}
		}
	}

	//trigger for items
	for (unsigned int i = 0; i < currentroom->items.size();i++){
		for (unsigned int j = 0; j < items.size(); j++){
			if (currentroom->items[i] == items[j] -> name){
				for (unsigned int k = 0; k < items[j] -> triggers.size(); k++){
					for (unsigned int l = 0; l < items[j] -> triggers[k] -> conditions.size(); l++){
						string obj = items[j] -> triggers[k] -> conditions[l]->object;
						string owner = items[j] -> triggers[k] -> conditions[l]->owner;
						string has = items[j] -> triggers[k] -> conditions[l]->has;
						string status = items[j] -> triggers[k] -> conditions[l]->status;
						if (items[j] -> triggers[k] -> command == userinput || !items[j] -> triggers[k] -> commandexist){
							bool triggered = checkcond(obj, owner, has, status);
							if (triggered){
								if (items[j] -> triggers[k] -> type == "permanent" || (items[j] -> triggers[k] ->type == "single" && items[j] -> triggers[k] ->times == false)){
									cout << items[j]->triggers[k]->print << endl;
									if (items[j] -> triggers[k] ->type == "single"){
										items[j] -> triggers[k] ->times = true;
									}
									for (unsigned int m = 0; m < items[j] -> triggers[k] -> action.size(); m++){
										executeaction(items[j] -> triggers[k]-> action[m]);
									}
									return (true);
								}
							}
						}
					}
				}
			}
		}
	}
	return (false);
}

