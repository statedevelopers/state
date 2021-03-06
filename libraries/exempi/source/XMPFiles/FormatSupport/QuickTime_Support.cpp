// =================================================================================================
// ADOBE SYSTEMS INCORPORATED
// Copyright 2002-2008 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE: Adobe permits you to use, modify, and distribute this file in accordance with the terms
// of the Adobe license agreement accompanying it.
// =================================================================================================

#include "XMP_Environment.h"
#if ! ( XMP_64 || XMP_UNIXBuild)	//	Closes at very bottom.

#include "QuickTime_Support.hpp"

#if XMP_MacBuild
	#include <Movies.h>
#elif XMP_WinBuild
	#include "QTML.h"
	#include "Movies.h"
#endif

namespace QuickTime_Support 
{

	bool sMainInitOK = false;

	// =============================================================================================

	bool MainInitialize ( bool ignoreInit )
	{
		OSStatus err = noErr;
		
		if ( ignoreInit ) {
			sMainInitOK = true;
			return true;
		}
	
		#if XMP_WinBuild
			err = ::InitializeQTML ( 0 );
		#endif

		if ( err == noErr ) err = ::EnterMovies();
		if ( err == noErr ) sMainInitOK = true;
		
		return sMainInitOK;
	
	}	// MainInitialize
	
	// =============================================================================================

	void MainTerminate ( bool ignoreInit )
	{

		if ( ignoreInit ) return;
		
		::ExitMovies();

		#if XMP_WinBuild
			::TerminateQTML();
		#endif
	
	}	// MainTerminate
	
	// =============================================================================================

	bool ThreadInitialize()
	{
		OSStatus err = noErr;
		
		#if XMP_MacBuild
			err = ::EnterMoviesOnThread ( 0 );
		#endif
		
		return (err == noErr);
		
	}	// ThreadInitialize
	
	// =============================================================================================

	void ThreadTerminate()
	{
		
		#if XMP_MacBuild
			::ExitMoviesOnThread();
		#endif
		
	}	// ThreadTerminate

} // namespace QuickTime_Support

#endif
