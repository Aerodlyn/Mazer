module Mazer
    use, intrinsic :: iso_c_binding
    type, bind (C) :: Room
        logical (c_bool) :: valid
        integer (c_int16_t) :: w, h, x, y

        type (c_funptr) :: intersects
    end type
    
    interface
        integer (c_int) function rand () bind (C, name = "rand")
            use, intrinsic :: iso_c_binding
            implicit none
        end function rand
    end interface
end module Mazer

