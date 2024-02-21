/*
 ============================================================================
 Name       :  Procedures.cpp
 Date       :  03-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
*/


#include "Procedures.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>

#include <iconv.h>
namespace lw_lib {
bool
OnOffOnBool( const char* inData ) {
  bool outStatus = false;
  std::string data = std::string(inData);

  transform(data.begin(), data.end(),data.begin(), ::toupper);

  if ( data == "YES" || data == "ON" || data == "TRUE" || data == "1" || data == "ALLOWED" )
    outStatus = true;

  return outStatus;
}

std::string
itos(int num) {
  std::stringstream s;
  s << num;
  return s.str();
}

std::string
uitos(unsigned int num) {
  std::stringstream s;
  s << num;
  return s.str();
}

std::string
ftos(float num) {
  std::stringstream s;
  s << num;
  return s.str();
}

int
stoi (std::string const& inData) {
  int i;

  std::istringstream iss(inData);
  iss >> i;

  return i;
}

unsigned int
stoui  (std::string const& inData) {
  unsigned int i;

  std::istringstream iss(inData);
  iss >> i;

  return i;
}

unsigned int
hstoui  (std::string const& inData) {
  unsigned int i;

  std::stringstream ss;
  ss << std::hex << inData;
  ss >> i;

  return i;
}

std::string
itohs(int num) {
  std::stringstream s;
  s << std::setfill('0') << std::setw(2) << std::hex << num;
  return s.str();
}

std::string
itoHs ( int inInt ) {
  std::ostringstream ss;
  std::string result = "00";
  ss << std::setfill ('0') << std::setw (2) << std::uppercase << std::hex << inInt;
  result = ss.str();
  return result;
}

std::string
uitohs(unsigned int num) {
  std::stringstream s;
  s << std::setfill('0') << std::setw(2) << std::hex << num;
  return s.str();
}

std::string
uitoHs(unsigned int num, std::string::size_type len) {
  std::stringstream s;
  std::string outstring;
  std::string tmpS;

  s << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << num;

  tmpS = s.str();

  if ( tmpS.length() < len ) {
    for ( std::string::size_type i = 0; i < (len - tmpS.length()); ++i ) {
      outstring += "0";
    }
    outstring += tmpS;
  } else {
	outstring = tmpS;
  }

  return outstring;
}

bool
readFileTostring ( std::string &inData, std::string &outData ) {
  bool outStatus = false;
  std::string line   = "";
  std::fstream file;

  outData = "";

  if ( lw_lib::fileExist( inData ) ) {
    file.open( inData.c_str(), std::fstream::in );
    if ( file.is_open ( ) ) {
      while ( file.good() ) {
        getline (file, line);
        outData += line;
      }
      file.close();
      outStatus = true;
    }
  }

  return outStatus;
}

bool
readBFileToV ( const std::string &inPath, std::vector<uint8_t> &outData ) {
  bool outStatus = false;
  std::string line   = "";
  std::fstream file;

  std::streampos size;
  char * memblock;

  outData.clear();

  if ( lw_lib::fileExist( inPath ) ) {
    file.open( inPath.c_str(), std::ios_base::in | std::ios_base::binary | std::ios::ate);
    if ( file.is_open ( ) ) {

      size = file.tellg();
      memblock = new char [size];
      file.seekg (0, std::ios::beg);
      file.read (memblock, size);
      file.close();

      outData.insert(outData.end(), memblock, memblock + size);

      delete[] memblock;
      outStatus = true;
    }
  }

  return outStatus;
}

bool
fileExist ( const std::string &inData ) {

	std::fstream file;
  file.open(inData.c_str(), std::ios_base::in );
  if (file.is_open()) {
    file.close();
    return true;
  } else {
    file.close();
    return false;
  }
}

bool
dirExist ( const std::string &inData ) {

  struct stat st;

  if(stat(inData.c_str(),&st) == 0) {
    if((st.st_mode & S_IFDIR) != 0) {
      return true;
    }
  }
  return false;
}


int GetFileDescriptor(std::filebuf& filebuf) {
  class my_filebuf : public std::filebuf
  {
  public:
    int handle() { return _M_file.fd(); }
  };

  return static_cast<my_filebuf&>(filebuf).handle();
}

bool
safeSaveFile ( const std::string &inData, const std::string &inTmpDir, const std::string &inFilePath, int &outError ) {
  bool         outStatus = true;
  std::string  tmpfilePath = "";
  std::string  destDir = "";
  std::string  filePath    = "";
  size_t  poz       = 0;
  std::fstream file;

  outError = 0;

  if ( !dirExist( inTmpDir ) ) {
    outStatus = false;
    outError = ENOTSUP;
  } else {
    poz = inFilePath.find_last_of('/', inFilePath.length());
    if ( poz != std::string::npos ) {
      destDir = inFilePath.substr( poz );
      tmpfilePath = inTmpDir + inFilePath.substr( poz, ( inFilePath.length() - poz ) ) + ".part";
      filePath = inFilePath;
    } else {
      tmpfilePath = inTmpDir + "/" +inFilePath + ".part";
      filePath = std::string("./") + inFilePath;
      destDir = std::string("./");
    }

    file.open( tmpfilePath.c_str(), std::fstream::out );
    if ( file.is_open ( ) ) {

      file << inData;
      file.flush();

      if ( fsync(GetFileDescriptor(*file.rdbuf())) < 0 ) {
        file.close();
        outError  = errno;
        remove( tmpfilePath.c_str() );
        outStatus = false;
      } else {
        file.close();
        if ( rename( tmpfilePath.c_str() , filePath.c_str() ) < 0 ) {
          outError  = errno;
          remove( tmpfilePath.c_str() );
          outStatus = false;
        } else {
          //TODO: Dodac fsync na katalogu
        }
      }
    } else {
      outError  = errno;
      outStatus = false;
    }
  }
  return outStatus;
}

bool
safeAddToFile ( const std::string &inData, const std::string &inFilePath, int &outError ) {
	bool outStatus = false;
	outError = 0;

	std::ofstream fileStream(inFilePath, std::ios::app);

	if (!fileStream.is_open()) {
		outError = errno;
	} else {

		fileStream << inData;

		fileStream.flush();

		fileStream.close();

		outStatus = true;
	}

	return outStatus;
}

bool
checkMAC ( const std::string &inMAC ) {
  bool status = true;

  if ( inMAC.length() != 17 ) {
    status = false;
  } else {
    for (unsigned int i = 0; (i < inMAC.length()) && status; ++i ) {
      if ( (i%3) == 2 ) {
        if ( inMAC.c_str()[i] != ':') {
          status = false;
        }
      } else {
        if ( (inMAC.c_str()[i] < '0') || (inMAC.c_str()[i] > '9') ) {
          if ((inMAC.c_str()[i] < 'A') || (inMAC.c_str()[i] > 'F')) {
            if ((inMAC.c_str()[i] < 'a') || (inMAC.c_str()[i] > 'f')) {
              status = false;
            }
          }
        }
      }

    }
  }
  return status;
}

bool
checkIPMask ( const std::string &inMAC ) {
  bool status = true;
  std::vector<std::string> maskTokens;
  int octet;


  lw_lib::tokenize(inMAC.c_str(), maskTokens, ".");

  if ( maskTokens.size() == 4 ) {
    for ( std::vector<std::string>::size_type i_maskTokens = 0;  status && (i_maskTokens < maskTokens.size()); ++i_maskTokens) {
      octet = lw_lib::stoi(maskTokens[i_maskTokens]);
      if ( ( octet < 0 ) || ( octet > 255 ) ) {
        status = false;
      }
    }
  } else {
    status = false;
  }

  return status;
}

bool
isIpAddress(const char* text){

  if(text == NULL || text[0]==0){
    return false;
  }

  std::vector<std::string> ipTokens;

  lw_lib::tokenize(text, ipTokens, ".");

  if(ipTokens.size() == 4){

    char* tailptr;
    long int retVal;

    for (int i = 0; i < 4; ++i) {

      tailptr = NULL;

      retVal = strtol(ipTokens[i].c_str(), &tailptr, (int)0);

      if(tailptr!=NULL && tailptr[0]!=0){
        return false;
      }else{
        if(retVal<0 || retVal>=255){
          return false;
        }
        if(i==0 || i==3){
          if(retVal==0){
            return false;
          }
        }
      }
    }
    return true;
  }
  return false;
}

bool
checkIPPortServices( const std::string &inPort ) {
  bool outStatus = false;
  int port;

  port = lw_lib::stoi(inPort);

  if ( port > 100 && port < 65535 ) {
    outStatus = true;
  }

  return outStatus;
}

std::string
trim(std::string const& source, char const* delims) {
  std::string result(source);
  std::string::size_type index = result.find_last_not_of(delims);
  if(index != std::string::npos)
    result.erase(++index);

  index = result.find_first_not_of(delims);
  if(index != std::string::npos)
    result.erase(0, index);
  else
    result.erase();
  return result;
}

void
tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters){

  tokens.clear();

    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}


