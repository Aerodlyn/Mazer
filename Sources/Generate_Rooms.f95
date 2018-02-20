subroutine f_generateRooms (rooms, attempts, minSize, mazeSize, padding) &
    bind (C, name = "f_generateRooms")
    
    use, intrinsic :: iso_c_binding
    use Mazer
    implicit none
    
    integer (c_int16_t), intent (in) :: attempts, minSize, mazeSize, padding
    type (Room), dimension (attempts), intent (inout) :: rooms

    integer (c_int16_t) :: i, j, x, y, w, h
    logical (c_bool) :: add = .true.
    do i = 1, attempts
        x = mod (c_rand (), mazeSize)
        y = mod (c_rand (), mazeSize)
        w = mod (c_rand (), minSize) + minSize
        h = mod (c_rand (), minSize) + minSize

        if (x < padding) x = padding
        if (y < padding) y = padding
        if (x + w > mazeSize - padding) x = mazeSize - w - padding
        if (y + h > mazeSize - padding) y = mazeSize - h - padding
       
        do j = 1, i - 1
            if (.not. rooms (j)%valid) cycle

            if (x + w < rooms (j)%x .or. rooms (j)%x + rooms (j)%w < x) then
                add = .true.
            
            else if (y + h < rooms (j)%y .or. rooms (j)%y + rooms (j)%h < y) then
                add = .true.
            
            else
                add = .false.
                exit
            end if            
        end do

        rooms (i)%x = x
        rooms (i)%y = y
        rooms (i)%w = w
        rooms (i)%h = h
        rooms (i)%valid = add
    end do
end subroutine f_generateRooms

