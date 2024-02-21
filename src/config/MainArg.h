/*
 ============================================================================
 Name       :  MainArg.h
 Date       :  02-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#ifndef MAINARG_H_
#define MAINARG_H_

#include <string>

using namespace std;

namespace lw_lib {

	/** A class that describes the program argument set at runtime. */
	class MainArg final {
	private:
		/** The key by which the argument is recognized. */
		string _key;

		/** The first form of argument */
		string _switch1;

		/** The second form of argument */
		string _switch2;

		/** Description of argument */
		string _desc;

		/** The argument contains a value */
		bool   _value;

	public:

		/**
		 * Constructor
		 *
		 * @param inKey The key by which the argument is recognized.
		 * @param inSwitch1 The first type of argument, usually in shortened form.
		 * 					It is given in the form -<parameter>
		 * 					A blank value "" is allowed.
		 * @param inSwitch2 The second type of argument, usually in full form.
		 * 					It is given in the form --<parameter>.
		 * 					A blank value "" is allowed.
		 */
		MainArg(string inKey, string inSwitch1, string inSwitch2, string inDesc, bool inValue);
		virtual ~MainArg();

		/**
		 * Check whether the given parameter is this one.
		 *
		 * @param inSwitch Parameter name
		 */
		bool checkSwitch(string inSwitch);

		/**
		 * Checking whether the given parameter in two variants is this one.
		 *
		 * @param inSwitch1 Parameter name, first form
		 * @param inSwitch2 Parameter name, second form
		 */
		bool checkSwitches(string inSwitch1, string inSwitch2);

		/**
		 * Get the argument key.
		 *
		 * @return key of argument
		 */
		string getKey();

		/**
		 * Retrieving full data about an argument, including a description.
		 *
		 * @return full data
		 */
		string getData();

	};
}
#endif /* MAINARG_H_ */
