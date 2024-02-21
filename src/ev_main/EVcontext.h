/*
 ============================================================================
 Name       :  EVcontex.h
 Date       :  04-10-2023
 Author     :  Lukasz Wisniewski
 Email      :  lukasz.wisniew@gmail.com
 Copyright  :  (C) 2023 Lukasz Wisniewski
 ============================================================================
 */

#ifndef EV_MAIN_EVCONTEXT_H_
#define EV_MAIN_EVCONTEXT_H_

#include <netinet/in.h>


#include "../config/IConfiguration.h"
#include "EVmain.h"

namespace lw_lib {
	/**
	 * The base class for the application context.
	 */
	class EV_context : public EV_main {
	private:
		/** Entire application configuration.
		 * The class interface should be implemented in the application.
		 * */
		IConfiguration *_configuration;
	public:
		EV_context();
		virtual ~EV_context();

		/**
		 * Set the configuration of the entire application.
		 *
		 * @param inConfiguration
		 */
		void setConfiguration( IConfiguration *inConfiguration );

		/**
		 * Get the configuration of the entire application.
		 *
		 * @return Entire application configuration.
		 */
		IConfiguration* getConfiguration() { return _configuration; }
	};

}
#endif /* EV_MAIN_EVCONTEXT_H_ */
