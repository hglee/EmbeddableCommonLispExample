
(defsystem "sockets" :class asdf::prebuilt-system
	:lib #P"SYS:SOCKETS.LIB"
	:depends-on NIL
	:components ((:compiled-file "sockets" :pathname #P"SYS:SOCKETS.FAS")))