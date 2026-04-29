# Итоговый результат
<img width="865" height="85" alt="Снимок экрана 2026-04-29 в 21 54 29" src="https://github.com/user-attachments/assets/6e8b88f8-eda5-4944-aa08-6b1474bbf508" />



# Без оптимизаций:
<img width="908" height="300" alt="no_opt" src="https://github.com/user-attachments/assets/b0d50818-6fd0-47c3-b40f-b8e2a66903bb" />

## проблема: hash func CRC32:
<img width="908" height="300" alt="no_opt_perf" src="https://github.com/user-attachments/assets/4398cb22-03ab-4430-a8b5-9088c028715f" />


# После asm вставки crc32:
<img width="908" height="300" alt="ASM_CRC32" src="https://github.com/user-attachments/assets/15e2a9cc-f4b6-4c88-b1f6-3be6bb5a1df7" />
__________________________________________________________
<img width="337" height="546" alt="ASM_CRC32_imenno" src="https://github.com/user-attachments/assets/98e77f9c-df1b-49c2-9bb7-71fb2afe1f07" />


## Next problem: strcmp
<img width="908" height="300" alt="ASM_CRC32_perf" src="https://github.com/user-attachments/assets/e52d8cd0-e887-4f58-8b7c-5711a7d352c1" />

# после my_strcmp
<img width="908" height="291" alt="MY_STRCMP" src="https://github.com/user-attachments/assets/8ba11978-9ffa-44b3-8864-d468c2ad3ad5" />
__________________________________________________________
<img width="417" height="524" alt="MY_STRCMP_imeno" src="https://github.com/user-attachments/assets/01df907d-49ce-404f-a35c-c6c2e4df1d0c" />

## next пробуем ускорить с помощью likely/unlikely и prefetch
<img width="907" height="294" alt="prefetch" src="https://github.com/user-attachments/assets/79c78f92-254d-4e2d-a999-397223591f5c" />
__________________________________________________________
<img width="503" height="324" alt="likely_unlikely_imenno" src="https://github.com/user-attachments/assets/ec3967a0-1337-4c63-aaca-0d1e4bc3e546" />

## Также в папке dumpy/html представлены диаграммы распределения слов в хеш-таблице в зависимости от типа распределения
