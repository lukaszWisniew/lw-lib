/*
 ============================================================================
 Name       :  LogRotateType.h
 Date       :  19-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
*/



#ifndef LOG_LOGROTATETYPE_H_
#define LOG_LOGROTATETYPE_H_

namespace lw_lib {
/**
 * Enum class to set log file rotate type.
 *
 * SIZE - rotate the log file if size file is bigger then ... in MB
 * TIME - rotate the log file if time is done (hh:min)
 */
enum class LogRotateType {
	SIZE,
	TIME,
	none
};

}

#endif /* LOG_LOGROTATETYPE_H_ */
