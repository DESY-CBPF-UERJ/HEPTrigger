# HEPTrigger
Cálculo da eficiência de trigger.
#Setup
Baixe esse repositório com:

```bash
git clone https://github.com/DESY-CBPF-UERJ/HEPTrigger.git
```

#Modificações que devem ser feitas

O framework consiste de duas macros (conversion.C e TrigEffStudy.C), somente é necessário alterar o conversion.C, na linha 62, onde é delcrado o char com o
diretório onde os datasets estão.

``` const char dirname[48] = "/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files"; ```

#Rodando as macros
Há uma ordem que deve ser seguida na execução das macros, sendo ela Conversion.C->TrigEffStudy.C. Para rodar a macro Conversion.C, execute no terminal a seguinte
linha
``` root Conversion.C```
Os seguintes avisos são comuns
```Warning in <TFile::Init>: file Tree.root probably not closed, trying to recover
Warning in <TFile::Init>: no keys recovered, file has been made a Zombie
```
Ao final da execução você deve ter, além dos warnings, um output parecido com
95
Numero de eventos: 242422
```
No caso, passaram 95 files, que juntos contém 242422 entradas.
Para rodar a macro TrigEffStudy.C, execute os seguintes comandos
```
root -l
.L trigEffStudy.C++
trigEffStudy("", "false","", "true", YEAR) # for Data; YEAR = [2016, 2017, 2018]
trigEffStudy("", "true", "", "true", YEAR) # for MC;   YEAR = [2016, 2017, 2018]
```

#Explicação de cada macro
