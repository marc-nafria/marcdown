# marcdown
A Markdown terminal viewer
---
![imagen](https://user-images.githubusercontent.com/104323247/194083369-9344d0dd-50b6-403a-a450-ea6f00311f79.png)

# Index

+ 1. Titols
+ 2. Comentaris
+ 3. Enumeracions
+ 4. Format de linea
++ 4.1 Codi
++ 4.2 Negreta
+ 5. Separadors

---

# 1. Titols

Per posar un titol cal usar el caracter `#` al principi de una nova línea. S'indentara el titol en funcio de quants `#` es posin: `## Aixó serà un subtitol`.

## Això serà un subtitol

---

# 2. Comentaris

Per posar un comentari cal usar el caracter `>` al principi de una nova línea. Si el comentari durà més d'una linea cal posar `>` a totes les línes:

`> Aixo serà un comentari`

> Aixo serà un comentari

---

# 3. Enumeracions

Per posar una numeració cal usar el caracter `+` al principi de cada item. S'identara en funcio del numero de `+` que es posin.

`+ item1`
`+ item2`
`++ item2.1`
`++ item2.2`
`+ item3`

+ item1
+ item2
++ item2.1
++ item2.2
+item3

---

# 4. Format de línea

## 4.1 Codi

Per posar un fragment de codi en mig d'una linea cal usar el caracter reservat \` i escriure el codi. S'ha de acabar amb un altre cop el caracter \`.

`\`int main()\``

`int main()`

## 4.2 Negreta

El funcionament és igual que amb el codi pero amb un doble caracter \*\*.

`\*\*negreta\*\*`

**negreta**

> Per poder posar els caracters **\\, \*, \`** s'ha de utilitzar la barra enrrere abans: `\\\\, \\\*, \\\``.
___

# 5. Separadors

Per posar un separador en una linea cal escriure **només** tres caracter de resta: `---`
