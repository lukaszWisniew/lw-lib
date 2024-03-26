/*
 ============================================================================
 Name       :  ParseMainArgs.cpp
 Date       :  02-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#include "ParseMainArgs.h"

#include <iostream>


lw_lib::ParseMainArgs::ParseMainArgs() {
}

lw_lib::ParseMainArgs::~ParseMainArgs() {
}

bool
lw_lib::ParseMainArgs::addArg(string inKey, string inSwitch1, string inSwitch2, string inDesc, bool inParam) {
	bool output = false;

	vector<MainArg>::size_type i_argsVec;

	for (i_argsVec = 0; i_argsVec < _argsVec.size(); ++i_argsVec) {
		if ( _argsVec[i_argsVec].checkSwitches(inSwitch1,inSwitch2) ) {
			break;
		}
	}

	if (i_argsVec >= _argsVec.size()) {

		_argsVec.push_back( MainArg (inKey, inSwitch1, inSwitch2, inDesc, inParam));
	}

	return output;
}

bool
lw_lib::ParseMainArgs::onTheList(string inArg, string &outKey) {
	bool output = false;
	outKey = "";

	for(vector<MainArg>::size_type i_argsVec = 0; i_argsVec < _argsVec.size(); ++i_argsVec) {

		if (_argsVec[i_argsVec].checkSwitch(inArg)) {
			output = true;
			outKey = _argsVec[i_argsVec].getKey();
			i_argsVec = _argsVec.size();
		}
	}

	return output;
}

void
lw_lib::ParseMainArgs::printHelp(string inProgram_doc, string inFoot) {
	cout << "" << endl;
	cout << "  " << inProgram_doc << endl;
	cout << "" << endl;
	cout << " Switches:"<< endl;
	cout << "" << endl;

	for(vector<MainArg>::size_type i_argsVec = 0; i_argsVec < _argsVec.size(); ++i_argsVec) {
		cout << "  " << _argsVec[i_argsVec].getData() << endl;
	}

	if ( inFoot != "" ) {
		cout << "" << endl;
		cout << " " << inFoot << endl;
	}

	cout << "" << endl;

}

void
lw_lib::ParseMainArgs::printVersion(string inProgram_doc, string inVersion, string inGit_commit, string inRelease_date) {

	cout << "" << endl;
	cout << "  " << inProgram_doc << endl;
	cout << "" << endl;
	cout << "  Version: " << inVersion << "." << inGit_commit << endl;
	cout << "  Release date: " << inRelease_date << endl;
	cout << "" << endl;
	cout << "  Lukasz Wisniewski" << endl;
	cout << "  2024 (C) All rights reserved." << endl;
	cout << "" << endl;

}
