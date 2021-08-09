
(defsystem "cl-simd" :class asdf::prebuilt-system
        :lib #P"SYS:CL-SIMD.LIB"
        :depends-on NIL
        :components ((:compiled-file "cl-simd" :pathname #P"SYS:CL-SIMD.FAS")))