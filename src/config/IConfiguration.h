/*
 ============================================================================
 Name       :  IConfiguration.h
 Date       :  04-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#ifndef CONFIG_ICONFIGURATION_H_
#define CONFIG_ICONFIGURATION_H_

#include <string>

namespace lw_lib {
	/** A class is an interface for implementing a class that describes the program's configuration. */
	class IConfiguration {
	public:
		/** Verbose mode */
		bool        _verbose;
		/** Path to the configuration file */
		std::string _configFilePath;

	public:

		IConfiguration();
		virtual ~IConfiguration();

		/**
		 * A virtual method that is the method interface,
		 * for setting variables according to the configuration contained in the configuration file.
		 */

		virtual void readConfigFile() = 0;

		/**
		 * A virtual method that is the method interface for displaying the full configuration.
		 */
		virtual void showConfig() = 0;
	};
}
#endif /* CONFIG_ICONFIGURATION_H_ */
