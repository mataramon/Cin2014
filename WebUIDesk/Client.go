package main

import (
        "flag"
        "fmt"
        "os"
        _"net/http"
        "log"
        "io/ioutil"
        )

/*******************************************/
// Web page data structure

type WebPage struct {
    Title string
    Body []byte
}

func (self *WebPage) save() error {
    filename := self.Title + ".tmpl"
    return ioutil.WriteFile(filename, self.Body,0600)  
}

func loadWebPage(title string) (*WebPage, error){
    log.Println("Loading web page tempalte file: ", title)

    filename := title + ".tmpl"
    body, err := ioutil.ReadFile(filename)

    if err != nil{
        return nil, err
    }

    return &WebPage{Title: title, Body: body}, nil
}

/**************************************/
// CLIENT OBJECT 
// This object download the list of coordenates
type Client struct{
    Server  string   // Server URL location 
    LogFile string   // log file name e.g myclient.log
    Template string  // Template name for the front end app e.g ui.tmpl 

}

/* Parser the command line parameters*/
func (self *Client) init() {
    // Parameters
    var server   = flag.String("server",  "http://162.243.155.132:3000", "This is the server location to download all files")
    var logfile  = flag.String("logfile", "client.log", "Please entry the log location") 
    var template = flag.String("template", "ui", "Insert the web page template to render eg ui")

    flag.Parse()
    self.Server  = *server
    self.LogFile = *logfile
    self.Template= *template

    // Logger
    log_file, err := os.OpenFile(self.LogFile, os.O_RDWR | os.O_CREATE | os.O_APPEND, 0666)
    if err != nil{
        fmt.Println("Cannot create log file ")
    }
    //defer log_file.Close()
    log.SetOutput(log_file)


}

/* Shows the config to be used by the server */
func (self *Client) config() {
    log.Println("*******************************************")
    log.Println("Starting Map Client application")
    log.Println("Remote Server: ", self.Server)
}

func (self *Client) Download() {


}


/*END OF ALL DATA STRUCTURES */

func main() {
    // Load config file
    var Rx Client 
    Rx.init()
    Rx.config()

    Web, err := loadWebPage(Rx.Template)
    if err != nil{
        log.Fatalln("Cannot continue error loading the template file", Rx.Template, err)
    }
    fmt.Println(string(Web.Body))



    log.Println("All operations done")
    log.Println("*******************************************")

}
