/**
 * File_Utilities.mm
 * Mac OS X implementation of PathForResource.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
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
