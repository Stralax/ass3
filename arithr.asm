prog1 START 0
    LDT x
    LDS y
    
    .SUM
    CLEAR A
    ADDR T,A
    ADDR S,A
    STA sum
    
    .DIFF
    CLEAR A
    ADDR T,A
    SUBR S,A
    STA diff

    .PROD
    CLEAR A
    ADDR T,A
    MULR S,A
    STA prod

    .QUOT
    CLEAR A
    ADDR T,A
    DIVR S,A
    STA quot

    .MOD
    CLEAR A
    ADDR T,A
    DIVR S,A
    MULR S,A
    SUBR A,T
    STT mod
    


halt J halt

x   WORD 20
y   WORD 15
sum RESW 1
diff RESW 1
prod RESW 1
quot RESW 1
mod RESW 1

