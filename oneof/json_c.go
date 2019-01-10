package main
import (
	t1 "./t1.pb"
	"fmt"
	"github.com/golang/protobuf/jsonpb"
	"bytes"
//	"io/ioutil"
)

func main() {
	t := t1.Terra{}
	t.Mona = &t1.Terra_T{int32(1)}
	t.B = 2
//	bt:=t.GetQwint()
//	bt=t.GetT()
	bt:=bytes.NewBuffer(nil)
	b := &jsonpb.Marshaler{}
	b.Marshal(bt , &t)
	fmt.Println(bt)
	fmt.Println(t.String())
}
