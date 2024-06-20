#!/usr/bin/env bash
###################################
#         CCalc Installer         #
###################################

echo "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#"
echo "#                -- [ CCalc Installer ] --                  #"
echo "#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#"

printf "\nWould you like to remove README.md?\n"
read -r ask_remove_readme

while true
do
  case $ask_remove_readme in
      [Yy]* )
          rm README.md
          break ;;
      [Nn]* )
        echo "README.md not removed."
        break ;;
      * )
        echo "Invalid input."
  esac
done

make
