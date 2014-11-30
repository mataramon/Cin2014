package main

import (
        "flag"
        "fmt"
        "os"
        "net/http"
        "log"
        "io/ioutil"
        "time"
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

// Load web page file
func loadWebPage(title string) (*WebPage, error){
    log.Println("Loading web page template file: ", title)

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
    Server   string   // Server URL location 
    LogFile  string   // log file name e.g myclient.log
    Template string   // Template name for the front end app e.g ui.tmpl 
    Ofile    string   // Output file where the list is stored
    Web *WebPage // Web page in memory 
    Interval time.Duration 

}

/* Parser the command line parameters*/
func (self *Client) init() {
    // Parameters
    var server   = flag.String("server",  "http://162.243.155.132:3000", "This is the server location to download all files")
    var logfile  = flag.String("logfile", "client.log", "Please entry the log location") 
    var template = flag.String("template", "ui", "Insert the web page template to render eg ui")
    var outfile  = flag.String("outfile", "items.list", "File to download the locations")
    var interval = flag.Int("secs", 100, "Seconds to update and generate a new file")

    flag.Parse()
    self.Server  = *server
    self.LogFile = *logfile
    self.Template= *template
    self.Ofile   = *outfile
    self.Interval =  time.Duration(*interval) * time.Second

    // Logger
    log_file, err := os.OpenFile(self.LogFile, os.O_RDWR | os.O_CREATE | os.O_APPEND, 0666)
    if err != nil{
        fmt.Println("Cannot create log file ")
    }
    //defer log_file.Close()
    log.SetOutput(log_file)

    // Web page loading
    Web, err := loadWebPage(self.Template)
    if err != nil{
        log.Fatalln("Cannot continue error loading the template file", self.Template, err)
    }
    self.Web = Web

}

/* Shows the config to be used by the server */
func (self *Client) config() {
    // Log items
    log.Println("Starting Map Client application")
    log.Println("Remote Server: ", self.Server)
    log.Println("Logfile      : ", self.LogFile)
    log.Println("Template     : ", self.Template)
    // Displaying message for stdout
    fmt.Println("The Map Client is already started please check the logfile", self.LogFile)

}

// HTML Handler 
func (self *Client) Root (response http.ResponseWriter, rqx *http.Request) {
    fmt.Fprintf(response,"%s", self.Web.Body)
}

// This function does a request to download the locations.file this 
func (self *Client) Download() {
    // Creating download file 
        name := self.Ofile + time.Now().Format("2006_01_02_150405")

        f, err := os.Create(name)
        if err != nil{
            log.Println("Error creating output file")
            return
        }

    // Once the file is created the doing the request
        resp, err2 := http.Get(self.Server)
        // Accessing to the response
        if err2 != nil {
            log.Println("Error: cannot get updated info from server using Get request")
            return
        }
        
        defer resp.Body.Close()
        defer f.Close()
        
        body, err3 := ioutil.ReadAll(resp.Body)

        if err3 != nil {
            log.Println("Error: cannot open the Body from the get request")
        }

        f.Write(body)
        f.Sync()
        // symlink 
         failure := os.Symlink(name, self.Ofile) 
        if failure != nil {
            log.Println("Error: cannot update the symlink to ", self.Ofile)
        }

}
/*END OF ALL DATA STRUCTURES */

// Go routine to download the ubications
func update_data(client *Client){
    for {
          client.Download()
          time.Sleep(client.Interval)
    }
}

func main() {
    // Load config file
    var Rx Client 
    Rx.init()
    Rx.config()
    // Move to thread
    go update_data(&Rx)
    // Front end 
    http.HandleFunc("/", Rx.Root,)
    http.ListenAndServe(":8080", nil)

    log.Println("All operations done")
    log.Println("*******************************************")

}

/* APPLICATION DESCRIPTION 
 *
 *   This client   
 *       -> Post request to the server to get all the current positions.  
 *       -> The client will download this to a txt file
 *       
 *    FRONT - END HTML
 *       -> will plot all elements in / (root)
 *       -> There will be a Search Item, where you will see the nearest element to you. 
 */