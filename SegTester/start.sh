# !/bin/bash

c_datei="SegTester.c"
ausgabe_datei="SegTester"

if pgrep -x "$ausgabe_datei" > /dev/null
then
  echo "Das Programm läuft bereits."
else

  cc $c_datei -o $ausgabe_datei


  if [ $? -eq 0 ]; then
    echo "Kompilierung erfolgreich!"


    open -a iTerm "./$ausgabe_datei"
  else
    echo "Fehler bei der Kompilierung."
  fi
fi

# !/bin/bash

# c_datei="SegTester.c"
# ausgabe_datei="SegTester"

# if pgrep -x "$ausgabe_datei" > /dev/null; then
#   echo "Das Programm läuft bereits."
# else
#   gcc $c_datei -o $ausgabe_datei

#   if [ $? -eq 0 ]; then
#     echo "Kompilierung erfolgreich!"

#     # Anpassung je nach Terminal-Emulator (z.B., gnome-terminal, konsole, xterm)
#     x-terminal-emulator -e "./$ausgabe_datei"
#   else
#     echo "Fehler bei der Kompilierung."
#   fi
# fi

