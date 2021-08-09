
(defsystem "profile" :class asdf::prebuilt-system
        :lib #P"SYS:PROFILE.LIB"
        :depends-on NIL
        :components ((:compiled-file "profile" :pathname #P"SYS:PROFILE.FAS")))