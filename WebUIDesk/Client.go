package main

import (
        "flag"
        "fmt"
        )

type Client struct{
    Server string
}

func (self *Client) init() {
    var tmp = flag.String("server", "http://162.243.155.132:3000", "This is the server location to download all files")
    flag.Parse()
    self.Server = *tmp;
}

func (self *Client) config() {
    fmt.Println("----- Map Client ----")
    fmt.Println("-> Remote Server: ", self.Server)
}

func main() {
    // Load config file
    var Rx Client 
    Rx.init()
    Rx.config()


}
