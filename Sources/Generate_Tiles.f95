module Generate_Tiles
    contains
        subroutine f_generateTiles (tiles, length, x, y, w, h) bind (C, name = "f_generateTiles")
            use, intrinsic :: iso_c_binding
            use Mazer
            implicit none

            integer (c_int16_t), intent (in) :: x, y, w, h
            integer (c_int32_t), intent (in) :: length
            type (Tile), dimension (0 : length - 1), intent (inout) :: tiles

            integer :: i, j
            type (Tile) :: t
            do i = 0, w - 1
                do j = 0, h - 1 
                    call Tile_init (tiles ((x + i) + NUM_OF_TILES_PER_SIDE * (y + j)))
                end do
            end do 
        end subroutine f_generateTiles
end module Generate_Tiles
