
(defsystem "ecl-help" :class asdf::prebuilt-system
	:lib #P"SYS:ECL-HELP.LIB"
	:depends-on NIL
	:components ((:compiled-file "ecl-help" :pathname #P"SYS:ECL-HELP.FAS")))