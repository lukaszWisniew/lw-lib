/*
 ============================================================================
 Name       :  IParseSwitches.h
 Date       :  29-09-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#ifndef IPARSESWITCHES_H_
#define IPARSESWITCHES_H_

#include <vector>
#include <string>

#include "IConfiguration.h"

using namespace std;

namespace lw_lib {

	/** The class is an interface for implementing a class that examines the application's invocation switches. */
	class IParseSwitches {
	public:
		IParseSwitches();
		virtual ~IParseSwitches();

		/**
		 * A method is an interface to be implemented in a derived class.
		 *
		 * It should contain code that responds to application invocation switches.
		 *
		 * @param argc refers to the number of arguments passed to the program
		 * @param argv is a pointer array which points to each argument passed to the program
		 * @param inOutConfiguration The object contains program configuration variables.
		 */
		virtual void parse(int argc, char **argv, IConfiguration *inOutConfiguration) = 0;
	protected:

		/**
		 * Interface to a method containing a list of parameters that can be passed to the program during startup.
		 */
		virtual void _setParams() = 0;

		/**
		 * Retrieving the value of a parameter passed to the program during startup.
		 *
		 * @param inArguments list of arguments
		 * @param inIarguments position of argument in list
		 *
		 * @return value of parameter
		 */
		string _getParamValue(vector<string> &inArguments,	vector<string>::size_type &inIarguments);
	};
}
#endif /* IPARSESWITCHES_H_ */
