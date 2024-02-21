/*
 ============================================================================
 Name       :  LogConf.h
 Date       :  10-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#ifndef LOG_LOGCONF_H_
#define LOG_LOGCONF_H_

#include <string>

#include "LogLevel.h"
#include "LogRotateType.h"

namespace lw_lib {
/**
 * The class that keep the configuration for logging.
 * Setters added to make it possible to reload the configuration,
 * without restarting the application.
 */
class LogConf {
private:
	/** Log enable */
	bool _logEnable;

	/** Send messages on stdout */
	bool _verbose;

	/** Login level.*/
	LogLevel    _loglevel;

	/** Path to the file where logs are to be dumped. */
	std::string _file_path;

	/** The name of log file. */
	std::string _file_name;

	/** Information whether logs are to be rolled. */
	bool        _rotate;

	/** Add the thread PID to file name. */
	bool        _addPID;

	/** The type of Rotate log file */
	LogRotateType _logRotateType;

	/** Create a new log file every day at the specified time */
	std::string _logRotateTime;

	/** The max size of log file in MB*/
	uint _logRotateSize;

public:
	/** Main constructor */
	LogConf();

	/**
	 * Constructor with parameters.
	 *
	 * @param inFilePath Path to the file where logs are to be dumped.
	 * @param inFileName Logs file name.
	 * @param inLogLevel Login level.{INFO, WARNING, DEBUG}
	 * @param inRotate Information whether logs are to be rolled.
	 * @param inAddPID Add pid process to name file log.
	 */
	LogConf( std::string &inFilePath, std::string &inFileName, LogLevel inLogLevel, bool inRotate, bool inAddPID );
	virtual ~LogConf();

	/**
	 * Setting sned log to stdout.
	 *
	 * @param inVerbose true - send message to stdout.
	 */
	void setVerboseMode( bool inVerbose );

	/**
	 * Get the Verbose mode status.
	 *
	 * @return Status of verbose mode - enable verbose enable
	 */
	bool isVerboseMode();

	/**
	 * Setting the log enable
	 *
	 * @param inLogEnable Enable logging
	 */
	void setLogEnable( bool inLogEnable);

	/**
	 * Get the logging is enabled
	 *
	 * @return true if logging is enabled.
	 */
	bool isLogEnable() const;

	/**
	 * Getting the path to the log file.
	 *
	 * @return Path to the log location.
	 */
	const std::string& getFilePath() const;

	/**
	 * Setting the path to the log file.
	 *
	 * @param inFilePath path to the log file.
	 */
	void setFilePath(const std::string &inFilePath);

	/**
	 * Getting the name of the log file.
	 *
	 * @return The log file name.
	 */
	const std::string& getFileName() const;

	/**
	 * Setting the name of log file.
	 *
	 * @param inFileName path to the log file.
	 */
	void setFileName(const std::string &inFileName);


	/**
	 * Getting the logging level
	 *
	 * @return Login level.
	 */
	LogLevel getLoglevel() const;

	/**
	 * Setting the logging level
	 *
	 * @param inLoglevel logging level
	 */
	void setLoglevel(LogLevel inLoglevel);

	/**
	 * Getting the logging file rotate parameter.
	 *
	 * @return rotate value
	 */
	bool isRotate() const;

	/**
	 * Setting the logging file rotate parameter.
	 *
	 * @param inRotate Rotate parameter. True if the log file is to be rolled.
	 */
	void setRotate(bool inRotate);

	/**
	 * Sending settings to standard output.
	 */
	void showConfig();

	/**
	 * Get the status add thread pid to log file name.
	 *
	 * @return true if add pid is on.
	 */
	bool isAddPid() const;

	/**
	 * Set add pid thread to file log.
	 *
	 * @param inAddPid true if add pid number to file log.
	 */
	void setAddPid(bool inAddPid);

	/**
	 * Set rotate type
	 *
	 * See LogRotateType
	 *
	 * @param ROtate type
	 */
	void setRotateFileType(LogRotateType inLogRotateType);

	/**
	 * Get rotate log file type
	 *
	 * See LogRotateType
	 *
	 * @return rotate type.
	 */
	LogRotateType getLogRotateType();

	/**
	 * Set time to time rotate log type
	 *
	 * @param inTime time in format hh:mm (07:05)
	 */
	void setLogRotateTime (const std::string &inTime );

	/**
	 * Get time to time rotate log type
	 *
	 * @return time in format hh:mm (07:05)
	 */
	const std::string &getLogRotateTime();

	/**
	 * Set file size to size rotate log type.
	 *
	 * @param inLogRotateSize file size in MB
	 */
	void setLogRotateSize (uint inLogRotateSize);

	/**
	 * Get file size to size rotate log type.
	 *
	 * @return file size in MB
	 */
	uint getLogRotateSize ();

	/**
	 * Checks the correctness of the given time for logrotate.
	 *
	 * See lw_lib::LogConf
	 *
	 * @param inTime time in format hh:mm
	 */
	bool checkRotateTimeFormat(const std::string& inTime);

	/**
	 * Method used to convert from enum to string.
	 *
	 * @param inLoglevel Logging level enum
	 *
	 * @return Logging level in string mode.
	 */
	std::string logLevelToString( LogLevel inLoglevel );

private:

	/**
	 * Method used internally to convert from enum to string.
	 *
	 * @param inLogRotateType rotate type (file, time)
	 *
	 * @return Rotate type in string mode.
	 */
	std::string _rotateTypeToString ( LogRotateType inLogRotateType );
};

} /* namespace lw_lib */

#endif /* LOG_LOGCONF_H_ */
