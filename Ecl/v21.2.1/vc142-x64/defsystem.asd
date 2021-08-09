
(defsystem "defsystem" :class asdf::prebuilt-system
        :lib #P"SYS:DEFSYSTEM.LIB"
        :depends-on NIL
        :components ((:compiled-file "defsystem" :pathname #P"SYS:DEFSYSTEM.FAS")))