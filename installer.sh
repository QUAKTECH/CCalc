#!/usr/bin/bash
###################################
#         CCalc Installer         #
###################################

echo "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#"
echo "#                -- [ CCalc Installer ] --                  #"
echo "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#"

function prompt_delete_file() {
    local file=$1
    local choice=1
    while true; do
        clear
        echo "Do you want to delete $file?"
        if [ $choice -eq 1 ]; then
            echo "> Yes"
            echo "  No - Recommended"
        else
            echo "  Yes"
            echo "> No - Recommended"
        fi

        read -rsn1 input
        case $input in
            $'\x1b')
                read -rsn2 -t 0.1 input
                if [ "$input" == "[A" ]; then
                    choice=1
                elif [ "$input" == "[B" ]; then
                    choice=2
                fi
                ;;
            '')
                if [ $choice -eq 1 ]; then
                    rm -f $file
                    echo "$file deleted."
                    sleep 1
                    return 0
                else
                    echo "$file not deleted."
                    sleep 1
                    return 1
                fi
                ;;
        esac
    done
}

prompt_delete_file "README.md"
prompt_delete_file "ccalc.c"

make
