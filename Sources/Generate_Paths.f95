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
    
        if (x < perSide - padding - 2_c_int8_t) then
            if (.not. tiles (((x + 1_c_int16_t) + perSide * y) + 1_c_int16_t)%valid) f_validStarter = .true.
        end if

        if (y > padding + 1_c_int8_t) then
            if (.not. tiles ((x + perSide * (y - 1_c_int16_t)) + 1_c_int16_t)%valid) f_validStarter = .true.
        end if
    
        if (y < perSide - padding - 2_c_int8_t) then
            if (.not. tiles ((x + perSide * (y + 1_c_int16_t)) + 1_c_int16_t)%valid) f_validStarter = .true.
        end if
    end if 
end function f_validStarter

! Try picking a tile that has one or more empty neighbors, and move mostly in a straight line
!   until you hit another tile.
subroutine f_generatePaths (tiles, perSide, attempts, padding) bind (C, name = "f_generatePaths")
    use, intrinsic :: iso_c_binding
    use Mazer
    implicit none
    logical, external :: f_validStarter

    integer (c_int16_t), intent (in) :: perSide, attempts
    integer (c_int8_t), intent (in) :: padding
    type (Tile), dimension (perSide * perSide), intent (inout) :: tiles

    integer (c_int16_t) :: i, x, y, w = 1_c_int16_t, h = 1_c_int16_t
    type (Tile) :: t
    do i = 1, attempts
        x = mod (c_rand (), perSide)
        y = mod (c_rand (), perSide)

        if (x < padding) x = padding
        if (y < padding) y = padding
        if (x > perSide - padding - 1) x = perSide - padding - 1_c_int16_t
        if (y > perSide - padding - 1) y = perSide - padding - 1_c_int16_t

        if (.true.) then
            t = tiles ((x + perSide * y) + 1_c_int8_t)

            call Tile_init (t)
            !call c_mapRGB (t%fill, 0.5_c_float, 1.0_c_float, 1.0_c_float)
            !call c_mapRGB (t%border, 1.0_c_float, 1.0_c_float, 1.0_c_float)

            tiles ((x + perSide * y) + 1_c_int8_t) = t
        end if
    end do
end subroutine f_generatePaths
