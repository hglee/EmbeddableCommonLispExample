
(defsystem "ecl-cdb" :class asdf::prebuilt-system
        :lib #P"SYS:ECL-CDB.LIB"
        :depends-on NIL
        :components ((:compiled-file "ecl-cdb" :pathname #P"SYS:ECL-CDB.FAS")))