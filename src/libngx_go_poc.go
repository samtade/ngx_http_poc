// package name: libngx_go_poc
package main

import (
	"C"
	"log"
	"github.com/google/uuid"
)

// main is required for the file to compile to an object.
func main() {}

//export GetUserID
func GetUserID() *C.char {
	uuidv1, error := uuid.NewUUID()

	if error != nil {
		log.Fatal(error)
	}

	return C.CString(uuidv1.String())
}
