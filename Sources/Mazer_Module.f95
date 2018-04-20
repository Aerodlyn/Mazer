module Mazer
    use, intrinsic :: iso_c_binding
    type, bind (C) :: Room
        logical (c_bool) :: valid
        integer (c_int16_t) :: w, h, x, y

        type (c_funptr) :: intersects
    end type

    type, bind (C) :: Tile
        logical (c_bool) :: valid
        integer (c_int16_t) :: x, y, w, h
        integer (c_int8_t), dimension (4) :: border, fill

        type (c_funptr) :: getX, getY, destroy, getSize, getBorderColor, getFillColor
    end type
    
    interface
        subroutine c_mapRGB (rgb, r, g, b) bind (C, name = "c_mapRGB")
            use, intrinsic :: iso_c_binding
            implicit none

            integer (c_int8_t), dimension (*), intent (inout) :: rgb
            real (c_float), intent (in) :: r, g, b
        end subroutine c_mapRGB

        integer (c_int) function c_rand () bind (C, name = "rand")
            use, intrinsic :: iso_c_binding
            implicit none
        end function c_rand

        subroutine c_Tile_init (t, x, y, w, h) bind (C, name = "c_Tile_init")
            use, intrinsic :: iso_c_binding
            import
            implicit none

            type (Tile), intent (inout) :: t
            integer (c_int16_t), intent (in) :: x, y, w, h
        end subroutine c_Tile_init
    end interface
end module Mazer

