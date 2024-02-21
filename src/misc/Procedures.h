/*
 ============================================================================
 Name       :  Procedures.h
 Date       :  03-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
*/

#ifndef PROCEDURES_H_
#define PROCEDURES_H_

#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <errno.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "md5.h"

/**
 * A set of useful methods.
 * A legacy from previous systems.
 */
namespace lw_lib {

	bool   OnOffOnBool( const char* inData );

	template <typename T> std::string
	toString( T& inData ) {
	std::stringstream s;

	  s << inData;

	  return s.str();
	}

	template <typename T> T
	stringTo( const std::string& inData ) {
	  T output;

	  std::stringstream s(inData);

	  s >> output;

	  return output;
	}


	std::string itos  (int num);
	std::string uitos (unsigned int num);
	std::string ftos  (float num);

	int    stoi  (std::string const& inData);

	unsigned int stoui  (std::string const& inData);
	unsigned int hstoui  (std::string const& inData);
	std::string itohs (int num );
	std::string itoHs (int num );
	std::string uitohs (unsigned int num );
	std::string uitoHs (unsigned int num, std::string::size_type len = 0 );

	bool   readFileToString ( std::string &inData, std::string &outData );
	bool   readBFileToV     ( const std::string &inPath, std::vector<uint8_t> &outData );
	bool   fileExist ( const std::string &inData );
	bool   dirExist ( const std::string &inData );
	bool   safeSaveFile ( const std::string &inData, const std::string &inTmpDir, const std::string &inFilePath, int &outError );
	bool   safeAddToFile ( const std::string &inData, const std::string &inFilePath, int &outError );

	bool   checkMAC ( const std::string &inMAC );
	bool   checkIPMask ( const std::string &inMAC );
	bool   isIpAddress(const char* text);
	bool   checkIPPortServices( const std::string &inPort );

	std::string getBrAddress( std::string inInterface );

	std::string trim    (std::string const& source, char const* delims = " \t\r\n");
	void   tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters);
	void   tokenizeBytes(std::vector<uint8_t>& inData, std::vector<std::string>& tokens, const uint8_t& delimiters);
	std::string getValue( std::string &inStr, const std::string& delimiters );

	std::string byteUnsignedChar(unsigned char *inData, int inDataLen);

	uint16_t twou8Tou16( uint8_t data1, uint8_t data2 );

	void msleep ( unsigned int inMiliSec );

	std::string getCurrentDateTime();
	std::string getCurrentDateTime2();
	std::string getCurrentDateTime3();
	std::string getCurrentDateTime4();
	std::string DateTimeToS( int64_t timestamp );

	bool isUTF8(const void* pBuffer, long size);
	std::string convertCharsCoding ( const std::string& inData, const std::string& inFromCode, const std::string& inToCode );
	std::string convertCharsCoding ( const char* inData, size_t inSize, const std::string& inFromCode, const std::string& inToCode );

}
#endif /* PROCEDURES_H_ */