void
tokenizeBytes(std::vector<uint8_t>& inData, std::vector<std::string>& tokens, const uint8_t& delimiters) {

  //std::vector<uint8_t>::size_type last_pos = 0;
  std::string tmp_s;

  tokens.clear();

  for ( std::vector<uint8_t>::size_type i_data = 0; i_data < inData.size(); ++i_data ) {
    if ( inData[i_data] == delimiters ) {

      tokens.push_back(tmp_s);
      tmp_s.clear();
      //last_pos = i_data;

    }
    else {
      tmp_s.push_back(inData[i_data]);
    }
  }
  tokens.push_back(tmp_s);

}

std::string
getValue( std::string &inStr, const std::string& inDelimiters ) {
  std::string outstring = "";

  std::string::size_type pos = inStr.find(inDelimiters);
  if ( pos != inStr.npos ) {
    outstring = inStr.substr(pos + 1, inStr.length() - (pos+1));
  }

/*  tokenize( inStr, tokens, ":" );
  if ( tokens.size() == 2 ) {
    outstd::string = tokens[1];
  }*/

  return outstring;
}



std::string
byteUnsignedChar(unsigned char *inData, int inDataLen) {
  std::string outstring = "";

  for (int i = 0; i < inDataLen; ++i) {
    outstring += uitohs( inData[i] );
  }

  return outstring;
}

