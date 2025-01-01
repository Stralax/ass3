#!/bin/bash

# Preveri, ali je vhodna datoteka podana kot argument
if [ -z "$1" ]; then
  echo "Uporaba: $0 <vhodna_datoteka>"
  exit 1
fi

# Preberemo vhodno datoteko in obdelamo vrstico po vrstici
input_file="$1"
output_file="Koda.txt"

# Praznemo datoteko Koda.txt, da začnemo z novo vsebino
> "$output_file"

# Preberemo vhodno datoteko vrstico po vrstici
while IFS= read -r line || [ -n "$line" ]; do

    # Odstranimo vse tabulatorje in presežke presledkov
    line=$(echo "$line" | tr -d '\t' | tr -s ' ')

    # Če vrstica začne s piko (.), jo ignoriramo
    if [[ "$line" =~ ^\..* ]]; then
        continue
    fi

    # Če vrstica vsebuje piko v sredini, odstranimo del, ki sledi piki
    line=$(echo "$line" | sed 's/\..*//')

    # Odstranimo presledke na začetku in koncu vrstice
    trimmed_line=$(echo "$line" | xargs)

    # Če je vrstica prazna po odstranitvi presledkov, jo preskočimo
    if [[ -z "$trimmed_line" ]]; then
        continue
    fi

    # Dodajamo posebne znake ( +, #, @, , ) v oklepaje, pred obdelavo besed
    line=$(echo "$line" | sed 's/\([+]\)/{\1}/g')  # + -> {+}
    line=$(echo "$line" | sed 's/\([#]\)/{\1}/g')  # # -> {#}
    line=$(echo "$line" | sed 's/\([@]\)/{\1}/g')  # @ -> {@}
    
    # DODAJ: Pred vejico v oklepaju dodamo presledek (samo če vejica ni že v oklepaju)
    line=$(echo "$line" | sed 's/\([^[:space:]]\),/\1 ,/g')  # Dodaj presledek pred vejico

    # DODAJ: Zamenjaj vejico z {,}
    line=$(echo "$line" | sed 's/,/{,}/g')  # , -> {,}

    # Spremenimo vsako besedo v {beseda}, vendar ignoriramo prazne besede
    line=$(echo "$line" | sed 's/\([^[:space:]]\+\)/{\1}/g')

    # Poskrbimo, da bo prvi del besede imel začetek { 
    line=$(echo "$line" | sed 's/} {/}/g')

    
    echo "$line" >> "$output_file"
done < "$input_file"

# Po obdelavi datoteke, zamenjamo vse '}' s '}{' 
sed -i 's/}/}{/g' "$output_file"

# Zdaj odstranimo zadnjo zaklepno figuro '}'
#sed -i 's/{$//g' "$output_file"

sed 's/[[:space:]]*$//' "$output_file" | sed 's/.$//' > temp_file && mv temp_file "$output_file"

sed 's/{{/{/g' "$output_file" | sed 's/{}//g' > temp_file && mv temp_file "$output_file"

echo "Obdelava je končana. Rezultat je shranjen v $output_file."



gcc zbirnik.c
komanda="./a.out $1"
eval $komanda









