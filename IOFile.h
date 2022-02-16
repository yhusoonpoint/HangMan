#ifndef _IOFILE_H_
#define _IOFILE_H_

#include <string>

class IOFile
{
    public:
        // explained in  header
        static bool replaceLineInFile(const char * path, const std::string & word, std::string & newWord);
        static int addLine(const std::string & data,const char * path);
        static void quickAdd(const char * path, const std::string & word);
};



#endif