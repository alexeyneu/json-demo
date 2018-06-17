package main

import (
	"fmt"
	"os"
	"io/ioutil"
	"net/http"
	"bytes"
)
//Bitcore
func main() {
	s:=os.ExpandEnv("${APPDATA}\\Bitcore\\.cookie")
	data, _ := ioutil.ReadFile(s)
	var t string
	fmt.Sscanf(string(data),"__cookie__:%s",&t)
	client := &http.Client{}
	endPoint := "http://localhost:8556"
	z:=`{ "method":"listreceivedbyaccount","params": [0],"id":"listreceivedbyaccount" }`
	req, _ := http.NewRequest("POST", endPoint, bytes.NewBuffer([]byte(z))) // "Content-Length: ...\r\n" is also needed in this request , but it dealt with by golang. value is len(z)
	req.SetBasicAuth("__cookie__",t) // what's  added exactly is "Authorization: Basic base64_encoded_name+:+pwd\r\n"
	response, _ := client.Do(req)
	bt , _:=ioutil.ReadAll(response.Body)
	fmt.Println(string(bt))
}
