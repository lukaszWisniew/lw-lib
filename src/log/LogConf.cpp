/*
 ============================================================================
 Name       :  LogConf.cpp
 Date       :  10-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#include "LogConf.h"

#include <iostream>
#include <regex>

#include "../misc/Procedures.h"

namespace lw_lib {

LogConf::LogConf () {
	_verbose   = false;
	_logEnable = false;
	_loglevel  = LogLevel::INFO;
	_file_path = "undefined";
	_file_name = "undefined";
	_rotate    = false;
	_addPID    = false;
	_logRotateType = LogRotateType::none;
	_logRotateTime = "undefined";
	_logRotateSize = 0;
}

LogConf::LogConf(std::string &inFilePath, std::string &inFileName, LogLevel inLogLevel, bool inRotate, bool inAddPID) {
	_loglevel  = inLogLevel;
	_file_path = inFilePath;

	_rotate    = inRotate;
	_addPID    = inAddPID;
	_logRotateType = LogRotateType::none;
	_logRotateTime = "undefined";
	_logRotateSize = 0;
	_logEnable = true;
	_verbose = false;
}

LogConf::~LogConf() {}

void
LogConf::setVerboseMode( bool inVerbose ) {
	_verbose = inVerbose;
}

bool
LogConf::isVerboseMode() {
	return _verbose;
}

void
LogConf::setLogEnable( bool inLogEnable) {
	_logEnable = inLogEnable;
}

bool
LogConf::isLogEnable() const {
	return _logEnable;
}

const std::string&
LogConf::getFilePath() const {
	return _file_path;
}

void
LogConf::setFilePath(const std::string &inFilePath) {
	_logEnable = true;
	_file_path = inFilePath;
}

const
std::string& LogConf::getFileName() const {
	return _file_name;
}

void
LogConf::setFileName(const std::string &inFileName) {
	_logEnable = true;
	_file_name = inFileName;
}


LogLevel
LogConf::getLoglevel() const {
	return _loglevel;
}

void
LogConf::setLoglevel(LogLevel inLoglevel) {
	_logEnable = true;
	_loglevel = inLoglevel;
}

bool
LogConf::isRotate() const {
	return _rotate;
}

void
LogConf::setRotate(bool inRotate) {
	_logEnable = true;
	_rotate = inRotate;
}

bool
LogConf::isAddPid() const {
	return _addPID;
}

void
LogConf::setAddPid(bool inAddPid) {
	_logEnable = true;
	_addPID = inAddPid;
}

void
LogConf::setRotateFileType(LogRotateType inLogRotateType) {
	_logEnable = true;
	_logRotateType = inLogRotateType;
}

LogRotateType
LogConf::getLogRotateType() {
	return _logRotateType;
}


void
LogConf::setLogRotateTime (const std::string &inTime ) {
	_logEnable = true;
	_logRotateTime = inTime;
}

const std::string&
LogConf::getLogRotateTime() {
	return _logRotateTime;
}

void
LogConf::setLogRotateSize (uint inLogRotateSize) {
	_logEnable = true;
	_logRotateSize = inLogRotateSize;
}

uint
LogConf::getLogRotateSize () {
	return _logRotateSize;
}

bool
LogConf::checkRotateTimeFormat(const std::string& inTime) {
	std::regex wzorzec("\\d\\d:\\d\\d"); // Wyrażenie regularne dla formatu "cyfra cyfra : cyfra cyfra"
	return std::regex_match(inTime, wzorzec);
}

std::string
LogConf::logLevelToString( LogLevel inLoglevel ) {
	std::string output;

	_logEnable = true;

	switch (inLoglevel) {
		case LogLevel::INFO: output = "INFO";
			break;
		case LogLevel::WARNING: output = "WARNING";
			break;
		case LogLevel::DEBUG: output = "DEBUG";
			break;
		case LogLevel::ERROR: output = "ERROR";
			break;
	}
	return output;
}

std::string
LogConf::_rotateTypeToString ( LogRotateType inLogRotateType ) {
	std::string output;

	_logEnable = true;

	switch ( inLogRotateType ) {
		case LogRotateType::SIZE: output = "SIZE";
			break;
		case LogRotateType::TIME: output = "TIME";
			break;
		case LogRotateType::none:
		default:
			output = "not set";
			break;
	}

	return output;
}

void
LogConf::showConfig() {
	std::cout << "[" << "LOGGING" << "]" << std::endl;
	std::cout << " " << "LOGLEVEL    = " << logLevelToString(_loglevel) << std::endl;
	std::cout << " " << "FILE_PATH   = " << _file_path << std::endl;
	std::cout << " " << "FILE_NAME   = " << _file_name << std::endl;
	std::cout << " " << "ADD_PID     = " << ( _addPID ? "on" : "off" ) << std::endl;
	std::cout << " " << "ROTATE      = " << ( _rotate ? "on" : "off" ) << std::endl;
	if ( _rotate ) {
		std::cout << " " << "ROTATE_TYPE = " << _rotateTypeToString(_logRotateType) << std::endl;
		switch (_logRotateType) {
			case LogRotateType::SIZE:
				std::cout << " " << "ROTATE_SIZE_FILE = " << toString<uint>(_logRotateSize) << std::endl;
				break;
			case LogRotateType::TIME:
				std::cout << " " << "ROTATE_TIME = " << _logRotateTime << std::endl;
				break;
			case LogRotateType::none:
			default:
				break;
		}
	}
	std::cout << "[]" << std::endl;
	std::cout << "" << std::endl;
}

} /* namespace lw_lib */
