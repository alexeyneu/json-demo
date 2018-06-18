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
	s:=os.ExpandEnv("${APPDATA}\\Bitcore\\.cookie")  // linux style but it's windows
	data, err := ioutil.ReadFile(s)
	if err!=nil {
		fmt.Fprintf(os.Stderr, " %v\n", err)
		os.Exit(1)
	}
	t:=string(data[11:])     // "__cookie__:"
	client := &http.Client{}
	z:=`{ "method":"listreceivedbyaccount","params": [0],"id":"listreceivedbyaccount" }`
	req, _ := http.NewRequest("POST","http://localhost:8556" , bytes.NewBuffer([]byte(z))) // "Content-Length: ...\r\n" is also needed in this request , but it dealt with by golang. value is len(z)
	req.SetBasicAuth("__cookie__",t) // what's  added exactly is "Authorization: Basic base64_encoded_name+:+pwd\r\n"
	response, _ := client.Do(req)
	bt , _:=ioutil.ReadAll(response.Body)
	fmt.Println(string(bt))
}
