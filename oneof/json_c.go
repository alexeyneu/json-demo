package main
import (
	t1 "./t1.pb"
	"fmt"
	"github.com/golang/protobuf/jsonpb"
)

func main() {
	t := t1.Terra{}
	t.Mona = &t1.Terra_T{int32(1)}
	t.B = 2
	b := &jsonpb.Marshaler{}
	bt,_ := b.MarshalToString(&t)
	fmt.Println(bt)
}
