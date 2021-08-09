
(defsystem "cmp" :class asdf::prebuilt-system
        :lib #P"SYS:CMP.LIB"
        :depends-on NIL
        :components ((:compiled-file "cmp" :pathname #P"SYS:CMP.FAS")))