package main
import (
t1 "./t1.pb"
"fmt"
"reflect"
"github.com/golang/protobuf/jsonpb"
"encoding/json"
//	"github.com/golang/protobuf/descriptor"
)

func main() {
	t := t1.Terra{ B:2 , Mona:&t1.Terra_T{T: int32(1)} }
	b := &jsonpb.Marshaler{}
	bt,_ := b.MarshalToString(&t)
	fmt.Println(bt)
	li,_ := json.Marshal(&t)
	fmt.Println(string(li),"\n")
	var f reflect.Value
	f = reflect.ValueOf(t)
	ce := f.Type()
	c := 0
	tr := f.Field(c); 
	x := f.Type().Field(c);c = c + 1
			cf := x.Name
		fmt.Println(cf)
	if fe := x.Tag.Get("protobuf_oneof");fe != "" {
		wr := reflect.ValueOf(fe).Type()
		fmt.Println("tr",wr)
	}
	;fmt.Println(x,tr)
	tr = f.Field(c);
	x = f.Type().Field(c);c = c + 1
	h := tr.Interface()
	if fe := x.Tag.Get("protobuf_oneof");fe != "" {
		cf := x.Name
		fmt.Println(cf)
		fmt.Println("tr",fe)
	}
	z := tr.Elem().Elem().Field(0)
	xb := tr.Elem().Elem().Type().Field(0)
	sq := reflect.TypeOf(z.Interface())
	wr := f.Kind()
	trtd := reflect.TypeOf(f.Interface())
	var q bool
	q = !false
	fmt.Println(xb,z);
	fmt.Println("\n",ce)
	fmt.Println(sq)
	fmt.Println(wr)
	fmt.Println(trtd)
	fmt.Println(h)
	fmt.Println(q)


}
