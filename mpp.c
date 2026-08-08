//MIT License

//Copyright (c) 2026 StarDog555

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  EDIT THIS */
char *COMPILER = "clang"; // clang, gcc, cl, and cc
char *OUTNAME = "example"; // main ect..
char *MAIN = "example/test.c"; // ---.c ---.c ect..
char *LINKS = ""; // -lInlcude ect.
char *FLAGS = ""; // "-Wall - Wextra" ect.
/*-----------------------
* -----------------------
* -----------------------
*/

typedef enum {
    COMPILER_CLANG,
    COMPILER_GCC,
    COMPILER_CC,
    COMPILER_CL,
    COMPILER_UNKNOWN
} CompilerID;


void Check_For_NULL() 
{
    if (MAIN == NULL) {
        fprintf(stderr ,"[-] ERROR: MAIN is Null");
        return;
    }
}

CompilerID Get_CompilerID(char *c) 
{
    if (strcmp(c, "clang") == 0) return COMPILER_CLANG;
    else if (strcmp(c, "gcc") == 0) return COMPILER_GCC;
    else if (strcmp(c, "cc") == 0) return COMPILER_CC;
    else if (strcmp(c, "cl") == 0) return COMPILER_CL;
    return COMPILER_UNKNOWN;
}

void Run_CommandS(char *compiler) 
{
    switch (Get_CompilerID(compiler)) {
        case COMPILER_CLANG: {
            Check_For_NULL();
    
            const char *links = LINKS ? LINKS : "";
            const char *flags = FLAGS ? FLAGS : "";
    
            char command[1028];
            snprintf(command, sizeof(command),
                     "clang %s %s %s -o %s",
                     MAIN, links, flags, OUTNAME);
    
            int result = system(command);
            (void)result;
            break;
        }
    
        case COMPILER_GCC: {
            Check_For_NULL();
    
            const char *links = LINKS ? LINKS : "";
            const char *flags = FLAGS ? FLAGS : "";
    
            char command[1028];
            snprintf(command, sizeof(command),
                     "gcc %s %s %s -o %s",
                     MAIN, links, flags, OUTNAME);
    
            int result = system(command);
            (void)result;
            break;
        }
    
        case COMPILER_CC: {
            Check_For_NULL();
    
    #ifdef _WIN32
            fprintf(stderr, "[-] ERROR: 'cc' is not available on Windows.\n");
    #else
            const char *links = LINKS ? LINKS : "";
            const char *flags = FLAGS ? FLAGS : "";
    
            char command[1028];
            snprintf(command, sizeof(command),
                     "cc %s %s %s -o %s",
                     MAIN, links, flags, OUTNAME);
    
            int result = system(command);
            (void)result;
    #endif
            break;
        }
    
        case COMPILER_CL: {
            Check_For_NULL();
    
    #ifdef _WIN32
            const char *links = LINKS ? LINKS : "";
            const char *flags = FLAGS ? FLAGS : "";
    
            char command[1028];
            snprintf(command, sizeof(command),
                     "cl %s %s %s /Fe:%s.exe",
                     MAIN, links, flags, OUTNAME);
    
            int result = system(command);
            (void)result;
    #else
            fprintf(stderr, "[-] ERROR: Microsoft CL is only available on Windows.\n");
    #endif
            break;
        }
    
        case COMPILER_UNKNOWN:
        default:
            fprintf(stderr, "[-] ERROR: Unknown compiler.\n");
            break;
    }
}

int main(int argc, char **argv) 
{
    // Just HMMM HMM so good and 3 lines only just perfect
    if (argv[1]) {
        COMPILER = argv[1];
    }
    
    Run_CommandS(COMPILER);
    return 0;
}