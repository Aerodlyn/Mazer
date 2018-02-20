module Mazer
    use, intrinsic :: iso_c_binding
    type, bind (C) :: ALLEGRO_COLOR
        real (c_float) :: r, g, b, a
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
        integer (c_int) function c_rand () bind (C, name = "rand")
            use, intrinsic :: iso_c_binding
            implicit none
        end function c_rand
    end interface
    
    contains
        type (ALLEGRO_COLOR) function al_map_rgb_f (r, g, b)
            use, intrinsic :: iso_c_binding
            implicit none
        
            real (c_float), intent (in) :: r, g, b

            al_map_rgb_f%r = r 
            al_map_rgb_f%g = g 
            al_map_rgb_f%b = b 
            al_map_rgb_f%a = 1.0_c_float
        end function al_map_rgb_f
end module Mazer

