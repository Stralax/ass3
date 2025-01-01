prog START 0 
    JSUB sinit


BERI    TD #NAPRAVA
    JEQ BERI
    RD #NAPRAVA
    SUB #48
    COMP #0
    JEQ halt
    JSUB FAKU
    STA provera
    RD #NAPRAVA
    RD #NAPRAVA
    LDA provera
    JSUB NUM
    JSUB nl
    LDA #0
    J BERI

    
halt J halt

nl  STA pomocA      .nl funkcija
    LDA #10
    WD #1
    LDA pomocA
    RSUB

FAKU    +STL @sp
        JSUB spush
        +STB @sp
        JSUB spush      .namesto STL sumL

        COMP #1
        JEQ fakuOUT
        RMO A, B    .shranimo A .... nekam
        SUB #1      .zmanjsamo A
        JSUB FAKU   .Povozi vrednost v L
        MULR B, A

fakuOUT  JSUB spop
        +LDB @sp
        JSUB spop
        +LDL @sp
        RSUB






sinit   STA stackA       .nastavi vrednost sp na zacetek stacka
    LDA #stack
    STA sp
    LDA stackA
    RSUB

spush   STA stackA       .poveca vrednost sp za eno besedo
    LDA sp
    ADD #3
    STA sp
    LDA stackA
    RSUB

spop    STA stackA        .zmanjsa vrednost sp za eno besedo
    LDA sp
    SUB #3
    STA sp
    LDA stackA
    RSUB


                .ISPiS desetiskeg stevila podaneg v registru A
NUM STA stevilo1
    STA pomocA1
    LDA #0
    STA length
    LDA #1
    STA treDelitev
    LDA stevilo1
    STL pomocL
    JSUB LEN
zaD LDA length
    COMP #1         .Dolocitev delilaca koliko je velik npr. 1000
    JEQ NAD
    LDA treDelitev
    MUL #10
    STA treDelitev
    LDA length
    SUB #1
    STA length
    J zaD
                .Nadeljevanje uzimanje cifara in priprema za ispis
NAD LDA stevilo1
    DIV treDelitev
    STA quot
    ADD #48
    WD #1           .stevilo1 = ostatku deljenja sa treDelitev
    LDA quot
    MUL treDelitev
    STA pomoc1
    LDA stevilo1
    SUB pomoc1
    STA stevilo1
    LDA treDelitev
    DIV #10
    STA treDelitev
    COMP #0
    JEQ KRAJ
    J NAD
KRAJ LDL pomocL
    LDA pomocA1
    RSUB


LEN STA stevilo     .f-ja za dolzino stevila podanega v A registru vrne njegovo dolzino v length 
    LDA #0
    STA length
LOOP    LDA stevilo 
    DIV #10
    STA stevilo
    LDA length
    ADD #1
    STA length
    LDA stevilo
    COMP #0
    JEQ VRN
    J LOOP
VRN LDA stevilo 
    RSUB 


maska WORD 0xFF
provera WORD 0x0
NAPRAVA EQU 0xFA
OUT EQU 0x1
pomocA RESW 1
pomocA1 RESW 1 
pomocL RESW 1 
length WORD 0x0
stevilo RESW 1
stevilo1 RESW 1
treDelitev WORD 0x1
cifra RESW 1
quot RESW 1
pomoc1 RESW 1

stack   RESW 1000       .pocetak steka
sp      WORD 0          .stackptr prvo prosto mesto v stacku    

stackA WORD 0

    END prog

