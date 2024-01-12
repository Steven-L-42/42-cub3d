# !/bin/bash

c_datei="SegTester.c"
ausgabe_datei="SegTester"

if pgrep -x "$ausgabe_datei" > /dev/null
then
  echo "[!!] cub3d is already running."
else

  cc $c_datei -o $ausgabe_datei


  if [ $? -eq 0 ]; then
    echo "[OK] Compilation completed!"


    open -a iTerm "./$ausgabe_datei"
  else
    echo "[KO] Compilation issue!"
  fi
fi

# !/bin/bash

# c_datei="SegTester.c"
# ausgabe_datei="SegTester"

# if pgrep -x "$ausgabe_datei" > /dev/null; then
#   echo "[!!] cub3d is already running."
# else
#   gcc $c_datei -o $ausgabe_datei

#   if [ $? -eq 0 ]; then
#     echo "[OK] Compilation completed!"

#     # Anpassung je nach Terminal-Emulator (z.B., gnome-terminal, konsole, xterm)
#     x-terminal-emulator -e "./$ausgabe_datei"
#   else
#     echo "[KO] Error: Compilation issue!"
#   fi
# fi

