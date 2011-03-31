Jonathan's XCode Templates

License
============

Copyright (c) 2010, Jonathan Fischer
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

 - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

 - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the
   distribution.


 - Neither the name of Jonathan Fischer nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

What is this?
=============

When I start a new project in Xcode, I've got a bunch of code that I
don't want to rewrite every time.  After dealing with copying stuff
into place every time I start a new project, I decided to go ahead and
wrap them up into an Xcode template so that I get a pre-configured,
ready to go project with all of my helper stuff already in place.

How do I use it?
================

Download and/or check out this repository, then copy the "SDL Game
Template" folder to:

~/Library/Application Support/Developer/Shared/Xcode/Project Templates/Application

Restart Xcode, and click Create a new Xcode project.  On the left
there should be a section named "User Templates".  Under that, choose
Application, then on the right you'll see "SDL Game Template".  Click
that, click Choose, and you'll be on your way.

You'll also need both the SDL and SDL_image frameworks installed.  You
can grab them from:

http://www.libsdl.org/download-1.2.php and
http://www.libsdl.org/projects/SDL_image/

Drag the .framework directories out of the disk image files to
/Library/Frameworks.  (or ~/Library/Frameworks, if you prefer)

How do I use the code?
======================

It's pretty self-explanatory; checkout Main.cpp for an example.