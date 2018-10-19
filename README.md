#Victimize: Choose ~~your~~ someone else's fate

Ever had that situation where you had to pick someone at random ? Ever had six hours of free time ? I had both.

**USAGE**

Windows: ~~Just double click the .exe~~ victimize-ng [options]  
Linux: victimize [options] [path to txt file]

*Options:*  
- --cli: Outputs to console instead of through Qt
- --dull: Gets rid of the fancy reasons explaining why you'd want to toss that particular person under the bus

*Txt file format:*  
LASTNAME,firstname  
LASTNAME2,firstname2  
...  
LASTNAME999,firstname999

**COMPILING**

Windows: qmake && mingw32-make && mingw32-make clean  
Linux: qmake && make && sudo make install && make clean

Both assume you have the Qt binaries in your path. On Windows, you might want to call that command from Qt's prompt (it's probably called something like "Qt 5.XX for Desktop (MinGW 5.3.0 32-bit)" if you used the installer)

**FAQ**

Q: Why ?  
A: I was bored.

Q: What about MacOS ?  
A: You try and compile it yourself. I don't have a Mac. I wish I could say it *should* compile, but clang and gcc don't work the same way, so I really have no idea. Good luck.

Q: Precompiled binaries ?  
A: Windows should come soon. Linux less soon.

Q: Why does passing a .txt as launch option not work on Windows ?  
Short A: Not worth the effort setting up.  
Long A: Seriously, the CLI compatibility is essentially meant for Linux. Nothing really prevents you from adding that .exe to your %PATH% however, but if you're on Windows I still recommend you use the GUI. Passing a .txt as parameter should work, if it is in the same folder as the executable.
