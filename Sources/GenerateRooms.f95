module ftn
    use, intrinsic :: iso_c_binding
    type, bind (C) :: room
        integer (c_int) w, h, x, y
    end type

    type, bind (C) :: tile
        integer (c_int) x, y, size_s
    end type
    
    interface
        integer (c_int) function rand () bind (C, name="rand")
            use, intrinsic :: iso_c_binding
            implicit none
        end function rand
    end interface
end module ftn

subroutine generate_rooms (rooms, attempts, minSize, screenSize, padding) bind (C, name="generate_rooms")
    use, intrinsic :: iso_c_binding, only: c_int
    use ftn
    implicit none    
    
    integer (kind = c_int), intent (in) :: attempts, minSize, screenSize, padding
    integer (kind = c_int), intent (inout), dimension (attempts * 4_c_int) :: rooms
    integer :: sAttempts = 0
    
    integer (c_int) :: i, j, x, y, w, h, rx, ry, rw, rh
    logical :: add = .true.
    
    do i = 0, attempts - 1
        x = mod (rand (), screenSize)
        y = mod (rand (), screenSize)
        w = mod (rand (), minSize) + minSize
        h = mod (rand (), minSize) + minSize
       
        if (x < padding) x = padding
        if (y < padding) y = padding
        if (x + w > screenSize - padding) x = screenSize - w - padding
        if (y + h > screenSize - padding) y = screenSize - h - padding

        do j = 0, i - 1
            rx = rooms (j * 4_c_int + 1_c_int)
            ry = rooms (j * 4_c_int + 2_c_int)
            rw = rooms (j * 4_c_int + 3_c_int)
            rh = rooms (j * 4_c_int + 4_c_int)
        
            if (rx == -1) cycle

            if (x + w < rx .or. rx + rw < x) then
                add = .true.
            
            else if (y + h < ry .or. ry + rh < y) then
                add = .true.
            
            else
                add = .false.
                exit
            end if            
        end do

        rooms (i * 4_c_int + 1_c_int) = x
        rooms (i * 4_c_int + 2_c_int) = y
        rooms (i * 4_c_int + 3_c_int) = w
        rooms (i * 4_c_int + 4_c_int) = h

        if (.not. add) rooms (i * 4_c_int + 1_c_int) = -1
    end do

    print "(4I4)", rooms
end subroutine generate_rooms

subroutine test_rooms (proom) bind (C, name = "test_rooms")
    use, intrinsic :: iso_c_binding, only: c_int
    use ftn
    implicit none

    type (room) :: proom
    print *, proom%x
end subroutine test_rooms

subroutine test_tile (tile_p) bind (C, name = "test_tile")
    use, intrinsic :: iso_c_binding
    use ftn

    type (tile) :: tile_p
    print *, tile_p%size_s
end subroutine test_tile
