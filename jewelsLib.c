#include "jewelsLib.h"

long frames;
long score;
long level = 1;

ALLEGRO_FONT *font;
long score_display;


void hud_init()
{
    font = al_create_builtin_font();
    mustInit(font, "font");

    score_display = 0; // Zera o score
}

void hud_deinit()
{
    al_destroy_font(font);
}

// Procura combinacoes por linhas
int linear_combination(MATRIX **m, int i, int j)
{

    if ((m[i][j].type == m[i][j + 1].type) || (m[i][j].type == m[i][j - 1].type))
    {
        return 1;
    }

    return 0;
}

// Procura combinacoes por colunas
int vertical_combination(MATRIX **m, int i, int j)
{

    if ((m[i][j].y == 0) || (m[i][j].y == 380))
    {
        return 0;
    }
    if (m[i][j].type == m[i - 1][j].type)
    {
        return 1;
    }

    return 0;
}


MATRIX **matrix_init(int size)
{
    // Posicao da primeira peça
    int dx = 30;
    int dy = 0;

    // Aloca e inicializa a matriz
    MATRIX **m = malloc(sizeof(MATRIX *) * size);
    mustInit(m, "matrix");

    // Preenche a matriz com as peças
    for (int i = 0; i < size; i++)
    {
        m[i] = malloc(sizeof(MATRIX) * size);
        mustInit(m[i], "matrix");

        for (int j = 0; j < size; j++)
        {
            m[i][j].select[0] = 0;
            m[i][j].select[1] = 0;
            m[i][j].x = DISP_W / 2 - dx;
            m[i][j].y = dy;
            m[i][j].type = rand() % 5; // Gera uma peça aleatória

            // Se essa peça gerar uma combinação, gera outra no lugar
            while ((linear_combination(m, i, j)) || (vertical_combination(m, i, j)))
                m[i][j].type = rand() % 5;

            dx -= 35;
        }
        dx = 35;
        dy += 36;
    }
    return m;
}

void matrix_deinit(MATRIX **m, int size)
{
    for (int i = 0; i < size; i++)
        free(m[i]);
    free(m);
}

void matrix_draw(MATRIX **matrix)
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            switch (matrix[i][j].type)
            {
            case 0:
                if (matrix[i][j].select[0] == 1)
                    al_draw_tinted_bitmap(sprites.green, al_map_rgb(0, 0, 0), matrix[i][j].x, matrix[i][j].y, 0);
                else
                    al_draw_bitmap(sprites.green, matrix[i][j].x, matrix[i][j].y, 0);
                break;
            case 1:
                if (matrix[i][j].select[0] == 1)
                    al_draw_tinted_bitmap(sprites.blue, al_map_rgb(0, 0, 0), matrix[i][j].x, matrix[i][j].y, 0);
                else
                    al_draw_bitmap(sprites.blue, matrix[i][j].x, matrix[i][j].y, 0);
                break;
            case 2:
                if (matrix[i][j].select[0] == 1)
                    al_draw_tinted_bitmap(sprites.red, al_map_rgb(0, 0, 0), matrix[i][j].x, matrix[i][j].y, 0);
                else
                    al_draw_bitmap(sprites.red, matrix[i][j].x, matrix[i][j].y, 0);
                break;
            case 3:
                if (matrix[i][j].select[0] == 1)
                    al_draw_tinted_bitmap(sprites.yellow, al_map_rgb(0, 0, 0), matrix[i][j].x, matrix[i][j].y, 0);
                else
                    al_draw_bitmap(sprites.yellow, matrix[i][j].x, matrix[i][j].y, 0);
                break;
            case 4:
                if (matrix[i][j].select[0] == 1)
                    al_draw_tinted_bitmap(sprites.purple, al_map_rgb(0, 0, 0), matrix[i][j].x, matrix[i][j].y, 0);
                else
                    al_draw_bitmap(sprites.purple, matrix[i][j].x, matrix[i][j].y, 0);
                break;
            case 5:
                break;
            case 6:
                if(matrix[i][j].select[0] == 1)
                    al_draw_tinted_bitmap(sprites.glitch, al_map_rgb(0, 0, 0), matrix[i][j].x, matrix[i][j].y, 0);
                else
                    al_draw_bitmap(sprites.glitch, matrix[i][j].x, matrix[i][j].y, 0);
                break;

            default:
                break;
            }
        }
    }
}

void menu_draw(bool easteregg)
{
    int text_r = 20;
    int text_g = 179;
    int text_b = 20;

    if (easteregg)
    {
        text_r = 255;
        text_g = 159;
        text_b = 48;
    }

    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 50, ALLEGRO_ALIGN_CENTRE, "< T E R M O I L >");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 110, ALLEGRO_ALIGN_CENTRE, "<J>ogar");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 130, ALLEGRO_ALIGN_CENTRE, "<A>juda");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 150, ALLEGRO_ALIGN_CENTRE, "<R>anking");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 170, ALLEGRO_ALIGN_CENTRE, "<S>air");
}

