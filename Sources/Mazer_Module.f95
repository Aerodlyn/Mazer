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
        integer (c_int) function rand () bind (C, name = "rand")
            use, intrinsic :: iso_c_binding
            implicit none
        end function rand

        type (ALLEGRO_COLOR) function al_map_rgb (r, g, b) bind (C, name = "al_map_rgb")
            use, intrinsic :: iso_c_binding
            import
            implicit none
        
            integer (c_signed_char) :: r, g, b
        end function al_map_rgb

        type (ALLEGRO_COLOR) function al_map_rgb_f (r, g, b) bind (C, name = "al_map_rgb_f")
            use, intrinsic :: iso_c_binding
            import
            implicit none
        
            real (kind = 4) :: r, g, b
        end function al_map_rgb_f

        logical function f_validStarter (tiles, x, y, perSide, padding)
            use, intrinsic :: iso_c_binding
            use Mazer
            implicit none
            
            integer (c_int16_t), intent (in) :: x, y, perSide
            integer (c_int8_t), intent (in) :: padding
            type (Tile), dimension (perSide * perSide), intent (in) :: tiles
            
            f_validStarter = .false.
            if (.not. tiles ((x + perSide * y) + 1_c_int16_t)%valid) then
                f_validStarter = .false.
            
            else
                if (x > padding + 1_c_int8_t) then
                    if (.not. tiles (((x - 1_c_int16_t) + perSide * y) + 1_c_int16_t)%valid) f_validStarter = .true.
                end if
            
                if (x < perSide - padding - 1_c_int8_t) then
                    if (.not. tiles (((x + 1_c_int16_t) + perSide * y) + 1_c_int16_t)%valid) f_validStarter = .true.
                end if
            
                if (y > padding + 1_c_int8_t) then
                    if (.not. tiles ((x + perSide * (y - 1_c_int16_t)) + 1_c_int16_t)%valid) f_validStarter = .true.
                end if
            
                if (y < perSide - padding - 1_c_int8_t) then
                    if (.not. tiles ((x + perSide * (x + 1_c_int16_t)) + 1_c_int16_t)%valid) f_validStarter = .true.
                end if
            end if 
        end function f_validStarter
    end interface
end module Mazer