uint16_t
twou8Tou16( uint8_t data1, uint8_t data2 ) { //two u8 to one u16
  return (data1 & 0xff) + ((data2 & 0xff) *256);
}

void
msleep ( unsigned int inMiliSec ) {

  timespec req;
  timespec rem;

  rem.tv_sec  = 0;
  rem.tv_nsec = 0;

  req.tv_sec  = inMiliSec / 1000;
  req.tv_nsec = ( inMiliSec % 1000 ) * 1000000;

  if ( req.tv_nsec > 999999999 ) {
    req.tv_sec += req.tv_nsec / 1000000000;
    req.tv_nsec = req.tv_nsec % 1000000000;
  }

  while ( req.tv_sec > 0 || req.tv_nsec > 0 ) {
    nanosleep(&req, &rem);
    req = rem;
  }

}

std::string
getCurrentDateTime() {

  char buf[128];

  struct timeval tv;
  struct tm tt;

  gettimeofday(&tv, NULL);

  localtime_r(&tv.tv_sec, &tt);

  sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d%c%02d:%02d",
      tt.tm_year + 1900, tt.tm_mon + 1,
      tt.tm_mday, tt.tm_hour, tt.tm_min, tt.tm_sec,
      tt.tm_gmtoff > 0 ? '+' : '-',
      int(abs(tt.tm_gmtoff) / 3600),
      int((abs(tt.tm_gmtoff) / 60) % 60));

  return std::string(buf);
}

std::string
getCurrentDateTime2() {

  char buf[128];

  struct timeval tv;
  struct tm tt;

  gettimeofday(&tv, NULL);

  localtime_r(&tv.tv_sec, &tt);

  sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
      tt.tm_year + 1900, tt.tm_mon + 1, tt.tm_mday,
      tt.tm_hour, tt.tm_min, tt.tm_sec);

  return std::string(buf);
}

std::string
getCurrentDateTime3() {
	// Pobierz bieżącą datę i czas
	auto now = std::chrono::system_clock::now();

	// Przekształć na std::time_t
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	// Ustaw precyzję na mikrosekundy
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

	// Użyj std::put_time do sformatowania daty i czasu
	std::stringstream ss;
	ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S.") << std::setfill('0') << std::setw(3) << us.count() / 1000;

	return ss.str();
}

std::string
getCurrentDateTime4() {
	// Pobierz bieżącą datę i czas
	auto now = std::chrono::system_clock::now();

	// Przekształć na std::time_t
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	// Ustaw precyzję na mikrosekundy
	auto s = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

	// Użyj std::put_time do sformatowania daty i czasu
	std::stringstream ss;
	ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d_%H.%M.%S");

	return ss.str();
}

