/*
 ============================================================================
 Name       :  EVcontex.cpp
 Date       :  04-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#include "EVcontext.h"

lw_lib::EV_context::EV_context() {
	_configuration = NULL;
}

lw_lib::EV_context::~EV_context() {}

void
lw_lib::EV_context::setConfiguration( IConfiguration *inConfiguration ) {

	if ( inConfiguration != NULL ) {
		_configuration = inConfiguration;
	}
}
