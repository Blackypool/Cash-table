section .text

global M_strcmp_

;===============M_strcmp_==============my_style====

;   Entry:      rdi = ptr || rsi = ptr
;   Exit:       1 = strcmp good         0 = strcmp fail = AX
;   Expected:   Entry
;   Destr:      xmm0, xmm1, eax

;=====================================================

M_strcmp_:
;{
    xor eax, eax

    start_chech:
    
    movdqu xmm0, [rdi]
    movdqu xmm1, [rsi]


    ; unsigned char = 00
    ; strcmp = 10
    ; negative finder = 01 check differents not equaly
    ; give first differens letter = 0
    pcmpistri xmm0, xmm1, 0x18        ; eCX = first dif or /0 = 0b00011000  // 16символов || цикл 
    ; ZF = 1 <=> xmm0 E /0
    ; CF = 1 <=> xmm1 E /0
    ; SF = 1 <=> str not equal

    js str_not_equal
    jz equal                            ; ZF = 1 => дошли до /0

    add rsi, 16            ; пока что равны но еще не конец
    add rdi, 16
    jmp start_chech

    equal:
    inc eax

    str_not_equal:
    
    ret
;}
;_____________________________________________________



;===============mine_strlen==============my_style====

;   Entry:      rdi = ptr || rsi = ptr
;   Exit:       0 = strcmp good         -1 = strcmp fail = AX
;   Expected:   Entry
;   Destr:      xmm0, xmm1, rax

;=====================================================

;mine_strlen:
;{
;    pxor xmm0, xmm0
;    movdqu xmm1, [rdi]

    ;pcmpistri xmm0, xmm1, 0x08      ; <=> check where /0

    ;eCX = where /0
    ; сдвигать вправо на проверку того 16 ли символов или больше?
;}
;_____________________________________________________