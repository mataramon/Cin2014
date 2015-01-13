#!/usr/bin/env python
import sys

class decorator:

    def __init__(self, f):
        print "This is the constructor ! from the decorator"
        self.foo = f
        
    def __call__(self, name):
        print "Function from the decorator !!"
        z = self.foo(name)
        result = z*4
        return result
       
#@decorator
def myFoo(name):
    result = 2 * name
    return result

def main():
    print myFoo("jose")


if __name__ == '__main__':
    if main():
        sys.exit(0)
    sys.exit(1)
