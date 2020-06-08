
(defsystem "deflate" :class asdf::prebuilt-system
        :lib #P"SYS:DEFLATE.LIB"
        :depends-on NIL
        :components ((:compiled-file "deflate" :pathname #P"SYS:DEFLATE.FAS")))