/*
 *  File_Utilities.mm
 *  EgobooNext
 *
 *  Created by Jonathan Fischer on 1/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Utility.h"

static char sPath[PATH_MAX];

const char* PathForResource(const char *resource)
{
	const char *str;
	NSString *resourcesPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingString: @"/"];
	NSString *finalPath = [resourcesPath stringByAppendingString: [NSString stringWithCString: resource
																					 encoding: NSASCIIStringEncoding]];
	
	str = [finalPath cStringUsingEncoding: NSASCIIStringEncoding];
	strcpy(sPath, str);
	[finalPath release];
	[resourcesPath release];
	
	return sPath;
}
