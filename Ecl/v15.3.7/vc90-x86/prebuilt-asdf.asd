
(defsystem "prebuilt-asdf" :class asdf::prebuilt-system
	:lib #P"SYS:ASDF.LIB"
	:depends-on ("cmp")
	:components ((:compiled-file "prebuilt-asdf" :pathname #P"SYS:ASDF.FAS")))