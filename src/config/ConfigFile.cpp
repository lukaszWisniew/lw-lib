/*
 ============================================================================
 Name       :  ConfigFile.cpp
 Date       :  03-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
*/

#include "ConfigFile.h"

#include "../misc/Procedures.h"

lw_lib::ConfigFile::ConfigFile() : _fileName("undefined") {}

lw_lib::ConfigFile::ConfigFile(string const& inConfigFile) : _fileName(inConfigFile) { }

bool
lw_lib::ConfigFile::read() {
  ifstream file;

  file.open(_fileName.c_str(), ifstream::in);

  if(file.fail()){
	  return false;
  }

  string line;
  string param;
  string value;
  string section;

  unsigned int pos;

  while (getline(file,line)) {

    if (! line.length()) continue;

    line = lw_lib::trim(line);

    if (line[0] == '#') continue;
    if (line[0] == ';') continue;

    pos = line.find('#');
    if(pos!=string::npos){
    	line = lw_lib::trim(line.substr(0,pos));
    }else{
    	pos = line.find(';');
    	if(pos!=string::npos){
    		line = lw_lib::trim(line.substr(0,pos));
    	}
    }

    if (line[0] == '[') {
    	section=lw_lib::trim(line.substr(1,line.find(']')-1));
      continue;
    }

    if(line == "") {
    	continue;
    }

    vector<string> tokens;
    lw_lib::tokenize(line, tokens, "=");
    if(tokens.size()==2){
    	param = lw_lib::trim(tokens[0]);
    	value = lw_lib::trim(tokens[1]);

    	//cout << "ConfigFile: param = '" << param << "'"<< " value = '" << value << "'" << endl;

    	_params.push_back(section+'/'+param);
    	_values.push_back(value);

    }else if(tokens.size()==1){
    	param = lw_lib::trim(tokens[0]);

    	//cout << "ConfigFile: param = '" << param << "'" << endl;

    	_params.push_back(section+'/'+param);
    	_values.push_back("");
    }
  }

  file.close();
  return true;
}

/*void
ConfigFile::getSections(map<string,string>& outSections){

	sections.clear();

	for (unsigned int i = 0; i < _params.size(); ++i) {

		int pos = _params[i].find("/");
		if(pos > 0){
			sections[_params[i].substr(0,pos)] = "";
		}
	}
}*/

void
lw_lib::ConfigFile::getSectionParameters(string const& inSection, vector<string>& outParameters){

	string section = inSection;

	outParameters.clear();

	transform(section.begin(), section.end(),section.begin(), ::toupper);

	for (unsigned int i = 0; i < _params.size(); ++i) {

		if(_params[i].find(section)==0 && _params[i].at(section.length())=='/'){
			//cout << param << "***" << endl;
			outParameters.push_back(_params[i].substr(section.length()+1,_params[i].size()-(section.length()+1)));
		}
	}
}

string
lw_lib::ConfigFile::getParameter(string const& inParameter){

	string value;

	for (unsigned int i = 0; i < _params.size(); ++i) {

		if(_params[i] == inParameter){
			value = _values[i];
		}
	}

	//logger.info(parameter+" = '" + value + "'");

	return value;
}

bool
lw_lib::ConfigFile::isParameterDefined(string const& inParameter){

	for (unsigned int i = 0; i < _params.size(); ++i) {

		//cout << "P1:" << parameter << endl;
		//cout << "P2:" << _params[i] << endl;

		if(_params[i] == inParameter){
			//cout << "+" << endl;
			return true;
		}
		//cout << "-" << endl;
	}

	return false;
}

void
lw_lib::ConfigFile::setParameterValue(string const& inParameter, string& inValue){

	for (unsigned int i = 0; i < _params.size(); ++i) {

		if(_params[i] == inParameter){
			_values[i] = inValue;
		}
	}
}
