/*
 ============================================================================
 Name       :  EVmain.cpp
 Date       :  04-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#include "EVmain.h"

lw_lib::EV_main::EV_main() {
	_base = NULL;
}

lw_lib::EV_main::~EV_main() {}


void
lw_lib::EV_main::setBase( event_base *inBase ) {
	if ( inBase != NULL ) {
		_base = inBase;
	}
}

