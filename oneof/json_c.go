package main
import (
	t1 "./t1.pb"
	"fmt"
//	"os"
//	"io/ioutil"
//	"net/http"
//	"bytes"
)

func main() {
	t := new(t1.Terra)
	t.Mona = &t1.Terra_T{int32(1)}
//	t.Mona.(*t1.).T=1
	bt:=t.GetQwint()
	bt=t.GetT()
	fmt.Println(bt)
}
