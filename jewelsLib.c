#include "jewelsLib.h"


long frames;
long score;

ALLEGRO_FONT* font;
long score_display;

int between(int min, int max)
{
    return (rand() % (max - min)) + min;
}

float betweenf(float min, float max)
{
    return ((float)rand() / (float)RAND_MAX) * (max-min) + min;
}


void hud_init()
{
    font = al_create_builtin_font();
    mustInit(font, "font"); 

    score_display = 0;
}

void hud_deinit()
{
    al_destroy_font(font);
}

void hud_update()
{
    if(frames % 2)
        return;
    
    for(long i = 5; i>0; i--)
    {
        long diff = 1 << i;
        if(score_display <= (score - diff))
            score_display += diff;
    }
}

int linear_combination(MATRIX** m, int i, int j){

    if((m[i][j].type == m[i][j+1].type)||(m[i][j].type == m[i][j-1].type)){
        return 1;
    }

    return 0;

}

int vertical_combination(MATRIX** m, int i, int j){

    if((m[i][j].y == 0)||(m[i][j].y == 380)){
        return 0;
    }
    if(m[i][j].type == m[i-1][j].type){
        return 1;
    }

    return 0;

}

MATRIX** matrix_init(int size)
{
    int dx = 30;
    int dy = 0;
    // Create a size x size matrix
    MATRIX** m = malloc(sizeof(MATRIX*) * size);
    mustInit(m, "matrix");
    for(int i = 0; i < size; i++)
    {
        m[i] = malloc(sizeof(MATRIX) * size);
        mustInit(m[i], "matrix");

        for(int j = 0; j < size; j++)
        {
            m[i][j].select[0] = 0;
            m[i][j].select[1] = 0;
            m[i][j].x = DISP_W/2 - dx;
            m[i][j].y = dy;
            m[i][j].type = rand() % 5;

            while((linear_combination(m, i, j))||(vertical_combination(m, i, j)))
                m[i][j].type = rand() % 5;
            
            dx -= 35;
        }
        dx = 35;
        dy += 35;
    }
    return m;
}

void matrix_deinit(MATRIX** m, int size)
{
    for(int i = 0; i < size; i++)
        free(m[i]);
    free(m);
}

void matrix_draw(MATRIX** matrix)
{
    for(int i = 0; i < MATRIX_SIZE; i++)
        {
            for(int j = 0; j < MATRIX_SIZE; j++)
            {
                switch (matrix[i][j].type)
                {
                case 0:
                    if(matrix[i][j].select[0] == 1)
                        al_draw_tinted_bitmap(sprites.green,al_map_rgb(0, 0, 0),matrix[i][j].x, matrix[i][j].y, 0);
                    else
                        al_draw_bitmap(sprites.green, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                case 1:
                    if(matrix[i][j].select[0] == 1)
                        al_draw_tinted_bitmap(sprites.blue,al_map_rgb(0, 0, 0),matrix[i][j].x, matrix[i][j].y, 0);
                    else
                        al_draw_bitmap(sprites.blue, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                case 2:
                    if(matrix[i][j].select[0] == 1)
                        al_draw_tinted_bitmap(sprites.red,al_map_rgb(0, 0, 0),matrix[i][j].x, matrix[i][j].y, 0);
                    else
                        al_draw_bitmap(sprites.red, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                case 3:
                    if(matrix[i][j].select[0] == 1)
                        al_draw_tinted_bitmap(sprites.yellow,al_map_rgb(0, 0, 0),matrix[i][j].x, matrix[i][j].y, 0);
                    else
                        al_draw_bitmap(sprites.yellow, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                case 4:
                    if(matrix[i][j].select[0] == 1)
                        al_draw_tinted_bitmap(sprites.purple,al_map_rgb(0, 0, 0),matrix[i][j].x, matrix[i][j].y, 0);
                    else
                        al_draw_bitmap(sprites.purple, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                
                default:
                    break;
                }
            }
        }
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

    if(easteregg){
        text_r = 255;
        text_g = 159;
        text_b = 48;
        score_r = 23;
        score_g = 23;
        score_b = 23;
        table_r = 23;
        table_g = 23;
        table_b = 23;

    }

    al_draw_textf(font, al_map_rgb(score_r, score_g, score_b), 150, 50, 0, "%06ld", score_display); 

    al_draw_filled_rectangle(DISP_W/2 - 30, 15, DISP_W/2 + 350, 370, al_map_rgb(shadow_r, shadow_g, shadow_b));
    al_draw_filled_rectangle(DISP_W/2 - 40, 10, DISP_W/2 + 340, 360, al_map_rgb(table_r, table_g, table_b));

    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), 100, 10, 0, "< T E R M O I L >");
    
}

void help_draw(bool easteregg)
{
    int text_r = 20;
    int text_g = 179;
    int text_b = 20;

    if(easteregg){
        text_r = 255;
        text_g = 159;
        text_b = 48;
    }

    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 10, ALLEGRO_ALIGN_CENTRE, "< T E R M O I L >");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 30, ALLEGRO_ALIGN_CENTRE, "F1 ou H - menu de ajuda");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 50, ALLEGRO_ALIGN_CENTRE, "Como jogar:");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 70, ALLEGRO_ALIGN_CENTRE, "Clique em duas peças para troca-las de lugar");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 90, ALLEGRO_ALIGN_CENTRE, "Combine 3 ou mais peças do mesmo tipo para eliminá-las");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 110, ALLEGRO_ALIGN_CENTRE, "Quanto mais peças você eliminar de uma vez, mais pontos você ganha");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 140, ALLEGRO_ALIGN_CENTRE, "<V>oltar");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 200, ALLEGRO_ALIGN_CENTRE, "Criado por: Thales Carvalho");
}

