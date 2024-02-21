/*
 ============================================================================
 Name       :  ParseMainArgs.h
 Date       :  02-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#ifndef PARSEMAINARGS_H_
#define PARSEMAINARGS_H_

#include <string>
#include <vector>

#include "MainArg.h"

using namespace std;

namespace lw_lib {

	/** A class that parses program arguments. */
	class ParseMainArgs final {
	private:
		/** argsVec PRogram arguments list. */
		vector<MainArg>_argsVec;

	public:
		ParseMainArgs();
		virtual ~ParseMainArgs();

		/**
		 * Adding program arguments to be parsed.
		 *
		 * A blank value "" of switch1 and switch2 fields at the same time is not allowed.
		 *
		 * @param inKey the key of program argument.
		 * @param switch1 short form of program argument
		 * @param switch2 long form of program argument
		 * @param inDesc Description of argument
		 * @param inParam the true if argument need set the value
		 *
		 * @return true - Successful addition to parsing. false - Otherwise
		 *
		 * @see MainArg class
		 */
		bool addArg(string inKey, string inSwitch1, string inSwitch2, string inDesc, bool inParam);

		/**
		 * Check the program argument be on the list.
		 *
		 * @param inArg Argument passed for checking.
		 * @param outKey If the argument is in the list, the argument key is returned.
		 *
		 * @return true - List contain the argument.
		 *
		 * @see -
		 */
		bool onTheList(string inArg, string &outKey);

		/**
		 * Send program help to standard output.
		 *
		 * @param inProgram_doc Program description
		 * @param inFoot Program description footer.
		 *
		 * @return -
		 *
		 * @see -
		 */
		void printHelp(string inProgram_doc, string inFoot = "");

		/**
		 * Send program version to standard output.
		 *
		 * @param inProgram_doc Program description
		 * @param inVersion Program description footer.
		 * @param inGit_commit  the git commit key
		 * @param inRelease_date The release date of program
		 *
		 * @return -
		 *
		 * @see -
		 */
		void printVersion(string inProgram_doc, string inVersion, string inGit_commit, string inRelease_date);
	};
}
#endif /* PARSEMAINARGS_H_ */
