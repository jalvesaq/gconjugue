# GConjugue -- Informações adicionais

Informações sobre o funcionamento do programa estão disponíveis no menu
*Ajuda/Conteúdo*.

## Versões futuras

Algumas ideias para melhorias do programa aguardando colaboradores voluntários
(não sendo necessário nenhum conhecimento de programação):


   - Classificar paradigmas como regular/irregular conforme gramática
     normativa. Registrar paradigma oficial (sem considerar acentuações
     específicas).

   - Tratamento adequado dos verbos pronominais e reflexivos, tais como
     aproximar-se, apiedar-se, comprazer-se, autonomear-se, doer-se e
     condoer-se.


   - **1.0**

      - O programa será promovido a 1.0 quando todos os verbos do arquivo
        `paradigms_and_verbs` estiverem classificados como seguidores de algum
        paradigma. Mas estou deixando essa tarefa de classificação para outros
        voluntários (ainda inexistentes). Não é preciso nenhum conhecimento de
        programação: basta ter conhecimento de gramática normativa e tempo
        para pesquisar sobre a conjugação oficial dos verbos.


## Sobre o banco de verbos

O arquivo `data/paradigms_and_verbs` contém o banco de dados com as
conjugações dos verbos utilizadas pelo gconjuge. O banco foi iniciado a partir
de uma cópia do arquivo `/usr/lib/brazilian-conjugate/verbos-UTF-8` o qual faz
parte do pacote brazilian-conjugate do projeto Debian.

A nota abaixo estava presente no banco original:

> Banco de conjugações de verbos da língua portuguesa
> (conforme o modo de falar de São Paulo, Brasil), versão
> 1.1 por Ricardo Ueda Karpischek (ueda@ime.usp.br),
> junho de 1999. Este banco faz parte do programa conjugue,
> e aplica-se a ele tudo o que se prescreve para aquele
> programa no referente a direitos autorais.
>
> Muitas pessoas colaboraram para a ampliação e depuração deste
> banco. Uma lista atualizada dos seus nomes com alguns outros
> comentários pode ser encontrada em
> http://www.ime.usp.br/~ueda/br.ispell
>
> Os verbos defectivos precisam ser revistos.
>
> As formas enclíticas como amá-la ou o preocuparmo-nos não estão
> sendo geradas.
>
> Provir na terceira do plural é provêm ou provém?
>
>
> *Abreviações*
>
> FN - formas nominais: infinitivo, gerúndio e particípio
>
> IP - infinitivo pessoal
>
>
> PI - presente do indicativo
>
> II - imperfeito do indicativo
>
> EI - perfeito do indicativo
>
> MI - mais-que-perfeito do indicativo
>
> TI - futuro do pretérito do indicativo
>
> FI - futuro do presente do indicativo
>
>
> PS - presente do subjuntivo
>
> IS - imperfeito do subjuntivo
>
> FS - futuro do subjuntivo
>
>
> IA - imperativo afirmativo
>
> IN - imperativo negativo

Ao definir um novo paradigma não é preciso repetir todas as conjugações;
apenas as que introduzem mudanças em relação ao paradigma anterior.
