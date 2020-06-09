
(defsystem "ecl-quicklisp" :class asdf::prebuilt-system
	:lib #P"SYS:ECL-QUICKLISP.LIB"
	:depends-on NIL
	:components ((:compiled-file "ecl-quicklisp" :pathname #P"SYS:ECL-QUICKLISP.FAS")))