void rank_draw(bool easteregg)
{
    int text_r = 20;
    int text_g = 179;
    int text_b = 20;

    if (easteregg)
    {
        text_r = 255;
        text_g = 159;
        text_b = 48;
    }

    long highscore;
    FILE *arq;

    arq = fopen("assets/save/highscore.txt", "r");

    fscanf(arq, "%ld", &highscore);

    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 50, ALLEGRO_ALIGN_CENTRE, "< T E R M O I L >");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2 - 40, 110, ALLEGRO_ALIGN_CENTRE, "Highscore:");
    al_draw_textf(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2 + 40, 110, 0, "%06ld", highscore);
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 170, ALLEGRO_ALIGN_CENTRE, "<V>oltar");
}

void hud_draw(int x, int y, bool easteregg)
{
    int text_r = 20;
    int text_g = 179;
    int text_b = 20;
    int score_r = 255;
    int score_g = 255;
    int score_b = 255;
    int table_r = 219;
    int table_g = 218;
    int table_b = 222;
    int shadow_r = 0;
    int shadow_g = 0;
    int shadow_b = 0;
    int err_r = 23;
    int err_g = 23;
    int err_b = 23;

    if (easteregg)
    {
        text_r = 255;
        text_g = 159;
        text_b = 48;
        score_r = 23;
        score_g = 23;
        score_b = 23;
        table_r = 23;
        table_g = 23;
        table_b = 23;
        err_r = 255;
        err_g = 159;
        err_b = 48;
    }

    al_draw_textf(font, al_map_rgb(score_r, score_g, score_b), 150, 50, 0, "%06ld", score);

    al_draw_filled_rectangle(DISP_W / 2 - 30, 15, DISP_W / 2 + 350, 379, al_map_rgb(shadow_r, shadow_g, shadow_b));
    al_draw_filled_rectangle(DISP_W / 2 - 40, 10, DISP_W / 2 + 340, 369, al_map_rgb(table_r, table_g, table_b));

    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), 100, 10, 0, "< T E R M O I L >");

    switch (level)
    { 
    case 1:
        al_draw_text(font, al_map_rgb(text_r, text_g, text_b), 140, 30, 0, "Level: 1");
        break;
    case 2:
        al_draw_text(font, al_map_rgb(text_r, text_g, text_b), 140, 30, 0, "Level: 2");
        break;
    case 3:
        al_draw_text(font, al_map_rgb(text_r, text_g, text_b), 140, 30, 0, "Level: 3");
        break;
    default:
        break;
    }  

    al_draw_text(font, al_map_rgb(err_r, err_g, err_b), 50, 300, 0, "Segmentation fault(core dumped)");
}

void help_draw(bool easteregg)
{
    int text_r = 20;
    int text_g = 179;
    int text_b = 20;

    // Se easteregg estiver ativado, muda as cores
    if (easteregg)
    {
        text_r = 255;
        text_g = 159;
        text_b = 48;
    }

    // Escreve arvore no meio da tela

    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 10, ALLEGRO_ALIGN_CENTRE, "< T E R M O I L >");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 30, ALLEGRO_ALIGN_CENTRE, "F1 ou H - menu de ajuda");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 50, ALLEGRO_ALIGN_CENTRE, "Como jogar:");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 70, ALLEGRO_ALIGN_CENTRE, "Clique em duas peças para troca-las de lugar");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 90, ALLEGRO_ALIGN_CENTRE, "Combine 3 ou mais peças do mesmo tipo para eliminá-las");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 110, ALLEGRO_ALIGN_CENTRE, "Quanto mais peças você eliminar de uma vez, mais pontos você ganha");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 140, ALLEGRO_ALIGN_CENTRE, "<V>oltar");

    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W / 2, 200, ALLEGRO_ALIGN_CENTRE, "Criado por: Thales Carvalho");
}

void replace_jewels_row(MATRIX **m, int i, int j)
{
    // Substitui as joias pelas de cima e geram novas joias no topo da coluna
    int k;

    if(i >= 2)
    {
        for(k = i + 2; k > 2; k--)
        {
            m[k][j].type = m[k-3][j].type;
        }
    }

    // Como o for acima não chega até o topo da coluna (pois acessaria uma posicao fora da matriz),
    // é necessário fazer uma substituição manual para as joias do topo 
    m[0][j].type = rand() % 5;  
    m[1][j].type = rand() % 5;
    m[2][j].type = rand() % 5;

    if((level > 1)){ 
        // Create a small chance of creating a glitch that increses as the score increases
        if((rand() % 100) < (score / 1000)){
            for(int l = (rand() % 3); l < 3; l++){
                m[l][j].type = 6;
            }
        }

    }

}

void replace_jewels_line(MATRIX **m, int i, int j)
{
    // Substitui as joias pelas de cima e geram novas joias no topo
    if(i >= 1)
    {


        for(int l = j + 2; l >= j; l--){
            for(int k = i; k > 0; k--)
            {
                m[k][l].type = m[k-1][l].type;
            }
        }

    }
    
    m[0][j].type = rand() % 5;
    m[0][j + 1].type = rand() % 5;
    m[0][j + 2].type = rand() % 5;

    if((level > 1)){ 
        // Create a small chance of creating a glitch that increses as the score increases
        if((rand() % 100) < (score / 1000)){
            m[0][j].type = 6;
        }

    }
}

