# T2-Seguranca-Crypto
- Segundo trabalho da disciplina CI301 - Introdução à Segurança Computacional
- Tem como finalidade gerar um dicionário de palavras para tentar quebrar, por força bruta, senhas de um arquivo especifíco passado pelo professor.
- É composto de 3 partes:
  1. Wordlist: Um programa que, dado um path de diretório, lê todos os arquivos e gera um dicionário sem repetição de palavras.
  2. Brutexor: Um programa que, dada um dica cifrada com xor e convertida um hexadecimal, o tamanho de duplas desse hexadecimal, uma hash em md5 da senha que cifrou essa dica e um tamanho de senha; ele encontra a senha e descriptografa a dica, ambos por força bruta.
  3. A terceira parte requer o uso do programa John the Ripper, na qual passa-se o dicionario gerado para que ele quebre a criptografia do arquivo dado pelo professor.
  
**Compilação**
