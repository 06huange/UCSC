.text
.global fill_bitmap

#*****************************************************
# fill_bitmap: 
#  Given a color, will fill the bitmap display with that color.
#-----------------------------------------------------
#   Inputs:
#           a0 = 8 bit color value
#   Outputs:
#           No register outputs
#*****************************************************
fill_bitmap:

    #read in 8 bit color
    #apply color to 1024 bytes after base address 0x00000C00
    addi x2, x0, 0xc
    slli x2, x2, 8
    addi x3, x2, 0
    addi x4, x0, 1028
    addi x5, x0, 0
    fill:
    blt x4, x5, end # ifx4 <x31 then target
    sb x10, 0(x3)
    addi x3, x3, 1
    addi x5, x5, 1
    jal x0, fill

    
    end:
        jr      ra
