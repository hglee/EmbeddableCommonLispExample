
(defsystem "ecl-curl" :class asdf::prebuilt-system
	:lib #P"SYS:ECL-CURL.LIB"
	:depends-on NIL
	:components ((:compiled-file "ecl-curl" :pathname #P"SYS:ECL-CURL.FAS")))