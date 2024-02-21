/*
 ============================================================================
 Name       :  Log.h
 Date       :  17-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#ifndef LOG_LOG_H_
#define LOG_LOG_H_

#include <string>
#include <memory>

#include "LogConf.h"
#include "LogLevel.h"
#include "../misc/Procedures.h"

namespace lw_lib {

/**
 * Class encapsulate lib spdlog.
 * Simplifies use.
 */
class Log final {
private:

	/**
	 * Logging configuration .
	 */
	LogConf * _logConf;

	std::string _full_path;
	pid_t _pid;

public:
	Log();
	virtual ~Log();

	/**
	 * Set connfiguration
	 *
	 * See LogConf
	 *
	 * @param inLogConf the log configuration.
	 */
	void setLogConf(LogConf *inLogConf);

	/**
	 * Send log
	 *
	 * @param inLogLevel logLevel. See LogLevel
	 * @param inMessage message to log.
	 */
	void sendLog( LogLevel inLogLevel, std::string &inMessage );

	/**
	 * Send log in Info level.
	 *
	 * See LogConf
	 *
	 * @param inMessage message to log.
	 */
	void sendInfo( std::string inMessage );

	/**
	 * Send log in Warning level.
	 *
	 * See LogConf
	 *
	 * @param inMessage message to log.
	 */
	void sendWarning( std::string inMessage );

	/**
	 * Send log in Debug level.
	 *
	 * See LogConf
	 *
	 * @param inMessage message to log.
	 */
	void sendDebug( std::string inMessage );

	/**
	 * Send log in Error level.
	 *
	 * See LogConf
	 *
	 * @param inMessage message to log.
	 */
	void sendError( std::string inMessage );

private:

	/**
	 * Spdlog configuration according to the settings contained in LogConf.
	 */
	void _setLogger();

	void _rollBiggerThan();

	bool _isBiggerThan();

	bool _checkFileSizeMB( std::string &inFilePath, double &outFileSize );

	bool _checkLogLevel(LogLevel inLogLevel);

};

} /* namespace lw_lib */

#endif /* LOG_LOG_H_ */