int is_combo(MATRIX** m)
{
    // Verifica se há combinações na matriz
    int i, j;
    int combo = 0;

    // Verifica linhas
    for(i = 0; i < MATRIX_SIZE; i++){
        for(j = 0; j < MATRIX_SIZE; j++){
            if(m[i][j].type == m[i][j+1].type && m[i][j].type == m[i][j+2].type){
                combo = 1;
                m[i][j].select[0] = 1;
                m[i][j+1].select[0] = 1;
                m[i][j+2].select[0] = 1;
            }
        }
    }

    // // Verifica colunas
    // for(i = 0; i < MATRIX_SIZE; i++){
    //     for(j = 0; j < MATRIX_SIZE; j++){
    //         if(m[j][i].type == m[j+1][i].type && m[j][i].type == m[j+2][i].type){
    //             combo = 1;
    //             m[j][i].select[0] = 1;
    //             m[j+1][i].select[0] = 1;
    //             m[j+2][i].select[0] = 1;
    //         }
    //     }
    // }

    return combo;
    
}

void menu_draw(bool easteregg)
{
    int text_r = 20;
    int text_g = 179;
    int text_b = 20;

    if(easteregg){
        text_r = 255;
        text_g = 159;
        text_b = 48;
    }

    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 50, ALLEGRO_ALIGN_CENTRE, "< T E R M O I L >");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 110, ALLEGRO_ALIGN_CENTRE, "<J>ogar");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 130, ALLEGRO_ALIGN_CENTRE, "<A>juda");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 150, ALLEGRO_ALIGN_CENTRE, "<R>anking");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 170, ALLEGRO_ALIGN_CENTRE, "<S>air");
}

void rank_draw(bool easteregg){
    int text_r = 20;
    int text_g = 179;
    int text_b = 20;

    if(easteregg){
        text_r = 255;
        text_g = 159;
        text_b = 48;
    }

    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 50, ALLEGRO_ALIGN_CENTRE, "< T E R M O I L >");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 110, ALLEGRO_ALIGN_CENTRE, "1 - Nome - 000000");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 130, ALLEGRO_ALIGN_CENTRE, "2 - Nome - 000000");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 150, ALLEGRO_ALIGN_CENTRE, "3 - Nome - 000000");
    al_draw_text(font, al_map_rgb(text_r, text_g, text_b), DISP_W/2, 170, ALLEGRO_ALIGN_CENTRE, "<V>oltar");
}

void swap_jewels(MATRIX** matrix, int* pos1, int* pos2)
{
    
    int aux = matrix[pos1[0]][pos1[1]].type;

    matrix[pos1[0]][pos1[1]].type = matrix[pos2[0]][pos2[1]].type;
    matrix[pos2[0]][pos2[1]].type = aux;


}

void main_game_loop(MATRIX** matrix, int* pos1, int* pos2, int pos_x, int pos_y)
{
        if((matrix[pos1[0]][pos1[1]].select[0] == 0)){
            mouse_on_jewel(matrix, pos1, pos_x, pos_y);
        }

        if((pos1[0] != -1)&&(matrix[pos1[0]][pos1[1]].select[0] != 0)){
            
            mouse_on_jewel(matrix, pos2, pos_x, pos_y);
            
            printf("pos1: %d %d\n", pos1[0], pos1[1]);
            printf("pos2: %d %d\n", pos2[0], pos2[1]);
            
            if((pos2[0] != -1))
            {

                if(((pos1[0] == pos2[0])&&((pos1[1] == pos2[1]+1)))||((pos1[0] == pos2[0])&&(pos1[1] == pos2[1]-1))||((pos1[0] == pos2[0] + 1)&&((pos1[1] == pos2[1])))||((pos1[0] == pos2[0] - 1)&&(pos1[1] == pos2[1])))
                {
                    swap_jewels(matrix, pos1, pos2);
                    matrix[pos2[0]][pos2[1]].select[0] = 0;
                    matrix[pos1[0]][pos1[1]].select[0] = 0;
                } 
                
                if(is_combo(matrix) == 1)
                {
                    printf("combo\n");
                }
                else
                {
                    printf("no combo\n");
                }
            }
        }
         
}

int mouse_on_jewel(MATRIX** m, int* pos, int x, int y)
{
    // Checa se o mouse esta em cima de algum jewel
    int valid = 0;
    for(int i = 0; i < MATRIX_SIZE && !valid; i++)
    {
        for(int j = 0; j < MATRIX_SIZE && !valid; j++)
        {
            if((x >= m[i][j].x) && (x <= m[i][j].x + 35) && (y >= m[i][j].y) && (y <= m[i][j].y + 35))
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
