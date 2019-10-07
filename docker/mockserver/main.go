package main

import (
	"net/http"
	"fmt"
)

func sayHello(w http.ResponseWriter, r *http.Request) {
	userId := r.Header.Get("X-UserId")
	message := fmt.Sprintf("Hello, THIS IS YOUR USERID: %s", userId )
	w.Write([]byte(message))
}
  
func main() {
	http.HandleFunc("/", sayHello)
	if err := http.ListenAndServe(":12345", nil); err != nil {
	  panic(err)
	}
}