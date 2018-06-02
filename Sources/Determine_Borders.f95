subroutine f_determineBorders (tiles, length) bind (C, name = "f_determineBorders")
    use, intrinsic :: iso_c_binding
    use Mazer
    implicit none

    integer (c_int32_t), intent (in) :: length 
    type (Tile), dimension (0 : length - 1), intent (inout) :: tiles

    integer (c_int32_t) :: i, c, r
    do i = 0, length - 1
        c = modulo (i, NUM_OF_TILES_PER_SIDE)
        r = i / NUM_OF_TILES_PER_SIDE

        if (c > 0) then
            if (.not. tiles (i - 1)%valid) tiles (i)%borders = IOR (tiles (i)%borders, LEFT)
        else
            tiles (i)%borders = IOR (tiles (i)%borders, LEFT)
        end if 

        if (c < NUM_OF_TILES_PER_SIDE - 1) then
            if (.not. tiles (i + 1)%valid) tiles (i)%borders = IOR (tiles (i)%borders, RIGHT)
        else
            tiles (i)%borders = IOR (tiles (i)%borders, RIGHT)
        end if 

        if (r > 0) then
            if (.not. tiles (i - NUM_OF_TILES_PER_SIDE)%valid) tiles (i)%borders = IOR (tiles (i)%borders, TOP)
        else
            tiles (i)%borders = IOR (tiles (i)%borders, TOP)
        end if 

        if (r < NUM_OF_TILES_PER_SIDE - 1) then 
            if (.not. tiles (i + NUM_OF_TILES_PER_SIDE)%valid) tiles (i)%borders = IOR (tiles (i)%borders, BOTTOM)
        else
            tiles (i)%borders = IOR (tiles (i)%borders, BOTTOM)
        end if
    end do
end subroutine f_determineBorders
