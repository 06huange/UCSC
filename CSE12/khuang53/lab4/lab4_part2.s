.text
.global draw_pixel

#*****************************************************
# draw_pixel:
#  Given a coordinates y (row) in a1, and x (col) in
#  a2 sets corresponding value in memory to the color 
#  given by a0	
#-----------------------------------------------------
#   Inputs:
#           a0 = 8 bit color value
#           a1 = y coordinate of pixel in format
#           a2 = x coordinate of pixel in format
#   Outputs:
#           No register outputs
#*****************************************************
draw_pixel:

    #0b0101111
    addi x2, x0, 0xc
    slli x2, x2, 8
    addi x3, x2, 0
    addi x4, x0, 0
    addi x13, x0, 0
    find_pixel:
    blt x12, x4, draw # ifx12 < t1 then target
    add x13, x13, 32
    addi x4, x4, 1
    jal x0, find_pixel
    draw:
    add x13, x13, x11
    add x3, x3, x13
    sb x10, 0(x3)
    
    jr ra
    