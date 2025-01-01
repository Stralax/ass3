prog1 START 0
    .SUM
    LDA x 
    ADD y
    STA sum

    .DIFF
    LDA x
    SUB y
    STA diff .alo kume

    .PROD
    LDA x
    MUL y  
    STA prod

    .QUOT
    LDA x
    DIV y
    STA quot

    .MOD
    LDA quot
    MUL y
    STA pomoc
    LDA x
    SUB pomoc
    STA mod
    



halt J halt

x   WORD 5
y   WORD 3
sum RESW 1
diff RESW 1
prod RESW 1
quot RESW 1
mod RESW 1
pomoc RESW 1
