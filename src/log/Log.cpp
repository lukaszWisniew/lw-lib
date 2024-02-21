/*
 ============================================================================
 Name       :  Log.cpp
 Date       :  14-11-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
*/

#include "Log.h"

#include <unistd.h>
#include <filesystem>

namespace lw_lib {

namespace fs = std::filesystem;

Log::Log() {
	_logConf = NULL;
	_pid = gettid();
}

Log::~Log() {}

void
Log::setLogConf(LogConf *inLogConf) {
	_logConf = inLogConf;

	if (_logConf->isLogEnable()) {
		_setLogger();
	}
}

void
Log::sendLog(LogLevel inLogLevel, std::string &inMessage) {
	int error;

	std::string message = "[" + lw_lib::getCurrentDateTime3() + "] " +
			              "[" + _logConf->logLevelToString(inLogLevel) + "] " +
						  "[thread "  + toString<pid_t>(_pid) + "] " + inMessage + "\n";
	if ( _logConf->isVerboseMode()) {
		if ( LogLevel::ERROR == inLogLevel ) {
			std::cerr << message << std::flush;
		} else {
			std::cout << message << std::flush;
		}
	}

	if ( _logConf->isLogEnable() && _checkLogLevel(inLogLevel) ) {


		lw_lib::safeAddToFile(message, _full_path, error);

		if ( _logConf->isRotate() ) {
			_rollBiggerThan();
		}
	}
}

void
Log::sendInfo(std::string inMessage) {
	sendLog( LogLevel::INFO, inMessage);
}

void
Log::sendWarning(std::string inMessage) {
	sendLog( LogLevel::WARNING, inMessage);
}

void
Log::sendDebug(std::string inMessage) {
	sendLog( LogLevel::DEBUG, inMessage);
}

void
Log::sendError(std::string inMessage) {
	sendLog( LogLevel::ERROR, inMessage);
}

void
Log::_setLogger() {
	_full_path = _logConf->getFilePath() + "/" + _logConf->getFileName();

	if (_logConf->isAddPid()) {
		_full_path += "_" + toString<pid_t>(_pid) + ".log";
	} else {
		_full_path += ".log";
	}
}

void
Log::_rollBiggerThan() {
	double fileSize;
	if (_logConf->getLogRotateType() == lw_lib::LogRotateType::SIZE) {
		if (_checkFileSizeMB( _full_path, fileSize )) {
			if ( fileSize >= _logConf->getLogRotateSize() ) {
				if ( !_isBiggerThan() ) {
					sendError("The log file name cannot be changed.");
				}
			}
		}
	} else {
		sendError("Unable to check log file size.");
	}
}

bool
Log::_isBiggerThan() {
	bool outStatus = false;

	std::string nextName = _logConf->getFilePath() + "/" + _logConf->getFileName();

	if (_logConf->isAddPid()) {
		nextName += "_" + toString<pid_t>(_pid) + "_" + getCurrentDateTime4() + ".log";
	} else {
		nextName += "_" + getCurrentDateTime4() + ".log";
	}

    if (!( rename( _full_path.c_str() , nextName.c_str() ) < 0 )) {

    	std::ofstream fileStream(_full_path);
    	if (fileStream.is_open()) {
    		fileStream.close();
    	}
    	outStatus = true;
    }

	return outStatus;
}

bool
Log::_checkFileSizeMB( std::string &inFilePath, double &outFileSize ) {
	bool outStatus = false;
	outFileSize = 0;
	if (lw_lib::fileExist(inFilePath)) {
		std::uintmax_t fileSize = fs::file_size(inFilePath);
		outFileSize = static_cast<double>(fileSize) / (1024 * 1024);
		outStatus = true;
	}
	return outStatus;
}

bool
Log::_checkLogLevel(LogLevel inLogLevel) {
	bool outStatus = false;

	if ( _logConf->getLoglevel() == LogLevel::DEBUG ) {
		outStatus = true;
	} else if ( _logConf->getLoglevel() == LogLevel::INFO ) {
		switch (inLogLevel) {
			case LogLevel::INFO:
			case LogLevel::WARNING:
			case LogLevel::ERROR:
				outStatus = true;
		}
	} else if ( _logConf->getLoglevel() == LogLevel::WARNING ) {
		switch (inLogLevel) {
			case LogLevel::WARNING:
			case LogLevel::ERROR:
				outStatus = true;
		}
	} else if ( _logConf->getLoglevel() == LogLevel::ERROR ) {
		switch (inLogLevel) {
			case LogLevel::ERROR:
				outStatus = true;
		}
	}

	return outStatus;
}

} /* namespace lw_lib */


