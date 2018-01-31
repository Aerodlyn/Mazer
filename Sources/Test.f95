program Test
    implicit none

    integer, parameter :: ROOM_POINTS = 4
    integer, allocatable :: rooms (:, :)
    integer :: i

    rooms = generateRooms (50, 10, 100, 1)
    print *, ""
    do i = 1, size (rooms) / 4
        print "(4I4)", rooms (i, :)
    end do

contains
    subroutine testFuc ()
        print *, "Hello"
    end subroutine testFuc
    
    function generateRooms (attempts, minSize, screenSize, padding) result (rooms)
        implicit none

        integer, intent (in) :: attempts, minSize, screenSize, padding
        integer :: sAttempts = 0

        integer, allocatable :: rooms (:, :)
        integer :: rooms_s (attempts, 4)

        integer :: i, j
        logical :: add = .true.
        do i = 1, attempts
            do j = 1, 4
                rooms_s (i, 1) = mod (generateRandomNumber (), screenSize)
                rooms_s (i, 2) = mod (generateRandomNumber (), screenSize)
                rooms_s (i, 3) = mod (generateRandomNumber (), minSize) + minSize
                rooms_s (i, 4) = mod (generateRandomNumber (), minSize) + minSize

                if (rooms_s (i, 1) < padding) rooms_s (i, 1) = padding

                if (rooms_s (i, 2) < padding) rooms_s (i, 2) = padding

                if (rooms_s (i, 1) + rooms_s (i, 3) > screenSize - padding) rooms_s (i, 1) = screenSize - rooms_s (i, 3)

                if (rooms_s (i, 2) + rooms_s (i, 4) > screenSize - padding) rooms_s (i, 2) = screenSize - rooms_s (i, 4)
            end do

            print *, rooms_s (i, :)
            do j = 1, i - 1
                if (rooms_s (j, 1) == -1) cycle

                if (rooms_s (i, 1) + rooms_s (i, 3) < rooms_s (j, 1) &
                    .or. rooms_s (j, 1) + rooms_s (j, 3) < rooms_s (i, 1)) then
                    add = .true.

                else if (rooms_s (i, 2) + rooms_s (i, 4) < rooms_s (j, 2) &
                    .or. rooms_s (j, 2) + rooms_s (j, 4) < rooms_s (i, 2)) then
                    add = .true.

                else
                    add = .false.
                    exit
                end if
            end do

            if (add) then
                sAttempts = sAttempts + 1

            else
                rooms_s (i, 1) = -1
            end if
        end do

        allocate (rooms (sAttempts, 4))

        j = 1
        do i = 1, attempts
            if (rooms_s (i, 1) /= -1) then
                rooms (j, :) = rooms_s (i, :)
                j = j + 1
            end if
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

