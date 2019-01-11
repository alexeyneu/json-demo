package main
import (
	t1 "./t1.pb"
	"fmt"
	"reflect"
	"github.com/golang/protobuf/jsonpb"
)

func main() {
	t := t1.Terra{}
	t.Mona = &t1.Terra_T{int32(1)}
	t.B = 2
	b := &jsonpb.Marshaler{}
	bt,_ := b.MarshalToString(&t)
	fmt.Println(bt,"\n")

	
	f := reflect.ValueOf(t)
	ce := f.Type()
	c := 0
	tr := f.Field(c); 
	x := f.Type().Field(c);c = c + 1
		;fmt.Println(x,tr)
	tr = f.Field(c);
	x = f.Type().Field(c);c = c + 1
	if x.Tag.Get("protobuf_oneof") != "" {
		fmt.Println("tr")
	}
	z := tr.Elem().Elem().Field(0)
	xb := tr.Elem().Elem().Type().Field(0)
	fmt.Println(xb,z);
	fmt.Println("\n",ce)


}
