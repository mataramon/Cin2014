#!/usr/bin/env python
# Memory model in python references

#functions
def multiply(a):
    print "Reference in the function: ", id(a)
    a = a*2
    # needs assigment and return
    #return a

def add(b):
    b["foo"] = "Nice example from add function"

print "##################################"
print "*) Test list"
a = range(10)
print "ref in main" , id(a)
multiply(a)
print "Total of items after function ", len(a)

print "*) Test dictionary"
dictionary = {}
add(dictionary)
print dictionary

print "*) Test string "
x = 'bar'
y = x
y += 'foo'
print "result: ", x

print "*) Test list in main"
x = range(20)
y = x
y *= 2 
print "result: ", x
