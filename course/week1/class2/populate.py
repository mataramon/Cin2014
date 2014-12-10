#!/usr/bin/env python
import sys
import random 
import urllib2
import json

# Random item with name latitude and longitude
class GeoItem:
    # Constructor
    def __init__(self, name):
         #Generating random elements
         self.name = name
         self.latitude = random.randrange(20,25)-random.random()
         self.longitude= random.randrange(-104,-97)-random.random()
         self.latitude  = round(self.latitude, 7)
         self.longitude = round(self.longitude, 7)

    def send_data(self):
        #Sends the information to the server
        # dictionary
        data = {
          "name"     : str(self.name),
          "latitude" : str(self.latitude),
          "longitude": str(self.longitude)
        }
        request = urllib2.Request("http://162.243.155.132:3000/")
        request.add_header('Content-Type', 'application/json') 
        response = urllib2.urlopen(request, json.dumps(data))
        print response.read()
        print "-> {0}".format(data)
        #print "result: {0}".format(response)
        
         
def main():
    print "Generating boots"
    #generaring 1000 bots 
    for i in xrange(3000):
        Item = GeoItem("PadtsBot{0}".format(i))
        # Sending request to the server to store information
        Item.send_data()

        

if '__main__' == __name__:
    ret = main()
    if ret:
        sys.exit(0)
    sys.exit(1)

