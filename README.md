# Teksto analizė

Programa nuskaito tekstą iš failo ir išveda tris rezultatus:
- kiek kartų kiekvienas žodis pasikartoja tekste
- kuriose eilutėse kiekvienas žodis buvo paminėtas (cross-reference)
- visus rastus URL adresus

## Kompiliavimas

Reikia CMake ir C++17 palaikančio kompiliatoriaus.

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Paleidimas

Tekstą reikia įdėti į `data/tekstas.txt`, tada paleisti:

```
./TextAnalize
```

arba Windows:

```
TextAnalize.exe
```

Programa sukuria tris failus `output/` aplanke:
- `zodziu_daznis.txt` - žodžiai kurie pasikartojo daugiau nei kartą ir kiek kartų
- `cross_reference.txt` - kuriose eilutėse kiekvienas žodis buvo
- `url_adresas.txt` - rasti URL adresai

## Testai

```
./Testai
```

## Pastabos

Skyrybos ženklai (taškai, kableliai ir pan.) yra pašalinami prieš skaičiuojant žodžius.
Žodžiai paverčiami mažosiomis raidėmis, todėl "The" ir "the" laikomi tuo pačiu žodžiu.
