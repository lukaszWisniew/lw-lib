/*
 ============================================================================
 Name       :  IParseSwitches.cpp
 Date       :  29-09-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#include "IParseSwitches.h"

#include <iostream>

lw_lib::IParseSwitches::IParseSwitches() {
}
lw_lib::IParseSwitches::~IParseSwitches() {
}

string
lw_lib::IParseSwitches::_getParamValue(vector<string> &inArguments,	vector<string>::size_type &inIarguments) {
	string output;

	if (inArguments.size() > inIarguments + 1) {
		output = inArguments[++inIarguments];
	}

	return output;
}
