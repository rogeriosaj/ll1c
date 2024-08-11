@@ Gramatica

```sh
E=TX
X=+TX | X=@
T=FY
Y=*FY | Y=@
F=(E) | F=id
```

@@ Tabela M

```sh
  ======================================================================================================
          |       +               *               (               )               i               $
  ======================================================================================================
     E    |                                       E=TX                            E=TX
  ------------------------------------------------------------------------------------------------------
     X    |       X=+TX                                           X=@                             X=@
  ------------------------------------------------------------------------------------------------------
     T    |                                       T=FY                            T=FY
  ------------------------------------------------------------------------------------------------------
     Y    |       Y=@             Y=*FY                           Y=@                             Y=@
  ------------------------------------------------------------------------------------------------------
     F    |                                       F=(E)                           F=id
  ------------------------------------------------------------------------------------------------------
```

@@ Entrada

```sh
(i+i)*i$
```