int is_combo(MATRIX **m)
{
    // Verifica se há combinações na matriz
    int i, j;
    int combo = 0;


    // Verifica linhas
    for (i = 0; i < MATRIX_SIZE; i++)
    {
        for (j = 0; j < MATRIX_SIZE - 2; j++)
        {
            if ((m[i][j].type != 6) && (m[i][j].type == m[i][j + 1].type && m[i][j].type == m[i][j + 2].type))
            {
                combo = 1;
                if (combo > 0)
                {
                    al_play_sample(success_sound, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    m[i][j].type = 5;
                    m[i][j + 1].type = 5;
                    m[i][j + 2].type = 5;
                    score += combo * 100;
                }
                replace_jewels_line(m, i, j);
            }
        }
    }

    // Verifica colunas
    for (i = 0; i < MATRIX_SIZE; i++)
    {
        for (j = 0; j < MATRIX_SIZE - 2; j++)
        {
            if ((m[j][i].type != 6) && (m[j][i].type == m[j + 1][i].type && m[j][i].type == m[j + 2][i].type))
            {
                combo = 1;
                if (combo > 0)
                {
                    al_play_sample(success_sound, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    m[j][i].type = 5;
                    m[j + 1][i].type = 5;
                    m[j + 2][i].type = 5;
                    score += combo * 100;
                    combo = 0;
                    replace_jewels_row(m, j, i);
                }
            }
        }
    }

    
    return combo;
}


void swap_jewels(MATRIX **matrix, int *pos1, int *pos2)
{

    int aux = matrix[pos1[0]][pos1[1]].type;

    matrix[pos1[0]][pos1[1]].type = matrix[pos2[0]][pos2[1]].type;
    matrix[pos2[0]][pos2[1]].type = aux;
}

void main_game_loop(MATRIX **matrix, int *pos1, int *pos2, int pos_x, int pos_y)
{
    // Verifica se há combinações na matriz
    is_combo(matrix);

    // Verifica se o mouse está sobre uma joia e a seleciona

    if(pos1[0] == -1){
        mouse_on_jewel(matrix, pos1, pos_x, pos_y);
    }
    else if ((matrix[pos1[0]][pos1[1]].select[0] == 0))
    {
        mouse_on_jewel(matrix, pos1, pos_x, pos_y);
    }

    // Caso a primeira joia tenha sido selecionada, verifica se o mouse está sobre a segunda joia
    if ((pos1[0] != -1) && (matrix[pos1[0]][pos1[1]].select[0] != 0))
    {

        mouse_on_jewel(matrix, pos2, pos_x, pos_y);

        if ((pos2[0] != -1))
        {
            // Caso a segunda joia tenha sido selecionada, verifica se as duas são vizinhas
            if (((pos1[0] == pos2[0]) && ((pos1[1] == pos2[1] + 1))) || ((pos1[0] == pos2[0]) && (pos1[1] == pos2[1] - 1)) || ((pos1[0] == pos2[0] + 1) && ((pos1[1] == pos2[1]))) || ((pos1[0] == pos2[0] - 1) && (pos1[1] == pos2[1])))
            {
                swap_jewels(matrix, pos1, pos2);
                // Desseleciona as joias
                matrix[pos2[0]][pos2[1]].select[0] = 0;
                matrix[pos1[0]][pos1[1]].select[0] = 0;

                // Caso um combo não tenha sido feito, retorna as joias para a posição inicial e toca o som de erro
                if(!is_combo(matrix)){
                    al_play_sample(fail_sound, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    swap_jewels(matrix, pos1, pos2);
                }

            }
                
        }
    }

    // Verifica se o jogador passou de nível
    if((level < 3) && (score >= 2000 * level)){
        level++;
        al_play_sample(levelup_sound, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        matrix_deinit(matrix, MATRIX_SIZE);
        matrix = matrix_init(MATRIX_SIZE);
    }

    // Verifica se é nova highscore
    is_new_high_score();

}

int mouse_on_jewel(MATRIX **m, int *pos, int x, int y)
{
    // Checa se o mouse esta em cima de algum jewel
    int valid = 0;
    for (int i = 0; i < MATRIX_SIZE && !valid; i++)
    {
        for (int j = 0; j < MATRIX_SIZE && !valid; j++)
        {
            if ((x >= m[i][j].x) && (x <= m[i][j].x + 34) && (y >= m[i][j].y) && (y <= m[i][j].y + 34))
            {
                m[i][j].select[0] = 1;
                pos[0] = i;
                pos[1] = j;
                valid = 1;
            }
            else
            {
                m[i][j].select[0] = 0;
            }
        }
    }
    if (!valid)
    {
        pos[0] = -1;
        pos[1] = -1;
        return 0;
    }
    else
        return 1;
}
