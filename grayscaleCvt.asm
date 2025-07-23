section .data
scaleFactor dd 255.0    ; constant 255.0 for conversion (i = f * 255.0)

section .text
bits 64
default rel

global imgCvtGrayFloatToInt

; void imgCvtGrayFloatToInt(float* inputImage, uint8_t* outputImage, int width, int height)
; RCX = inputImage (float*)
; RDX = outputImage (uint8_t*)
; R8  = width
; R9  = height

imgCvtGrayFloatToInt:
    push rbp
    mov rbp, rsp
    push rsi
    push rdi
    push rbx

    ; Setup
    mov rsi, rcx        ; rsi = inputImage pointer
    mov rdi, rdx        ; rdi = outputImage pointer
    mov eax, r8d        ; eax = width
    imul eax, r9d       ; eax = width * height
    mov ecx, eax        ; ecx = total number of pixels (loop counter)

    ; Load 255.0f into xmm1 once
    movss xmm1, dword [scaleFactor]

loopConversion:
    test ecx, ecx
    jz done

    ; Load float pixel into xmm0
    movss xmm0, dword [rsi]
    mulss xmm0, xmm1              ; xmm0 = pixel * 255.0
    cvttss2si eax, xmm0            ; eax = (int)(pixel * 255.0) + convert with truncate

    ; Clamp to [0, 255]
    cmp eax, 255
    jle store
    mov eax, 255

store:
    cmp eax, 0
    jge write
    xor eax, eax

write:
    mov byte [rdi], al            ; store into outputImage[i]

    add rsi, 4                    ; next float
    inc rdi                       ; next byte
    dec ecx
    jmp loopConversion

done:
    pop rbx
    pop rdi
    pop rsi
    pop rbp
    ret
