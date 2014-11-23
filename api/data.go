package api

/* DATA TYPES */
type Business struct {
	ID int
	Name string
	Latitute string
	Longitud string
}

/* BASIC OPERATIONS*/

type ApiError struct{
	Error int
	ErrorMsg string
}

type Result struct {
	ApiError
	Places []Business
}

type Search struct{
	Word string
	Location string
}


