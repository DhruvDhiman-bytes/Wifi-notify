#!/bin/bash

nmcli -t -f SSID,SIGNAL,BARS dev wifi
# run nmcli and store output into array splitting on ':'
IFS=':' read -r -a INFO < <(nmcli -t -f SSID,SIGNAL,BARS dev wifi | head -1)

# print the full array
echo "Full array: ${INFO[@]}"

# print total number of elements
echo "Total elements: ${#INFO[@]}"

# access each element by index
SSID="${INFO[0]}"
SIGNAL="${INFO[1]}"
BARS="${INFO[2]}"

echo
echo "Ran the script perfectly fine"
