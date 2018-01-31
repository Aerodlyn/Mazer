program Test
    implicit none

    integer, parameter :: ATTEMPTS = 5
    integer, parameter :: ROOM_POINTS = 4

    integer :: roomsGenerated
    integer :: rooms (5, 4) = 0
 
    roomsGenerated = generateRooms (rooms)
    
contains
    integer function generateRooms (rooms)
        implicit none

        integer, intent (inout) :: rooms (:, :)

        integer :: i, j
        do i = 1, ATTEMPTS
            do j = 1, ROOM_POINTS
                rooms (i, j) = mod (generateRandomNumber (), 900)
            end do
            
            print *, rooms (i, :)
        end do
    end function generateRooms

    integer function generateRandomNumber ()
        INTEGER, PARAMETER :: n = 1000
        INTEGER :: i
        REAL :: array(n), pi, temp, mean = 1.0, sd = 0.5

        pi = 4.0*ATAN(1.0)
        CALL RANDOM_NUMBER(array) ! Uniform distribution
     
        DO i = 1, n-1, 2
            temp = sd * SQRT(-2.0*LOG(array(i))) * COS(2*pi*array(i+1)) + mean
            array(i+1) = sd * SQRT(-2.0*LOG(array(i))) * SIN(2*pi*array(i+1)) + mean
            array(i) = temp
        END DO
     
        mean = SUM(array)/n
        generateRandomNumber = irand (int (mean * 5000))
    end function generateRandomNumber
end program Test

