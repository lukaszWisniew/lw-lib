/*
 ============================================================================
 Name       :  LogLevel.h
 Date       :  10-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
*/



#ifndef LOG_LOGLEVEL_H_
#define LOG_LOGLEVEL_H_


namespace lw_lib {
/**
 * Enum class to set login level.
 */
	enum class LogLevel {
		INFO,
		WARNING,
		DEBUG,
		ERROR
	};
}


#endif /* LOG_LOGLEVEL_H_ */
