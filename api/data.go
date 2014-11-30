package api

import (
    "net/http"
    "gopkg.in/mgo.v2"
    "gopkg.in/mgo.v2/bson"
    "fmt"
    "encoding/json"

    )

/* DATA TYPES */
type GeoItem struct {
    Name string
    Latitude string
    Longitude string
}

type Server struct {
    Db *mgo.Session  // database session
    Url string
    DbName string
    Collection string

}

func (self *Server) Init(){
    // Starts the database
    var err error
    self.Db, err = mgo.Dial(self.Url)        
    if err != nil { 
        panic(err) 
    } 
    // Optional. Switch the session to a monotonic behavior.                
    self.Db.SetMode(mgo.Monotonic, true) 
}

// Add elements to the database
func (self *Server) Add(Item *GeoItem) bool{
    c := self.Db.DB(self.DbName).C(self.Collection)
    data := bson.M{ "$set": *Item}
     _, err := c.UpsertId(Item.Name, data)

    var result GeoItem
    err = c.FindId(Item.Name).One(&result)
    if err != nil {
        fmt.Println("FindId Error: ", err)
        return false
   }
   
   return true

}

func (self * Server) AddRequest(w http.ResponseWriter, req *http.Request){
      decoder := json.NewDecoder(req.Body)
      var request GeoItem
      err := decoder.Decode(&request)

      if err != nil {
          fmt.Fprintf(w, "The information provided is not valid\n")

      }else{

          fmt.Println(" User request information --------------")
          fmt.Println(" Name:", request.Name)
          fmt.Println(" Latitude:", request.Latitude)
          fmt.Println(" Longitude:", request.Longitude)
          
          result := self.Add(&request)

          if (result){  
                fmt.Fprintf(w, "Information saved\n")
             }else{
                fmt.Fprintf(w, "Error cannot save your data\n")
             }
      }
}



// Returns all the elements of the database
func (self *Server) GetALL(w http.ResponseWriter, req *http.Request){
    Business_1 := &GeoItem { 
    Name: "Angel's work",
    Latitude: "50000",
    Longitude: "7000",
  }

    Item,_ := json.Marshal(Business_1)

    fmt.Println("Header:")
    fmt.Println(req.Header)
    fmt.Println("Body")
    fmt.Println(req.Body)

    fmt.Fprintf(w, string(Item))
  

}



/* BASIC OPERATIONS*/

type ApiError struct{
    Error int
    ErrorMsg string
}

type Result struct {
    ApiError
    Places []GeoItem
}

type Search struct{
    Word string
    Location string
}


