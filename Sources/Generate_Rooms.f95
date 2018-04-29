logical function f_isRoomValid (rooms, length, n, r)
    use, intrinsic :: iso_c_binding 
    use Mazer 
    implicit none

    integer (c_int16_t), intent (in) :: length, n 
    type (Room), dimension (0 : length - 1), intent (in) :: rooms 
    type (Room), intent (in) :: r 

    integer i
    type (Room) tr
    do i = 0, n - 1
        tr = rooms (i)

        if (r%x + r%w < tr%x .or. tr%x + tr%w < r%x) then
            cycle 

        else if (r%y + r%h < tr%y .or. tr%y + tr%h < r%y) then
            cycle

        else 
            f_isRoomValid = .false.
            return
        end if
    end do

    f_isRoomValid = .true.
end function f_isRoomValid

type (Room) function f_generateRoom (minSize)
    use, intrinsic :: iso_c_binding 
    use Mazer 
    implicit none
    
    integer (c_int16_t), intent (in) :: minSize
    integer (c_int16_t) :: x, y, w, h 

    x = mod (c_rand (), NUM_OF_TILES_PER_SIDE)
    y = mod (c_rand (), NUM_OF_TILES_PER_SIDE)
    w = mod (c_rand (), minSize) + minSize
    h = mod (c_rand (), minSize) + minSize

    if (x < WINDOW_PADDING) x = WINDOW_PADDING
    if (y < WINDOW_PADDING) y = WINDOW_PADDING
    if (x + w > NUM_OF_TILES_PER_SIDE - WINDOW_PADDING) x = NUM_OF_TILES_PER_SIDE - w - WINDOW_PADDING
    if (y + h > NUM_OF_TILES_PER_SIDE - WINDOW_PADDING) y = NUM_OF_TILES_PER_SIDE - h - WINDOW_PADDING

    f_generateRoom%x = x 
    f_generateRoom%y = y
    f_generateRoom%w = w
    f_generateRoom%h = h 
end function f_generateRoom

subroutine f_generateRooms (tiles, length, attempts, minSize) bind (C, name = "f_generateRooms")
    use, intrinsic :: iso_c_binding 
    use Mazer
    use Generate_Tiles 
    implicit none

    logical, external :: f_isRoomValid
    type (Room), external :: f_generateRoom

    integer (c_int16_t), intent (in) :: attempts, minSize
    integer (c_int32_t), intent (in) :: length 
    type (Tile), dimension (0 : length - 1), intent (inout) :: tiles

    type (Room), dimension (0 : attempts - 1) :: rooms
    type (Room) :: tr
    integer (c_int16_t) :: i, n 

    do i = 0, attempts
        tr = f_generateRoom (minSize)

        if (f_isRoomValid (rooms, attempts, n, tr)) then
            rooms (n) = tr 
            call f_generateTiles (tiles, length, tr%x, tr%y, tr%w, tr%h)

            n = n + 1
        end if
    end do
end subroutine f_generateRooms
