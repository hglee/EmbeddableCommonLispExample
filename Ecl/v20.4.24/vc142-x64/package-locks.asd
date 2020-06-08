
(defsystem "package-locks" :class asdf::prebuilt-system
        :lib #P"SYS:PACKAGE-LOCKS.LIB"
        :depends-on NIL
        :components ((:compiled-file "package-locks" :pathname #P"SYS:PACKAGE-LOCKS.FAS")))