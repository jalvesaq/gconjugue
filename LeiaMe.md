# GConjugue -- Informações adicionais

Ao iniciar, o GConjugue carrega um banco de dados contendo verbos 
conjugados. Esses verbos são usados como paradigmas para a conjugação 
dos demais verbos presentes no banco. Alguns dos verbos estão 
explicitamente listados como seguidores de um dos paradigmas, mas 
outros estão listados apenas como verbos existentes. O programa atribui 
um paradigma para esses verbos, bem como a qualquer verbo digitado pelo 
usuário.

O GConjugue apresenta a seguinte informação antes da conjugação dos verbos:

**Paradigma: &lt;verbo&gt;**: Indica qual verbo serve de
paradigma para a conjugação; ou o próprio verbo conjugado é um paradigma ou está
explicitamente listado como seguidor do paradigma.

**Paradigma deduzido:  &lt;verbo&gt;**: O verbo está
presente no banco, mas não está classificado. Seu paradigma foi “calculado” pelo
programa.

**Não consta do banco de verbos**: Mesmo não constando do
banco de verbos, o verbo fornecido pelo usuário poderá ser conjugado se for
possível calcular um paradigma para ele.

**Não sei conjugar  &lt;verbo&gt;**: O GConjugue não
conseguiu relacionar nenhum paradigma com a expressão fornecida pelo usuário.
Isto somente deve acontecer com termos cujo tratamento como verbo é impossível
na língua portuguesa (palavras não terminadas com a letra ‘r’, por exemplo).

O número de paradigmas existente no banco de verbos do GConjugue é superior ao
número de paradigmas reconhecidos pela gramática normativa da língua portuguesa
porque o algoritmo do GConjugue não consegue extrair de um mesmo conjunto de
regras a conjugação correta de verbos irregulares que, nas conjugações, alteram
da mesma forma a última vogal do radical, como, por exemplo, “dormir” e
“tossir”, convencionalmente considerados seguidores do mesmo paradigma.

Um verbo não classificado no próprio banco como seguidor de um dos paradigmas,
tem seu paradigma deduzido pelo programa pela comparação da sua terminação com a
de alguns verbos. As comparações são feitas na sequência abaixo e são
interrompidas quando é encontrada uma coincidência de terminações:

```
çar  abraçar
iar  apoiar
gar  chegar
car  comunicar
oar  magoar
ear  passear
ar   cantar

cer  conhecer
guer erguer
ger  proteger
er   vender

ruir ruir
guir extinguir
uir  atribuir
air  cair
gir  afligir
zir  traduzir
ir   partir

or   propor
```


## Versões futuras

Algumas ideias para melhorias do programa aguardando desenvolvedores
voluntários:

   - **0.8**

      - Tratamento adequado dos verbos pronominais e reflexivos, tais como
        aproximar-se, apiedar-se, comprazer-se, autonomear-se, doer-se e
        condoer-se.

      - Usar cor cinza ou de alguma outra forma diferenciar o pronome do
        verbo.

      - Criar algoritmo desconjugador, a ser ativado quando for impossível
        tratar a expressão digitada como verbo no infinitivo.

      - Sugerir um verbo se a expressão digitada não constar do banco de
        verbos.

      - Classificar verbos como regular/irregular conforme gramática
        normativa.

      - Acrescentar opção de conjugação na forma de tabela.


   - **1.0**

      - O programa será promovido a 1.0 quando todos os verbos do
        BancoDeVerbos estiverem classificados como seguidores de algum
        paradigma. Mas estou deixando essa tarefa de classificação para outros
        voluntários (ainda inexistentes).
