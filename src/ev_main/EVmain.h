/*
 ============================================================================
 Name       :  EVmain.h
 Date       :  04-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#ifndef EV_MAIN_EVMAIN_H_
#define EV_MAIN_EVMAIN_H_

#include <event2/event.h>

namespace lw_lib {
	/**
	 * Base class for others based on libevent.
	 */
	class EV_main {
	public:
		/** Structure to hold information and state for a Libevent dispatch loop. */
		struct event_base *_base;

	public:
		EV_main();
		virtual ~EV_main();

		/**
		 * Event_base setting for libevent2
		 *
		 * @param inBase Structure to hold information and state for a Libevent dispatch loop.
		 *
		 * @see libevent2 documentation.
		 */
		virtual void setBase( event_base *inBase );
	};

}

#endif /* EV_MAIN_EVMAIN_H_ */