std::string
DateTimeToS( int64_t timestamp ) {
   char            fmt[64], buf[64];
   struct timeval  tv;
   struct tm       *tm;

   tv.tv_sec = timestamp / 1000;
   tv.tv_usec = (timestamp % 1000) * 1000;

   tm = localtime(&tv.tv_sec);
   strftime(fmt, sizeof fmt, "%Y-%m-%d %H:%M:%S.%%06u", tm);
   snprintf(buf, sizeof buf, fmt, tv.tv_usec);

   return buf;
}

std::string
getBrAddress( std::string inInterface ) {
  int fd;
  struct ifreq ifr;

  std::string outAddress;

  fd = socket(AF_INET, SOCK_DGRAM, 0);

  //Type of address to retrieve - IPv4 IP address
  ifr.ifr_addr.sa_family = AF_INET;

  //Copy the interface name in the ifreq structure
  strncpy(ifr.ifr_name , inInterface.c_str() , IFNAMSIZ-1);

  //get the br address
  ioctl(fd, SIOCGIFBRDADDR, &ifr);

  //display ip
  //printf("IP address of %s - %s\n" , inInterface.c_str() , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
  outAddress = std::string(inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr));
  close(fd);

  return outAddress;

}

std::string
convertCharsCoding ( const char* inData, size_t inSize, const std::string& inFromCode, const std::string& inToCode ) {
  return lw_lib::convertCharsCoding(std::string(inData, inSize), inFromCode, inToCode);
}

std::string
convertCharsCoding ( const std::string& inData, const std::string& inFromCode, const std::string& inToCode ) {

  bool outStatus = true;

  char *input_(const_cast<char*>(inData.data()));
  std::string output(inData.size()*2, std::string::value_type());
  char *output_(const_cast<char *>(output.data()));
  size_t count;
  size_t inputLeft(inData.size());
  size_t outputLeft(inData.size()*2);
  iconv_t conv_desc;


  if (  !inToCode.compare("UTF-8") && lw_lib::isUTF8(inData.c_str(), inData.size()) ) {
    return inData;
  }

  conv_desc = iconv_open(inToCode.c_str(), inFromCode.c_str());

#if _LP64
  if (((unsigned long)conv_desc) == (size_t)-1) {
#else
  if (((unsigned int)conv_desc) == (size_t)-1) {
#endif

    switch (errno) {
        /* See "man 3 iconv" for an explanation. */
    case EILSEQ:
        fprintf (stderr, "Invalid multibyte sequence.\n");
        break;
    case EINVAL:
        fprintf (stderr, "Incomplete multibyte sequence.\n");
        break;
    case E2BIG:
        fprintf (stderr, "No more room.\n");
        break;
    default:
        fprintf (stderr, "Error: %s.\n", strerror (errno));
    }

    exit(EXIT_FAILURE);
  }

  while ((count = iconv(conv_desc, &input_, &inputLeft, &output_, &outputLeft)) == size_t(-1)) {
    if (errno == E2BIG) {
      output.resize(output.size() + (outputLeft += inputLeft));
      output_ = const_cast<char *>(output.data()) + output.size() - outputLeft;
    } else {
      outStatus = false;
      break;
    }
  }

  if ( outStatus ) {
    output.resize(output_ - output.data());
  } else {
    output.clear();
    output = inData;
  }

  iconv_close (conv_desc);

  return output;
}

bool
isUTF8(const void* pBuffer, long size) {

  bool outStatus = true;
  unsigned char* start = (unsigned char*)pBuffer;
  unsigned char* end = (unsigned char*)pBuffer + size;

  while (start < end) {
    if (*start < 0x80) { // (10000000)[output][/output]
      start++;
    }
    else if (*start < (0xC0)) { // (11000000)
      outStatus = false;
      break;
    }
    else if (*start < (0xE0)) { // (11100000)

      if (start >= end - 1) {
        break;
      }

      if ((start[1] & (0xC0)) != 0x80) {
        outStatus = false;
        break;
      }
      start += 2;
    }
    else if (*start < (0xF0)) { // (11110000)

      if (start >= end - 2) {
        break;
      }

      if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80) {
        outStatus = false;
        break;
      }
      start += 3;
    }
    else {

      outStatus = false;
      break;
    }
  }
  return outStatus;
}
}

