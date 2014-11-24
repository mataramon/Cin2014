#!/usr/bin/env python
import sys
from subprocess import Popen, PIPE
import os
import platform
from os.path import isfile, join
import shutil

# Constants
current_path = os.path.dirname(os.path.realpath(__file__))
build_path = join(current_path, "build")

# shell commands
def shell(command):
    process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
    
    (std_output, std_error) = process.communicate()
    return_code = process.returncode
    
    return return_code, std_output, std_error


# Returns the list of files to be compiled
def Gcc():
    # Creating build directory
    files = [join(current_path,f) for f in os.listdir(current_path) if isfile(join(current_path,f))]
    return files
    
def main():
    Instruction = {
	"Darwin"   : "clang++ -std=c++11 -stdlib=libc++ {0} -o {0}.exec", 
	"Linux"  : "g++ -std=c++11 -pthread {0}           -o {0}.exec"
    }
    if not os.path.exists(build_path):
        os.makedirs(build_path)
    else:
        shutil.rmtree(build_path)
        os.makedirs(build_path)
    
    System = platform.system()
    
    Files = Gcc()
    # Taking c++ files for compile    
    cpp = [c for c in Files if c.endswith(".cpp") or c.endswith(".c")]
    
    if cpp:
        print "# C++ Compilation starting "
        # compiling c++ files 
        for cfile in cpp:
	    print "File: {0} ".format(cfile)
	    cmd = Instruction[System].format(cfile)
	    (code, std, err) = shell(cmd)
	    if not code:
	      print "-> OK"
	    else:
	      print "-> FAILURE"
	      print "   Dumping all information about the error"
	      print "   Command: {0}".format(cmd)
	      if std:
	          print "    Standard output information \n{0}".format(std)
	      if err:
	          print "    Error dump\n{0}".format(err)
	      
	      return False
    # Moving all .exec files to build path
    Files = Gcc()
    
    apps = [app for app in Files if app.endswith(".exec")]
    # Moving all files into the build directory
    for app in apps:
        shutil.move(app, build_path)

    return True 
    
if __name__== '__main__':
    rt = main()
    if rt:
      sys.exit(0)
    sys.exit(1)
