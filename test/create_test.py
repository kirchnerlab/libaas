#!/usr/bin/env python
#
# Copyright (C) 2011 Marc Kirchner
# Copyright (C) 2008 Bernhard Kausler
#

import os
import sys
import getopt

class Usage(Exception):
    def __init__(self, msg):
        self.usage = "Usage: " + sys.argv[0] + " [-h] <classname>"
        self.msg = msg

def main(argv=None):
    if argv is None:
        argv = sys.argv
    try:
        try:
            opts, args = getopt.getopt(argv[1:], "h", ["help"])
        except getopt.error, msg:
            raise Usage(msg)
        for o, a in opts:
            if o == "-h":
                raise Usage("")
        if len(args) < 1:
            raise Usage("too few arguments")
        
        # copy template and replace class name
        classname = sys.argv[1]
        print classname
        testfilename = classname+'-test.cpp'
        print testfilename
        testfile = open(testfilename, 'w')

        template = open('TEST_TEMPLATE.cpp')
        template = template.read()
        template = template.replace('CLASSNAME', classname)
        template = template.replace('FILENAME', testfilename)

        testfile.write(template)

        # adding the new unit test to git
        os.system("git add " + testfilename)

        cmakefile = open('CMakeLists.txt', 'r')
        cmake = cmakefile.read()
        cmakefile.close()

        srcs = 'SET(SRCS_'+classname.upper()+' '+testfilename+')'
        print srcs
        cmake = cmake.replace('#### Sources', '#### Sources\n'+srcs)


        test = 'ADD_LIBAAS_TEST("'+classname+'" test_'+classname.lower()+\
               ' ${SRCS_'+classname.upper()+'})'
        print test
        cmake = cmake.replace('#### Tests', '#### Tests\n'+test)

        cmakefile = open('CMakeLists.txt', 'w')
        cmakefile.write(cmake)
        cmakefile.close()
    except Usage, err:
        print >>sys.stderr, err.usage
        return 2

if __name__ == "__main__":
    sys.exit(main())

