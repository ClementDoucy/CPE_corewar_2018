##
## EPITECH PROJECT, 2019
## CPE_corewar_2018
## File description:
## asm_tester
##

make -C ../asm/ > /dev/null
make -C ../asm/ clean > /dev/null
mv ../asm/asm ./asm_binaries/

source ./utils/colors.sh

for file in ./champions/*.s
do
    if [[ -f $file ]]; then

        ./asm $file &> /dev/null
        exit_asm=$?
        if [ $exit_asm == 0 ]; then
            tmp=(./*.cor)
            first_file=$(echo $tmp)
            mv $first_file test.cor
        fi

        ./asm_subject $file &> /dev/null
        exit_asm_subject=$?
        if [ $exit_asm_subject == 0 ]; then
            second_file=$(find -iname '*.cor' -not -name test.cor)
        fi

        if [ $exit_asm != $exit_asm_subject ]; then
            echo -e "[${RED}FAILURE RETURN${NC}] Wrong error gesture on: $file (My:$a, Good one:$b)"
            rm -rf *.cor
            continue
        fi

        exit_status=`expr $exit_asm + $exit_asm_subject`
        if [ $exit_status != 0 ]; then
            rm -rf *.cor
            continue
        fi

        if [ "$first_file" != "$second_file" ]; then
            echo -e "[${RED}FAILURE FILENAME${NC}] Wrong name given to: $file (My:$first_file, Good one:$second_file)"
            rm -rf *.cor
            continue
        fi

        `hexdump -C test.cor > tmp_a`
        `hexdump -C $second_file > tmp_b`

        diff tmp_a tmp_b > /dev/null
        cmp=$?

        if [ $cmp != 0 ]; then
            echo -e "[${RED}FAILURE HEXDUMP${NC}] Wrong hexdump from: $file"
        fi
        rm -rf *.cor
    fi
done

rm -rf ./asm_binaries/asm
rm -rf ./*.cor
rm -rf tmp_a tmp_b
