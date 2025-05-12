#Como Rodar
bison -d parser.y   
flex scanner.l   

windows
    cc -o scanner parser.tab.c lex.yy.c -lfl 
mac linux
    cc -o scanner parser.tab.c lex.yy.c -lfl 

./scanner < entrada.txt 