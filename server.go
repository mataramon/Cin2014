package main

import (
  "github.com/codegangsta/negroni"
  "encoding/json"
  "github.com/gorilla/mux"
  "net/http"
  "fmt"
  "./api"
)

func main() {
  // Result
  Business_1 := &api.Business { 
    ID:1,
    Name: "Angel's work",
    Latitute: "50000",
    Longitud: "7000",
  }

  Item,_ := json.Marshal(Business_1)

  // mux handler
  mux := mux.NewRouter()
  mux.HandleFunc("/",func(w http.ResponseWriter, req *http.Request) {
    fmt.Println("Header:")
    fmt.Println(req.Header)
    fmt.Println("Body")
    fmt.Println(req.Body)

    fmt.Fprintf(w, string(Item))
  }).Methods("GET")

    mux.HandleFunc("/",func(w http.ResponseWriter, req *http.Request) {
      // Decoding the json format
      decoder := json.NewDecoder(req.Body)
      var request api.Search
      err := decoder.Decode(&request)

      if err != nil {
          fmt.Fprintf(w, "Sorry cannot continue working")
          fmt.Println("you want to know where to find", request.Word)

      }else{

          fmt.Println("you want to know where to find", request.Word)
          fmt.Fprintf(w, "Starting to work")
      }
  }).Methods("POST")


  n := negroni.Classic()
  n.UseHandler(mux)
  n.Run(":3000")
}