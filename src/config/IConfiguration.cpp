/*
 ============================================================================
 Name       :  IConfiguration.cpp
 Date       :  04-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#include "IConfiguration.h"

lw_lib::IConfiguration::IConfiguration() {
	_verbose = false;
	_configFilePath = "";
}

lw_lib::IConfiguration::~IConfiguration() {
}
