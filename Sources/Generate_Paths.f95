subroutine f_generatePaths (tiles, length, attempts) bind (C, name = "f_generatePaths")
    use, intrinsic :: iso_c_binding
    use Mazer
    use Generate_Tiles
    implicit none
    
    integer (c_int16_t), intent (in) :: attempts
    integer (c_int32_t), intent (in) :: length
    type (Tile), dimension (0 : length - 1), intent (inout) :: tiles

    integer :: i, r
    integer (c_int16_t) :: x, y, w, h
    do i = 0, attempts - 1
        r = modulo (c_rand (), NUM_OF_TILES)

        if (.not. tiles (r)%valid) then
            x = modulo (r, NUM_OF_TILES_PER_SIDE)
            y = r / NUM_OF_TILES_PER_SIDE
            w = modulo (c_rand (), NUM_OF_TILES_PER_SIDE / 7)
            h = modulo (c_rand (), NUM_OF_TILES_PER_SIDE / 7)

            call f_generateTiles (tiles, length, x, y, w, w)
        end if
    end do
end subroutine f_generatePaths
