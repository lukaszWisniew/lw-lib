/*
 ============================================================================
 Name       :  MainArg.cpp
 Date       :  02-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#include "MainArg.h"

#include <iostream>

lw_lib::MainArg::MainArg(string inKey, string inSwitch1, string inSwitch2, string inDesc, bool inValue ) {
	_key     = inKey;
	_switch1 = inSwitch1;
	_switch2 = inSwitch2;
	_desc    = inDesc;
	_value   = inValue;
}

lw_lib::MainArg::~MainArg() {}

bool
lw_lib::MainArg::checkSwitch(string inSwitch) {
	bool output = false;

	if ( inSwitch == "" ||(  !inSwitch.compare(_switch1) || !inSwitch.compare(_switch2))) {
		output = true;
	}
	return output;
}

bool
lw_lib::MainArg::checkSwitches(string inSwitch1, string inSwitch2) {
	bool output = false;

	if ( !(inSwitch1 == "" && inSwitch2 == "") ) {
		if ( (!(_switch1.compare(inSwitch1)) && (inSwitch1!="")) || (!(_switch2.compare(inSwitch2)) && (inSwitch2 != "")) ) {
			output = true;
		}
	}
	return output;

}

string
lw_lib::MainArg::getKey() {
	return _key;
}

string
lw_lib::MainArg::getData() {

	string output = "";

	if (_switch1 != "" ) {
		output += _switch1;
	} else {
		output += "   ";
	}

	if ( _switch1 != "" && _switch2 != "" ) {
		output +=",";
	}

	output += " ";

	if (_switch2 != "" ) {
		output += _switch2;
		if (_value) {
			output += " <PARAM>   ";
		}
	} else {
		output += "   ";
	}

	output += "\t"+_desc;


	return output;
}

