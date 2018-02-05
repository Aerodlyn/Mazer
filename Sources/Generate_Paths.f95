subroutine f_generatePaths (tiles, perSide, attempts) bind (C, name = "f_generatePaths")
    use, intrinsic :: iso_c_binding
    use Mazer
    implicit none

    integer (c_int16_t), intent (in) :: perSide, attempts
    type (Tile), dimension (perSide * perSide), intent (inout) :: tiles

    integer (c_int16_t) :: i, x, y, tx, ty
    do i = 0, attempts - 1
        
    end do
end subroutine f_generatePaths
