module ftn
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
    
    integer (c_int) :: i, j
    logical :: add = .true.
    
    do i = 0, attempts
        rooms (i * 4_c_int + 1_c_int) = mod (rand (), screenSize)
        rooms (i * 4_c_int + 2_c_int) = mod (rand (), screenSize)
        rooms (i * 4_c_int + 3_c_int) = mod (rand (), minSize) + minSize
        rooms (i * 4_c_int + 4_c_int) = mod (rand (), minSize) + minSize
    end do
end subroutine generate_rooms

