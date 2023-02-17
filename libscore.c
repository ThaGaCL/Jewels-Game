#include "libscore.h"
#include "jewelsLib.h"

int is_new_high_score(){
    long valor_atual, novo_valor;
    FILE *arq;

    arq = fopen("assets/save/highscore.txt", "r");

    fscanf(arq, "%ld", &valor_atual);

    fclose(arq);

    if(score > valor_atual){
        novo_valor = score;
        arq = fopen("assets/save/highscore.txt", "w");
        fprintf(arq, "%ld", novo_valor);
        fclose(arq);
        return 1;
    }

    return 0;

}