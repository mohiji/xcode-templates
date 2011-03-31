/**
 * Utility.h
 * Handy helper functions.
 *
 * This file is part of Jonathan Fischer's Xcode Game Template:
 * https://github.com/mohiji/xcode-templates
 */

#ifndef Utility_h
#define Utility_h

// Return the proper path to load a file from, relative to the
// game's directory.  If you need to keep that path around, make
// a copy of it.  PathForResource uses a static variable to pass
// the generated path around so that we don't have to worry about
// freeing it.
const char* PathForResource(const char *resource);

// Round a number up to the next nearest power of two
int NearestPowerOfTwo(int n);

#endif /* include guard */
