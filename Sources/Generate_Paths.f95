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

    integer (c_int16_t) :: i, x, y
    do i = 1, attempts
        x = mod (c_rand (), perSide)
        y = mod (c_rand (), perSide)

        if (x < padding) x = padding
        if (y < padding) y = padding
        if (x > perSide - padding - 1) x = perSide - padding - 1_c_int16_t
        if (y > perSide - padding - 1) y = perSide - padding - 1_c_int16_t

        if (f_validStarter (tiles, x, y, perSide, padding)) then
            tiles ((x + perSide * y) + 1_c_int16_t)%fill = al_map_rgb_f (0.0_c_float, 0.0_c_float, 1.0_c_float)
            tiles ((x + perSide * y) + 1_c_int16_t)%border = al_map_rgb_f (1.0_c_float, 1.0_c_float, 1.0_c_float)
        end if
    end do

    !integer (c_int) :: dir, odir
    !integer (c_int16_t) :: i, x, y
    !do i = 1, attempts
        !x = mod (c_rand (), perSide)
        !y = mod (c_rand (), perSide)

        !if (x < padding) x = padding
        !if (y < padding) y = padding
        !if (x > perSide - padding - 1) x = perSide - padding - 1_c_int16_t
        !if (y > perSide - padding - 1) y = perSide - padding - 1_c_int16_t

        !do while (.not. tiles ((x + perSide * y) + 1)%valid)
            !tiles ((x + perSide * y) + 1)%x = x
            !tiles ((x + perSide * y) + 1)%y = y
            !tiles ((x + perSide * y) + 1)%s = 1
            !tiles ((x + perSide * y) + 1)%border = al_map_rgb_f (1.0_c_float, 1.0_c_float, 1.0_c_float)
            !tiles ((x + perSide * y) + 1)%fill = al_map_rgb_f (0.0_c_float, 0.0_c_float, 1.0_c_float)
            !tiles ((x + perSide * y) + 1)%valid = .true.

            !dir = mod (c_rand (), 4_c_int)
            !do while (dir == odir)
                !dir = mod (c_rand (), 4_c_int)
            !end do

            !odir = mod (dir + 2_c_int, 4_c_int)

            !select case (dir)
                !case (0)
                    !x = x + 1_c_int16_t
                    !if (x > perSide - padding - 1) x = x - 1_c_int16_t
                !case (1)
                    !y = y + 1_c_int16_t
                    !if (y > perSide - padding - 1) y = y - 1_c_int16_t
                !case (2)
                    !x = x - 1_c_int16_t
                    !if (x < padding) x = x + 1_c_int16_t
                !case (3)
                    !y = y - 1_c_int16_t
                    !if (y < padding) y = y + 1_c_int16_t
            !end select
        !end do
    !end do
end subroutine f_generatePaths
