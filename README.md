## Floater - 32bit ARM floating point Operationen
__Dieses Repository enthät:__
* Selbstimplementierte Gleitkommabibliothek für 32bit, einfache Präzision _Addition, Subraktion und Multiplikation_.

* Einfache Implementation des Trapezintegrations Algorithmus, einmal unter Verwendung des integrierten FPU (_intergration_fpu.c_), und einmal unter Verwendung der selbstimplementierten Gleitkommaoperationen (_integration_i_float.c_).

Zum kompilieren ohne Optimierungen mit `make`, und um beide Varianten in allen Optimierungsstufen zu kompilieren `make full`. 

Der IEEE-754 Floating Point Calculator unter https://www.h-schmidt.net/FloatConverter/IEEE754.html ist sehr empfehlenswert um Ergebnisse in Dezimalrepresentation umzurechnen.