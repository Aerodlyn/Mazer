module Mazer
    use, intrinsic :: iso_c_binding
    implicit none

    integer (c_int8_t), bind (C, name = "WINDOW_PADDING") :: WINDOW_PADDING
    integer (c_int16_t), bind (C, name = "NUM_OF_TILES_PER_SIDE") :: NUM_OF_TILES_PER_SIDE
    integer (c_int16_t), bind (C, name = "WINDOW_HEIGHT") :: WINDOW_HEIGHT 
    integer (c_int16_t), bind (C, name = "WINDOW_WIDTH") :: WINDOW_WIDTH
    integer (c_int32_t), bind (C, name = "NUM_OF_TILES") :: NUM_OF_TILES

    type, bind (C) :: SDL_Color 
        character (c_char) :: r, g, b, a
    end type

    type, bind (C) :: Room
        logical (c_bool) :: valid
        integer (c_int16_t) :: w, h, x, y

        type (c_funptr) :: intersects
    end type

    type, bind (C) :: Tile
        logical (c_bool) :: valid
        integer (c_int16_t) :: x, y, w, h
        type (SDL_Color) :: border, fill

        type (c_funptr) :: getX, getY, destroy, getSize, getBorderColor, getFillColor
    end type
    
    interface
        subroutine c_mapRGB (rgb, r, g, b) bind (C, name = "c_mapRGB")
            use, intrinsic :: iso_c_binding
            import
            implicit none

            type (Tile), intent (inout) :: rgb
            real (c_float), intent (in) :: r, g, b
        end subroutine c_mapRGB

        integer (c_int) function c_rand () bind (C, name = "rand")
            use, intrinsic :: iso_c_binding
            implicit none
        end function c_rand

        subroutine Tile_init (t) bind (C, name = "Tile_init")
            use, intrinsic :: iso_c_binding
            import
            implicit none

            type (Tile), intent (inout) :: t
        end subroutine Tile_init
    end interface

    contains 
        subroutine f_init () bind (C, name = "f_init") 
            use, intrinsic :: iso_c_binding
            implicit none

            WINDOW_WIDTH = 550_c_int16_t
            WINDOW_HEIGHT = WINDOW_WIDTH

            NUM_OF_TILES_PER_SIDE = 50_c_int16_t
            NUM_OF_TILES = NUM_OF_TILES_PER_SIDE ** 2

            WINDOW_PADDING = 1_c_int8_t
        end subroutine f_init
end module Mazer

