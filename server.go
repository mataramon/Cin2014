package main

import (
  "github.com/codegangsta/negroni"
  "github.com/gorilla/mux"
  "./api"
)  

func main() {
  // mux handler
  var server api.Server
  server.Url = "162.243.155.132:5000"
  server.DbName = "cinvestav"
  server.Collection = "tele"
  server.Init()

  mux := mux.NewRouter()

  mux.HandleFunc("/", server.GetALL).Methods("GET")
  mux.HandleFunc("/", server.AddRequest).Methods("POST")

  n := negroni.Classic()
  n.UseHandler(mux)
  n.Run(":3000")
}
