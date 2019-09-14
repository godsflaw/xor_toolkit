# install
```
./configure
make
make install
```

# help
```
xor_toolkit -help

Usage: xor_toolkit
[-ihedpb] [-k <key>] [-f <input_file>] [-F <output_file>]
[-s <KAPPA_P>] [-a <ALPHA>] [-l <key_length>] [-g <data_file>]
[-z <DELTA>] [-o <output_data>]

-h	print this usage message
-e	XOR encipher data
-d	XOR decipher data
-b	break xor cipher
-l	specify the key length manually
-i	just print index of coincidence information
-k	the key used to encipher/decipher data
-p	get KAPPA_P value for some input file
-s	set the KAPPA_P value (default: .06721)
-a	set the ALPHA point for key length match (default: 85.00)
-z	set DELTA value probable plaintext match (default: 45.00)
-g	set delta data information
-o	output data file name
-f	input file name
-F	output file name
```
