/**
 * File_Utilities.mm
 * Mac OS X implementation of PathForResource.
 *
 *  ___PROJECTNAME___
 *
 *  Created by ___FULLUSERNAME___ on ___DATE___.
 *  Copyright ___YEAR___ ___ORGANIZATIONNAME___. All rights reserved.
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
