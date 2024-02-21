/*
 ============================================================================
 Name       :  ConfigFile.h
 Date       :  03-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
*/

#ifndef CONFIGFILE_H_
#define CONFIGFILE_H_

#include <string>
#include <vector>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

namespace lw_lib {

	/** The class is used to parse the configuration file. */
	class ConfigFile {
	private:
		/** The path to configuration file. */
		string		    _fileName;
		/** The list of parameters */
		vector<string>	_params;
		/** List of parameter values. */
		vector<string>	_values;
	public:
		/**
		 * Default constructor
		 */
		ConfigFile();

		/**
		 * Main constructor
		 * @parm inConfigFile - The path to configuration file.
		 */
		ConfigFile(string const& inConfigFile);

		/**
		 * Read the configuration file if exist.
		 *
		 * Function read configuration file and put data to vectors _params and _values.
		 *
		 * @return True if the file was successfully read and parsed.
		 */
		bool read();

		/**
		 * Getting the section names of the configuration file.
		 *
		 * @param outSections The Map
		 */
		//void getSections(map<string,string>& outSections);

		/**
		 * Retrieving parameter names in a given section.
		 *
		 * @param inSection the section name
		 * @param outParameters the list of parameters
		 */
		void getSectionParameters(string const& inSection, vector<string>& outParameters);

		/**
		 * Retrieving the value of a parameter.
		 *
		 * @param inParameter Parameter name.
		 *
		 * @return value of a parameter if exit, otherwise ""
		 */
		string getParameter(string const& inParameter);

		/**
		 * Check whether the given parameter has been defined.
		 *
		 * @param inParameter parameter name
		 *
		 * @return true if parameter exist, false otherwise.
		 */
		bool isParameterDefined(string const& inParameter);

		/**
		 * Passing a list of parameters.
		 *
		 * @return list of parameters
		 */

		vector<string>& getParams(){
			return _params;
		}

		/**
		 * Passing a list of values.
		 *
		 * @return list of values
		 */
		vector<string>& getValues(){
			return _values;
		}

		/**
		 * If the parameter exists, its value is overwritten.
		 *
		 * @param inParameter parameter name
		 * @param inValue value of parameter
		 */
		void setParameterValue(string const& inParameter, string& inValue);
	};
}
#endif
