
(defsystem "sb-bsd-sockets" :class asdf::prebuilt-system
        :lib #P"SYS:SB-BSD-SOCKETS.LIB"
        :depends-on ("sockets")
        :components ((:compiled-file "sb-bsd-sockets" :pathname #P"SYS:SB-BSD-SOCKETS.FAS")))