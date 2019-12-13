make ; clear
echo -e "\e[1m\x1B[34mmy .cor:\x1B[37m\e[0m"
./asm $1 && hexdump -C $2
echo -e "\n\n\n\e[1m\x1B[31mref .cor:\x1B[37m\e[0m"
./asm_ref $1 && hexdump -C $2
