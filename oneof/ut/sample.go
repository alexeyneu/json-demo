/* Package example contains a code sample to explain usage and sample data for tests.
 */
package main

import (
	"crypto/sha256"
	"encoding/json"
	"fmt"
t1 "./t1.pb"
"gopkg.in/alexeyneu/precise-proofs.v1/proofs"
)

func main() {
	// ExampleDocument is a protobuf message


	// The FillSalts method is a helper function that fills all fields with 32
	// random bytes. SaltedExampleDocument is a protobuf message that has the
	// same structure as ExampleDocument but has all `bytes` field types.
	t := t1.Terra{}
	t.Mona = &t1.Terra_T{int32(1)}
	t.B = 2
	b :=  t1.Kh{}
	checkErr(proofs.FillSalts(&t, &b))

	doctree := proofs.NewDocumentTree(proofs.TreeOptions{Hash: sha256.New()})

	checkErr(doctree.AddLeavesFromDocument(&t, &b))
	checkErr(doctree.Generate())
	fmt.Printf("Generated tree: %s\n", doctree.String())

	// Generate the actual proof for a field. In this case the field called "ValueA".
	proof, err := doctree.CreateProof("t")
	checkErr(err)
	proofJson, _ := json.Marshal(proof)
	fmt.Println("Proof:\n", string(proofJson))

	// Validate the proof that was just generated
	valid, err := doctree.ValidateProof(&proof)
	checkErr(err)

	fmt.Printf("Proof validated: %v\n", valid)
}

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}
