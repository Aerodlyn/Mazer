module Mazer
    use, intrinsic :: iso_c_binding
    type, bind (C) :: ALLEGRO_COLOR
        character (c_float) :: r, g, b, a
    end type

    type, bind (C) :: Room
        logical (c_bool) :: valid
        integer (c_int16_t) :: w, h, x, y

        type (c_funptr) :: intersects
    end type

    type, bind (C) :: Tile
        logical (c_bool) :: valid
        integer (c_int16_t) :: x, y, s
        type (ALLEGRO_COLOR) :: border, fill

        type (c_funptr) :: getSize, getX, getY, destroy, getBorderColor, getFillColor
    end type
    
    interface
        integer (c_int) function rand () bind (C, name = "rand")
            use, intrinsic :: iso_c_binding
            implicit none
        end function rand

        type (ALLEGRO_COLOR) function al_map_rgb_f (r, g, b) bind (C, name = "al_map_rgb_f")
            use, intrinsic :: iso_c_binding
            import
            implicit none
        
            real (c_float) :: r, g, b
        end function al_map_rgb_f
    end interface
end module Mazer

