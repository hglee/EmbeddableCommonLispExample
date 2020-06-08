
(defsystem "rt" :class asdf::prebuilt-system
        :lib #P"SYS:RT.LIB"
        :depends-on NIL
        :components ((:compiled-file "rt" :pathname #P"SYS:RT.FAS")))